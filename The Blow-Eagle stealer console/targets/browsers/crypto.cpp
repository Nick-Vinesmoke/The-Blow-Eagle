#include "crypto.hpp"

std::string crypto::base64_decode(std::string data)
{
    std::size_t padding_length = 3 * data.size() / 4;
    std::vector<unsigned char> buffer(padding_length + 1);
    std::size_t output_length = EVP_DecodeBlock(buffer.data(), reinterpret_cast<const unsigned char*>(data.c_str()), data.size());
    return std::string(buffer.begin(), buffer.end());
}

std::string crypto::base64_encode(std::string data)
{
    std::size_t padding_length = 4 * ((data.size() + 2) / 3);
    std::vector<unsigned char> buffer(padding_length + 1);
    std::size_t output_length = EVP_EncodeBlock(buffer.data(), reinterpret_cast<const unsigned char*>(data.c_str()), data.size());
    return std::string(buffer.begin(), buffer.end());
}

std::vector<unsigned char> crypto::v80_decrypt(const std::string &key, std::vector<unsigned char> data)
{
    std::vector<unsigned char> iv(data.begin() + 3, data.begin() + 15);
    std::vector<unsigned char> buffer(data.begin() + 15, data.end() - 15);
    std::vector<unsigned char> decrypted_buffer(buffer.size());

    EVP_CIPHER_CTX *ctx;
    int len, plaintext_len = 0;

    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL);
    EVP_DecryptInit_ex(ctx, NULL, NULL, (unsigned char*)key.c_str(), iv.data());
    EVP_DecryptUpdate(ctx, decrypted_buffer.data() + plaintext_len, &len, buffer.data() + plaintext_len, buffer.size() - plaintext_len);
    plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, decrypted_buffer.data(), &len);
    EVP_CIPHER_CTX_free(ctx);

    return std::vector<unsigned char>(decrypted_buffer.begin(), decrypted_buffer.begin() + plaintext_len - 1);
}