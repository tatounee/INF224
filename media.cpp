
#include "media.h"

#include <string>
#include <iostream>

Media::Media(std::string name, std::string pathname)
{
    this->name = name;
    this->pathname = pathname;
}

void Media::display(std::ostream &sout) const
{
    sout << "[Media]" << std::endl
         << "\tname: \"" << this->name << "\"\n"
         << "\tpathname: \"" << this->pathname << "\"\n";
}
