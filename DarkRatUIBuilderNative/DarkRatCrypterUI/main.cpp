#include "DarkRatCrypterUI.h"
#include "loginUI.h"
#include <QtWidgets/QApplication>
#include <tchar.h>
#include <iostream>
#include <string>
#include <wininet.h>
#include <QtWidgets\QMessageBox>
#pragma comment (lib, "WinInet.lib")

int main(int argc, char *argv[])
{


	QApplication a(argc, argv);
	//DarkRatCrypterUI w;
	std::ifstream infile("config.ini");

	if (infile.good())
	{
		std::string post;
		getline(infile, post);
		try {
			//Retrieve default http user agent
			char httpUseragent[512];
			DWORD szhttpUserAgent = sizeof(httpUseragent);
			//ObtainUserAgentString( 0, httpUseragent, &szhttpUserAgent );

			char m[5];

			//HINTERNET internet = InternetOpen(_T(" Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.153 Safari/537.36"), INTERNET_OPEN_TYPE_PROXY, L"SOCKS=127.0.0.1:9050", NULL, 0);

			HINTERNET internet = InternetOpen(_T(" Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.153 Safari/537.36"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
			if (internet == NULL)
			{
				qInfo() << "InternetOpen failed";
			}
			if (internet != NULL)
			{

				HINTERNET connect = InternetConnect(internet, _T("testwebspace12122.000webhostapp.com"), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
				if (connect == NULL)
				{
					qInfo() << "InternetConnect failed";
				}
				if (connect != NULL)
				{

					HINTERNET request = HttpOpenRequest(connect, _T("POST"), _T("/validate.php"), _T("HTTP/1.1"), NULL, NULL,
						INTERNET_FLAG_HYPERLINK | INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
						INTERNET_FLAG_IGNORE_CERT_DATE_INVALID |
						INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
						INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS |
						INTERNET_FLAG_NO_AUTH |
						INTERNET_FLAG_NO_CACHE_WRITE |
						INTERNET_FLAG_NO_UI |
						INTERNET_FLAG_PRAGMA_NOCACHE |
						INTERNET_FLAG_RELOAD, NULL);
					if (request == NULL)
					{
						
						QMessageBox msgBoxfailed;
						msgBoxfailed.setText("DarkRat License");
						msgBoxfailed.setInformativeText("Check your Internet we have no connection, or the License server is Offline conntact me!");
						msgBoxfailed.setStandardButtons(QMessageBox::Cancel);
						msgBoxfailed.setDefaultButton(QMessageBox::Cancel);
						int ret = msgBoxfailed.exec();
						
					}
					if (request != NULL)
					{
						int datalen = 0;
						if (post.c_str() != NULL) datalen = post.length();
						LPCWSTR RH = _T("Connection: keep-Alive\r\n");
						HttpAddRequestHeaders(request, RH, _tcslen(RH), HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
						LPCWSTR RH1 = _T("Content-Type: application/x-www-form-urlencoded\r\n");
						HttpAddRequestHeaders(request, RH1, _tcslen(RH1), HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
						LPCWSTR RH3 = _T("Accept-Language: en-US,en;q=0.8\r\n");
						HttpAddRequestHeaders(request, RH3, _tcslen(RH3), HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
						LPCWSTR RH4 = _T("Accept: */*\r\n");
						HttpAddRequestHeaders(request, RH4, _tcslen(RH4), HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
						LPCWSTR RH5 = _T("Accept-Encoding: gzip,deflate,sdch\r\n");
						HttpAddRequestHeaders(request, RH5, _tcslen(RH5), HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);

						HttpSendRequestA(request, NULL, 0, (LPVOID)post.c_str(), datalen);
						DWORD rSize;
						char tmp[1024 + 1];
						std::string szBuffer;

						while (InternetReadFile(request, tmp, 1024, &rSize) && rSize > 0)
						{
							tmp[rSize] = '\0';
							szBuffer += (std::string)tmp;
						}
						qInfo() << QString::fromStdString(szBuffer);


						DWORD StatusCode = 0;
						DWORD StatusCodeLen = sizeof(StatusCode);
						HttpQueryInfo(request, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &StatusCode, &StatusCodeLen, NULL);
						if (StatusCode == 200)
						{

							qInfo() << "Sucess=200";
						}
						else
						{
							qInfo() << "failed=" << StatusCode;
						}

						if (szBuffer == "access") {
							DarkRatCrypterUI w;
							w.show();
							return a.exec();
						}
						else {
						
						}


						InternetCloseHandle(request);
					}
				}
				InternetCloseHandle(connect);
			}
			InternetCloseHandle(internet);
		}
		catch (...) {}
	}

	infile.close();


	login w;
	w.show();
	return a.exec();
}
/*


	ifstream infile("config.ini");

	if (infile.good())
	{
		string sLine;
		getline(infile, sLine);
		if (!sLine.empty()) {
			std::string accessbool = postRequest(sLine);
			if (accessbool == "access") {
				DarkRatCrypterUI* builder;
				builder = new DarkRatCrypterUI(this);
				builder->show();
				this->close();
			}
			else {
				QMessageBox msgBox;
				msgBox.setText("DarkRat License");
				msgBox.setInformativeText("You account Looks not Existing or Banned");
				msgBox.setStandardButtons(QMessageBox::Cancel);
				msgBox.setDefaultButton(QMessageBox::Cancel);
				remove("config.ini");
				int ret = msgBox.exec();

			}
		}
	}

	infile.close();
*/