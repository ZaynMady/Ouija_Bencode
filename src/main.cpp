#include <string> 
#include <iostream>
#include <cstring>
#include "bdecode.h"



int main(int argc, char **argv)
{
    if(argc != 3)
    {
        std::cout << "invalid number of arguments" << std::endl;
    }
    else
    {
        if(strcmp(argv[1], "decode") == 0)
        {
            std::string filepath = argv[2];
            auto buffer = ouija::parse_torrent_file(filepath);
            auto dict = ouija::decode(buffer);
            ouija::write_info_file(dict);
        }
        else
        {
            std::cout << "invalid syntax\n";
        }
    }
}