
#include <istream>

#include "deserializer.h"

void deserializer(std::istream &data, symboles_map &symboles)
{
    std::string line;
    std::string symbole;
    std::string class_name;
    std::list<std::string> symbole_data;

    while (std::getline(data, line))
    {
        if (line.empty())
            continue;

        if (line[0] == ':')
        {
            if (!symbole.empty())
                symboles[symbole] = {class_name, symbole_data, nullptr};

            symbole = line.substr(1);
            symbole_data.clear();
            class_name.clear();
        }
        else if (line[0] == '-')
        {
            if (class_name.empty())
                class_name = line.substr(1);
            else
                symbole_data.push_back(line.substr(1));
        }
    }
    if (!symbole.empty())
        symboles[symbole] = {class_name, symbole_data, nullptr};
}
