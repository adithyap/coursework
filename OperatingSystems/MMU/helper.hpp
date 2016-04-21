#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
#include <sstream>
#include <vector>

class Helper
{
public:
    static std::vector<std::string> &split(const std::string&, char, std::vector<std::string>&);
    static std::vector<std::string> split(const std::string&, char);
};

#endif // HELPER_HPP
