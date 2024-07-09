#ifndef ENCRYPTER_H
#define ENCRYPTER_H


//Calculating the Info Hash using the OpenSSL library
#include <openssl/sha.h>
#include <vector>
#include <map> 
#include "bencodeelement.h"
#include <string> 
#include <iostream>

std::string encrpyt_info_hash(std::map<std::string, bencodeelement> info_dict);

std::string generate_peerid(std::string &client_name, std::string &client_version);



#endif //ENCRYPTER_H