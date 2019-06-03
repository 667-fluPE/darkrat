#include "pch.h"
#include <stdio.h> 
#include <string>


extern "C"
{

	__declspec(dllexport) void DisplayHelloFromDLL(std::string url)
	{
		//printf("Hello from DLL !\n");

		MessageBox(NULL, TEXT("Open the message box "), TEXT("message"), MB_OK | MB_SYSTEMMODAL);


	}
}