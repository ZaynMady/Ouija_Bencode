#include <variant>
#include <vector>
#include <iostream>
#include <map>


#ifndef BENCODEELEMENT_H
#define BENCODEELEMENT_H


//A Class to Handle Different Types of Bencode Elements
class bencodeelement;
typedef std::variant<int, std::string, std::vector <unsigned char>, std::vector<bencodeelement>, std::map<std::string, bencodeelement>> bencodevariant;

class bencodeelement {
private: 
    bencodevariant value; 

public: 

    bencodeelement() = default;
    //list of constructors 
    bencodeelement(int val) : value(val) {}
    bencodeelement(std::string val) : value(val) {}
    bencodeelement(std::vector<bencodeelement> val) : value(val) {}
    bencodeelement(std::map<std::string, bencodeelement> val) : value(val) {}
    bencodeelement(std::vector<unsigned char> val) : value(val) {}

    //some checking methods
    bool is_int();
    bool is_str();
    bool is_list();
    bool is_dict();
    bool is_binary();

    //some getting methods
    std::string get_string();
    int get_int();
    std::vector<bencodeelement> get_list();
    std::map<std::string, bencodeelement> get_dict();
    std::vector<unsigned char> get_binary();
};


#endif //BENCODEELEMENT_H