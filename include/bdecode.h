#ifndef BDECODE_H
#define BDECODE_H

//DECODER
#include <vector>
#include <string>
#include "bencodeelement.h"
#include <map>

namespace ouija{
//function to decode a string 
std::string decode_str(std::vector<unsigned char> encoded_data, size_t & position);
//function to decode an int
long decode_int(std::vector<unsigned char> encoded_data, size_t &  position);
//function to decode a dict
std::map<std::string, bencodeelement> decode_dict(std::vector<unsigned char>&encoded_data, size_t &position);
//function to decode a list
std::vector<bencodeelement> decode_list(std::vector<unsigned char> encoded_data, size_t& position);
//function to decode binary data, particularly used for pieces
std::vector<unsigned char> decode_binary(std::vector<unsigned char> encoded_data, size_t &position);


//function decode a ril3
std::vector<unsigned char> parse_torrent_file(std::string &filepath);

std::map<std::string, bencodeelement> decode(std::vector<unsigned char> buffer);

void write_info_file(std::map<std::string, bencodeelement> decoded_dict);
}




#endif //BDECODE_H