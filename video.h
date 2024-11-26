
#ifndef INF224_PICTURE_H
#define INF224_PICTURE_H

#include <stdint.h>
#include <iostream>

#include "media.h"

class Video : public Media
{
private:
    uint32_t duration{};

public:
    Video() {};
    Video(std::string name, std::string pathname, uint32_t duration) : Media(name, pathname)
    {
        this->duration = duration;
    };

    uint32_t getDuration() { return this->duration; };
    void setDuration(uint32_t duration) { this->duration = duration; };

    void display(std::ostream &sout) const
    {
        sout << "[Video]" << std::endl
             << "\tname: \"" << this->getName() << "\"\n"
             << "\tpathname: \"" << this->getPathname() << "\"\n"
             << "\tduration: \"" << this->duration << "\"\n";
    }

    void play()
    {
        std::string cmd = std::string("mpv ");
        cmd += this->getPathname();
        cmd += " &";

        system(cmd.data());
    }
};

#endif
