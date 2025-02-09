#pragma once

#include <openssl/evp.h>

class ARC4
{
public:
	ARC4(uint32 len);
	ARC4(uint8* seed, uint32 len);
	~ARC4();

	void Init(uint8* seed);
	void UpdateData(int len, uint8* data);

private:
	EVP_CIPHER_CTX* m_ctx;
};
