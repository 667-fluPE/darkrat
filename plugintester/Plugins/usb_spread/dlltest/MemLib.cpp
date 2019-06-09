#include "pch.h"
#include <stdio.h> 
#include <string>

#include <sys/types.h>
#include <io.h>
#include <windows.h>

#include <string.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ws2tcpip.h>

#define PASSWORD "niggerdick"
#ifdef WIN32
#define pid_t int
#endif

extern "C"
{

	char getRemovableDisk();

	__declspec(dllexport) void Spread(std::string url)
	{
		printf("Hello from DLL !\n");


	}
}