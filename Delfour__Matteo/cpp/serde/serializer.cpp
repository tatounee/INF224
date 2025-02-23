
#include <ostream>
#include <sstream>
#include "serializer.h"

void serializer(std::ostream &sout, symboles_map &symboles)
{
    for (auto &symbole : symboles)
    {
        sout << ':' << symbole.first << std::endl;
        sout << '-' << symbole.second.class_name << std::endl;
        for (auto &data : symbole.second.data)
        {
            sout << '-' << data << std::endl;
        }
    }
}
