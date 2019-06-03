
#include <tchar.h>
#include "MemLoadLibrary.h"
#include <Windows.h>
#include <urlmon.h>
#include <string>
#pragma comment (lib, "urlmon.lib")

typedef void(_cdecl* func)(std::string test);



//Removed for Commit
//unsigned char rawData[36864] = {}


int _tmain(int argc, _TCHAR* argv[])
{
	CLoad lib;
	HANDLE hLibrary = 0;

	//hLibrary = lib.LoadFromMemory(test, sizeof(test)); // loaded the dll from byte array.
	hLibrary = lib.LoadFromFile("C:\\Users\\darkspider\\Desktop\\DarkRatCoding\\darkrat\\plugintester\\Debug\\ExampleTask.dll"); // loaded the dll from byte array.
	func fn = (func)lib.GetProcAddressFromMemory(hLibrary, "DisplayHelloFromDLL");
	fn("");
	lib.FreeLibraryFromMemory(hLibrary);
	return 0;
}