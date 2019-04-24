#include <windows.h>
#include <string>
#include <sstream>
#include <limits.h>
#include <intrin.h>
typedef unsigned __int32  uint32_t;



class OsHelpers {
	uint32_t regs[4];

public:

	static std::string getCpuName()	{
		// Get extended ids.
		int CPUInfo[4] = { -1 };
		__cpuid(CPUInfo, 0x80000000);
		unsigned int nExIds = CPUInfo[0];

		// Get the information associated with each extended ID.
		char CPUBrandString[0x40] = { 0 };
		for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
			__cpuid(CPUInfo, i);

			// Interpret CPU brand string and cache information.
			if (i == 0x80000002)
			{
				memcpy(CPUBrandString,
					CPUInfo,
					sizeof(CPUInfo));
			}
			else if (i == 0x80000003)
			{
				memcpy(CPUBrandString + 16,
					CPUInfo,
					sizeof(CPUInfo));
			}
			else if (i == 0x80000004)
			{
				memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
			}
		}
		
		return CPUBrandString;
	}

	static std::string getGpuName() {
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
			hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
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


	static std::string getRam() {
		char* str = (char*)malloc(200);
		unsigned long long rams;
		GetPhysicallyInstalledSystemMemory(&rams);
		_itoa(rams, str, 10);
		return str;
	}

	static std::string checkPEIsAdmin() {
		char* str = (char*)malloc(200);
		bool fRet = false;
		HANDLE hToken = NULL;
		if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
			TOKEN_ELEVATION Elevation;
			DWORD cbSize = sizeof(TOKEN_ELEVATION);
			if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
				fRet = Elevation.TokenIsElevated;
			}
		}
		if (hToken) {
			CloseHandle(hToken);
		}

		if (fRet)
			strcpy(str, "true");
		else
			strcpy(str, "false");

		return str;
	}

	//https://www.codeproject.com/Tips/107866/32-Bit-or-64-bit-OS
	static std::string PrcessorArchitecture() {
		BOOL bIs64Bit = FALSE;
		#if defined(_WIN64)
			bIs64Bit = TRUE;  
		#elif defined(_WIN32)
			typedef BOOL(WINAPI * LPFNISWOW64PROCESS) (HANDLE, PBOOL);
			LPFNISWOW64PROCESS pfnIsWow64Process = (LPFNISWOW64PROCESS)GetProcAddress(GetModuleHandle(_T("kernel32")), "IsWow64Process");
			if (pfnIsWow64Process)
				pfnIsWow64Process(GetCurrentProcess(), &bIs64Bit);
		#endif
		if (bIs64Bit) {
			return "x64";
		}
		else {
			return "x86";
		}
	}
};
