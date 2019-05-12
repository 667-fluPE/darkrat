#include <cstdint>
#include <string>
#include "Base64.h"
//TODO AES CURRENT XOR
class XOR {
	uint32_t regs[4];

public:

	static std::string encryptDecrypt(std::string toEncrypt) {
		darkRat::config::config config = darkRat::config::load();
		std::string enckey = config.encryptionKey;
		char* key = (char*)enckey.c_str();
		size_t keylen = enckey.length();
		std::string output = toEncrypt;
		for (int i = 0; i < toEncrypt.size(); i++)
			output[i] = toEncrypt[i] ^ key[i % keylen];

		return output;

	}

	static std::string encryptReqeust(std::string params) {
		std::string encryptedPostParams = encryptDecrypt(base64_encode((const unsigned char*)params.c_str(), params.length()));
		std::string finalPost = base64_encode((const unsigned char*)encryptedPostParams.c_str(), encryptedPostParams.length());
		return finalPost;
	}

};

