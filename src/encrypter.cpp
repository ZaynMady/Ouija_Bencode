#include "encrypter.h"
#include "encoder.h"
#include <openssl/sha.h>
#include <fstream>
#include <iomanip>



std::string encrpyt_info_hash(std::map<std::string, bencodeelement> info_dict)
{
    std::vector <unsigned char> serialized_info = ouija::encode_dict(info_dict);
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(serialized_info.data()), serialized_info.size(), hash);
    
    std::stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}
//generating the random part
#include <string> 
#include <ctime>
#include <cstdlib>

std::string generateRandomString(size_t length) {
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = sizeof(charset) - 1;
    std::string random_string;

    for (size_t i = 0; i < length; ++i) {
        random_string += charset[rand() % max_index];
    }

    return random_string;
}
std::string generate_peerid(std::string &client_name, std::string& client_version)
{
    std::string peer_id;
    std::string prefix = '-' + client_name + client_version + '-';
    std::string random_part = generateRandomString(8);
    peer_id = prefix + random_part;

    return std::string(peer_id);
}