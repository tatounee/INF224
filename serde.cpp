
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "serde.h"

void print_symboles_map(symboles_map &symboles)
{
    for (auto &symbole : symboles)
    {
        std::cout << symbole.first;
        std::cout << "\t" << symbole.second.class_name << std::endl;
        for (auto &data : symbole.second.data)
            std::cout << "\t" << data << std::endl;
    }
}
