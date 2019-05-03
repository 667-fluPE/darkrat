#include <cstdint>
#include <string>
#include "Base64.h"
//TODO AES CURRENT XOR
class XOR {
	uint32_t regs[4];

public:

	static std::string encryptDecrypt(std::string toEncrypt) {
		char key[3] = { 'K', 'C', 'Q' }; //Any chars will work, in an array of any size
		std::string output = toEncrypt;

		for (int i = 0; i < toEncrypt.size(); i++)
			output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

		return output;
	}

	static std::string encryptReqeust(std::string params) {
		std::string encryptedPostParams = encryptDecrypt(base64_encode((const unsigned char*)params.c_str(), params.length()));
		std::string finalPost = base64_encode((const unsigned char*)encryptedPostParams.c_str(), encryptedPostParams.length());
		return finalPost;
	}

};

