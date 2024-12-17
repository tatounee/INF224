
#ifndef INT224_GROUP_H
#define INT224_GROUP_H

#include <list>

#include "media.h"

class Group : public std::list<Media *>
{
private:
    std::string name{};

public:
    Group() : name(std::string()) {};
    Group(std::string name) : name{name} {};

    std::string getName() const { return this->name; };
    void setName(std::string name) { this->name = name; };

    void display(std::ostream &sout) const
    {
        sout << "[Group]" << std::endl
             << "\tname: \"" << this->name << "\"\n"
             << "\tmedias: [\n";

        for (auto &media : *this)
        {
            media->display(sout);
        }

        sout << "]" << std::endl;
    };
};

#endif
