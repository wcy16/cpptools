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

    void read(std::ifstream& file, bool withHeader=false)
    {
        std::string line;
        if (withHeader)
        {
            std::getline(file, line);
            header = split(line, delim);
        }

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
        // write header
        if (header.size() != 0)
        {
            file << header[0];
            for (int i = 1; i != header.size(); i++)
                file << delim << header[1];
            file << std::endl;
        }

        // write elements
        for (auto& elem : data)
        {
            write_elements(file, elem);
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

    template<>
    std::string read_element<std::string>(const std::string& val)
    {
        return val;
    }

    void write_elements(std::ofstream& file, std::tuple<T...>& elements)
    {
        write_element<0>(file, elements);
    }

    template <size_t N>
    void write_element(std::ofstream& file, std::tuple<T...>& elements)
    {
        file << std::get<N>(elements);
        if (N != std::tuple_size<std::tuple<T...>>::value - 1)
        {
            file << delim;
            write_element<N + 1>(file, elements);
        }
    }

    template <>
    void write_element<std::tuple_size<std::tuple<T...>>::value - 1>(std::ofstream& file, std::tuple<T...>& elements)
    {
        file << std::get<std::tuple_size<std::tuple<T...>>::value - 1>(elements) << std::endl;
    }
};
