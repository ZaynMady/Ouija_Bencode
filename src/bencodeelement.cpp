#include "bencodeelement.h"
#include <string> 
#include <iostream> 
#include <vector> 
#include <map>
#include <variant> 
#include <typeinfo>
#include <fstream>
#include <sstream>


//Returns True if the Bencode Element is of Type INT
bool bencodeelement::is_int()
{
    return std::holds_alternative<int>(value);
}
//Returns True if the Bencode Element is of Type std string_literal
bool bencodeelement::is_str()
{
    return std::holds_alternative<std::string>(value);
}
//returns True if the Bencode Element is a List
bool bencodeelement::is_list()
{
        return std::holds_alternative<std::vector<bencodeelement>>(value);
}
//returns True if the Bencode Element is a Dictionary
bool bencodeelement::is_dict()
{
        return std::holds_alternative<std::map<std::string, bencodeelement>>(value);
}
// Returns the Value if it is a String, otherwise throws a runtime error
bool bencodeelement::is_binary()
{
        return std::holds_alternative<std::vector<unsigned char>>(value);
}
std::string bencodeelement::get_string()
{
        if(std::holds_alternative<std::string>(value))
        {
            return std::get<std::string>(value);
        }
        else
        {
            throw std::runtime_error("Incorrent Type, the Value is Not a String");
        }
}
//Returns the Value if it is an  Int, otherwise throws a runtime error
int bencodeelement::get_int()
{
    if(std::holds_alternative<int>(value))
    {
        return std::get<int>(value);
    }
    else
    {
        throw std::runtime_error("Incorrent Type, the Value is Not a Integer");
    }
}
//returns the value if it is a List(Vector), Otherwise throws a runtime error
std::vector<bencodeelement> bencodeelement::get_list()
{
        {
        if(std::holds_alternative<std::vector<bencodeelement>>(value))
        {
        return std::get<std::vector<bencodeelement>>(value);
        }
        else
        {
            throw std::runtime_error("Incorrent Type, the Value is Not a List");
        }
}
}
// returns the value if it is a dict(map), otherwise throws a runtime error
std::map<std::string, bencodeelement> bencodeelement::get_dict()
{
        if(std::holds_alternative<std::map<std::string, bencodeelement>>(value))
        {
            return std::get<std::map<std::string, bencodeelement>>(value);
        }
        else
        {
            throw std::runtime_error("Incorrent Type, the Value is Not a Dictionary");
        }
}
std::vector<unsigned char> bencodeelement::get_binary()
{
    return std::get<std::vector<unsigned char>>(value);
}