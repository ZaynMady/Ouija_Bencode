Ouija_Bencode is a C++ project that includes functionalities for decoding Bencode-encoded data and generating info-hash values. This can be particularly useful for working with torrent files.

**What is Bencode?**
Bencode is a simple encoding format used by the BitTorrent protocol for storing and transmitting loosely structured data. Bencoded data can represent strings, integers, lists, and dictionaries.

**Example of Bencoded data:**
d3:cow3:moo4:spam4:eggse
This represents a dictionary with keys "cow" and "spam", and values "moo" and "eggs", respectively.

**What is an Info-Hash?**
An info-hash is a SHA-1 hash of the bencoded form of the info dictionary from a torrent file. It is used to identify torrents uniquely.

How Ouija_Bencode Handles Them
Decoding Bencoded Data
The project includes a decoder that parses Torrent Files and extracts their data into a vector of unsigned char to correctly handle binary data. The decoded data is then written to an info file, including the calculated info-hash.
here is the code for the decode function 
```
      std::map<std::string, bencodeelement> ouija::decode_dict(std::vector<unsigned char> &encoded_data, size_t & position)
      {
    //map
    std::map<std::string, bencodeelement> decoded_element;
    //skip the d
    position++;

    //the key is always a string
    while(encoded_data[position] != 'e')
    {
    std::string key = ouija::decode_str(encoded_data, position);
    if (encoded_data[position] == 'i')
    {
        decoded_element[key] = ouija::decode_int(encoded_data, position);
    }
    else if (encoded_data[position] == 'd')
    {
        decoded_element[key] = ouija::decode_dict(encoded_data, position);
    }
    else if(encoded_data[position] == 'l')
    {
        decoded_element[key] = ouija::decode_list(encoded_data, position);
    }
    else if(isdigit(encoded_data[position]))
    {
        if(key == "pieces")
        {
            decoded_element[key] = ouija::decode_binary(encoded_data, position);
            
        }
        else
        {
            decoded_element[key] = ouija::decode_str(encoded_data, position);
        }
    }
    else
    {
        throw std::runtime_error("Incorrect Bencode Format");
    }
    }
    //skip the e
    position++;
    return decoded_element;
      }
```
You can view how each function decodes it's specific data type in the 

**Handling Bencode Elements**
Considering that the values in the decoded dictionary are variable and different and the std::map must be initialized with specific data types, 
I created a class specified for handling all the bencode elements, from string, int, list, dict and even binary data for the pieces field. I then created the constructor to take any type of those and store it in an std::variant, with a lot of is_type and get_type methods to ease the handling of these data;

**Handling the Info-Hash**
Required by the bittorrent protocol, every torrent file is uniquely identified by it's Info Hash, which is an SHA-1 encoded version of the bencoded "info" dictionary. 
here is a snippet of the encryping info-hash function, which utilizes the openssl library for the SHA-1 encoding and a file created by me which is an encoder that re-encodes decoded data back to bencode format
```
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
```

**How to Use?**

**Install the necessary dependencies which are:**
OPENSSL library using vcpkg 

**Modify the makefile and replace the path to the vcpkg dependies with your own path**

**compile the file using make**

**Run the Program ./ouija with either of two commands, either "Decode" which returns the info file of the meta data in the torrent file or "info-hash" which prints out the info-hash of the torrent file you are gonna provide, followed up by the path of the torrent file**
