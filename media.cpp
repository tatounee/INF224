
#include "media.h"

#include <string>
#include <iostream>

Media::Media(std::string name, std::string pathname)
{
    this->name = name;
    this->pathname = pathname;
}

std::string Media::getName() const
{
    return this->name;
}

std::string Media::getPathname() const
{
    return this->pathname;
}

void Media::setName(std::string name)
{
    this->name = name;
}

void Media::setPathname(std::string pathname)
{
    this->pathname = pathname;
}

void Media::display(std::ostream & sout) const {
    sout << "[Media]" << std::endl
        << "\tname: \"" << this->name << "\"\n"
        << "\tpathname: \"" << this->pathname << "\"\n";
}
