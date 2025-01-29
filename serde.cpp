
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "serde.h"

symbole_map parse_symboles(std::istream &data)
{
    symbole_map symboles;

    bool started = false;
    bool new_symbole = false;
    std::string symbole;
    serde_data_t symbole_data;

    std::string line;

    while (std::getline(data, line))
    {
        char c = line[0];

        if (c == ':')
        {
            if (started)
                symboles[symbole] = symbole_data;
            started = true;

            new_symbole = true;
            symbole = line.substr(1);
            symbole_data = serde_data_t();
        }
        else if (c == '-')
        {
            if (new_symbole)
            {
                new_symbole = false;
                symbole_data.class_name = line.substr(1);
            }
            else
                symbole_data.data.push_back(line.substr(1));
        }
    }

    symboles[symbole] = symbole_data;

    return symboles;
}

void print_symboles(symboles_list &symboles)
{
    for (auto &symbole : symboles)
        std::cout << symbole << ' ' << std::endl;
}

void print_symboles_map(symbole_map &symboles)
{
    for (auto &symbole : symboles)
    {
        std::cout << symbole.first;
        std::cout << "\t" << symbole.second.class_name << std::endl;
        for (auto &data : symbole.second.data)
            std::cout << "\t" << data << std::endl;
    }
}
