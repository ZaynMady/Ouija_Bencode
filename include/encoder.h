#ifndef ENCODER_H
#define ENCODER_H

#include <openssl/sha.h>
#include "bencodeelement.h"
#include <vector>
#include <string> 
#include <map>


namespace ouija{


std::vector <unsigned char> encode_str(std::string &decoded_data);
std::vector <unsigned char> encode_int(int &decoded_data);
std::vector <unsigned char> encode_binary(std::vector<unsigned char> &decoded_data);
std::vector <unsigned char> encode_list(std::vector<bencodeelement> &decoded_data);
std::vector <unsigned char> encode_dict(std::map<std::string, bencodeelement> &decoded_data);

std::vector<unsigned char> encode(std::map<std::string, bencodeelement> &decoded_data);


};


#endif //ENCODER_H