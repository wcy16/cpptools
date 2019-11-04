#include "str.h"

std::vector<std::string> split(const std::string& s, char delim, int times)
{
    std::vector<std::string> ret;
    if (times > 0) 
    {
        ret.reserve(times);
    }
    size_t pos1 = 0;
    size_t pos2 = 0;
    for (; times != 0; times--) 
    {
        pos2 = s.find(delim, pos1);
        if (pos2 == std::string::npos) 
        {
            ret.push_back(s.substr(pos1));
            break;
        }
        ret.push_back(s.substr(pos1, pos2));
        pos1 = pos2 + 1;
    }
    return ret;
}