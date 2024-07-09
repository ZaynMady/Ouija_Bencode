#include "encoder.h"

std::vector<unsigned char> ouija::encode_str(std::string &decoded_data)

{
    std::vector<unsigned char> encoded_data;
    std::string string_size = std::to_string(decoded_data.size());
    for (int i = 0; i < string_size.size(); i++ )
    {
        encoded_data.push_back(string_size[i]);
    }
    encoded_data.push_back(':');
    //encoding the string itself 
    for (int i = 0; i < decoded_data.size(); i++)
    {
        encoded_data.push_back(decoded_data[i]);
    }
    return encoded_data;
}

std::vector<unsigned char> ouija::encode_int(int &decoded_data)
{
    std::vector<unsigned char> encoded_data; 

    encoded_data.push_back('i');

    for (auto _char : std::to_string(decoded_data))
    {
        encoded_data.push_back(_char);
    }

    encoded_data.push_back('e');
    return std::vector<unsigned char>(encoded_data);
}

std::vector<unsigned char> ouija::encode_binary(std::vector<unsigned char> &decoded_data)
{
    std::vector<unsigned char> encoded_data;
    std::string string_size = std::to_string(decoded_data.size());
    for (int i = 0; i < string_size.size(); i++ )
    {
        encoded_data.push_back(string_size[i]);
    }
    encoded_data.push_back(':');
    //encoding the string itself 
    for (int i = 0; i < decoded_data.size(); i++)
    {
        encoded_data.push_back(decoded_data[i]);
    }
    return encoded_data;

    return std::vector<unsigned char>(encoded_data);
}

std::vector<unsigned char> ouija::encode_list(std::vector<bencodeelement> &decoded_data)
{
    std::vector<unsigned char> encoded_data;

    encoded_data.push_back('l');

    for ( auto elem : decoded_data)
    {
        if (elem.is_str())
        {
            auto str = elem.get_string();
            for (const auto _char : encode_str(str))
            {
                encoded_data.push_back(_char);
            }
        }
        else if (elem.is_int())
        {
            //getting the integer value of the element
            auto integer = elem.get_int();

            //iterating over it's encoded value to add each unsigned char individually to the greater bencoded list
            for (const auto _char : encode_int(integer))
            {
                encoded_data.push_back(_char);
            }
        }
        else if (elem.is_list())
        {
            //getting the list value of the element
            auto integer = elem.get_list();

            //iterating over it's encoded value to add each unsigned char individually to the greater bencoded list
            for (const auto _char : encode_list(integer))
            {
                encoded_data.push_back(_char);
            }
        }
        else if (elem.is_dict())
        {
            auto dict = elem.get_dict();

            for (const auto _char : encode_dict(dict))
            {
                encoded_data.push_back(_char);
            }
        }
    }

    //closing the list with an 'e'
    encoded_data.push_back('e');

    //returning the new bencoded data
    return std::vector<unsigned char>(encoded_data);
}

std::vector<unsigned char> ouija::encode_dict(std::map<std::string, bencodeelement> &decoded_data)
{
    std::vector<unsigned char> encoded_data;
    //adding the d token to declare start of the dictionary 
    encoded_data.push_back('d');

    for (auto it: decoded_data)
    {
        //adding the key
        std::string str_key = it.first;
        std::vector<unsigned char> key = encode_str(str_key);

        for(auto elem: key)
        {
            encoded_data.push_back(elem);
        }

        //adding the value 
        if(it.second.is_binary())
        {
            auto bin_value = it.second.get_binary();
            std::vector<unsigned char>value = encode_binary(bin_value);

            for(auto elem : value)
            {
                encoded_data.push_back(elem);
            }
        }
        else if(it.second.is_str())
        {
            auto str_value = it.second.get_string();
            std::vector<unsigned char>value = encode_str(str_value);

            for(auto elem : value)
            {
                encoded_data.push_back(elem);
            }
        }
        else if(it.second.is_int())
        {
            auto int_value = it.second.get_int();
            std::vector<unsigned char>value = encode_int(int_value);

            for(auto elem : value)
            {
                encoded_data.push_back(elem);
            }
        }
        else if(it.second.is_list())
        {
            auto list_value = it.second.get_list();
            std::vector<unsigned char>value = encode_list(list_value);

            for(auto elem : value)
            {
                encoded_data.push_back(elem);
            }
        }
        else if(it.second.is_dict())
        {
            auto dict_value = it.second.get_dict();
            std::vector<unsigned char>value = encode_dict(dict_value);

            for(auto elem : value)
            {
                encoded_data.push_back(elem);
            }
        }
        else{
            std::cerr << "Incorrect BencodeElement Data Type" << std::endl;
        }
    }

    encoded_data.push_back('e');


    //adding the e token to declare end of dictionary
    return std::vector<unsigned char>(encoded_data);
}

std::vector<unsigned char> ouija::encode(std::map<std::string, bencodeelement> &decoded_data)
{
    std::vector<unsigned char> encoded_data; 

    return std::vector<unsigned char>(encoded_data);
}