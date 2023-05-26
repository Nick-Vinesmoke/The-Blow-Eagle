#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include <openssl/evp.h>

namespace crypto
{
    std::string base64_decode(std::string data);
    std::string base64_encode(std::string data);

    std::vector<unsigned char> v80_decrypt(const std::string &key, std::vector<unsigned char> data);
}