#include "helper.hpp"

std::vector<std::string> &Helper::split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
    std::stringstream ss(s);
    std::string item;
    
    while (std::getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }

    return elems;
}

std::vector<std::string> Helper::split(const std::string &s, char delim) 
{
    std::vector<std::string> elems;
    Helper::split(s, delim, elems);
    return elems;
}
