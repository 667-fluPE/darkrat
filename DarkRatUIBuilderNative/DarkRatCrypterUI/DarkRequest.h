#include <iostream>
#include <shlwapi.h>
#include <wininet.h>
#include <string>


using namespace std;

#pragma comment (lib, "WinInet.lib")




std::string postRequest()
{


	std::string param = "test=test";
	std::string path = "/lol.php";
	TCHAR hdrs[] = TEXT("Content-Type: application/x-www-form-urlencoded", "Cache-Control: no-cache, no-store");
	LPVOID frmdata = "test=test";
	LPCSTR accept[2] = { "text/plain", NULL };
	HINTERNET hSession = InternetOpen(L"MyAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	HINTERNET hConnect = InternetConnect(hSession, L"http://127.0.0.1", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	HINTERNET hRequest = HttpOpenRequest(hConnect, L"POST", (LPCWSTR)path.c_str(), NULL, NULL, (LPCWSTR*)accept, INTERNET_FLAG_RESYNCHRONIZE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD, 1);



	if (!HttpSendRequest(hRequest,
		hdrs,
		strlen((const char*)hdrs),
		frmdata, //lpOptional <--Your POST data...not really optional for you.
		strlen(param.c_str()))) {
		DWORD errorCode = GetLastError();
		std::cout << errorCode;
	}
	//HttpSendRequest(hRequest, hdrs, strlen(hdrs), frmdata, strlen(param.c_str()));
	DWORD rSize;
	char tmp[1024 + 1];
	string szBuffer;

	while (InternetReadFile(hRequest, tmp, 1024, &rSize) && rSize > 0)
	{
		tmp[rSize] = '\0';
		szBuffer += (string)tmp;
	}
	InternetCloseHandle(hSession);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hRequest);
	//std::cout << szBuffer;
	return szBuffer;

}