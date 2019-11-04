#pragma once

#include <string>
#include <fstream>
#include <tuple>
#include <vector>

#include <iostream>
#include <sstream>

#include "str.h"

template<typename... T>
class csv
{

public:
    std::vector<std::tuple<T...>> data;
    std::vector<std::string> header;
    char delim=',';

    void read(std::ifstream& file)
    {
        std::string line;
        size_t t = sizeof...(T);
        while (std::getline(file, line))
        {
            auto sub = split(line, delim);
            int index = sub.size()-1;
            // here use index from largest to smallest,
            // because tuple construct is a kind of recursive expansion
            // the last will be evaluated first
            data.push_back(std::make_tuple(read_element<T>(sub[index--])...));
        }
    }

    void write(std::ofstream& file)
    {
        if (header.size() != 0)
        {
            
        }
    }

private:
    std::stringstream ss;

    template <typename Ty>
    Ty read_element(const std::string& input)
    {
        ss.clear();
        ss.str("");
        ss << input;
        Ty value;
        ss >> value;
        return value;
    }

    template< >
    std::string read_element<std::string>(const std::string& val)
    {
        return val;
    }
};
