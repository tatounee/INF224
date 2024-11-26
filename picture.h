
#ifndef INF224_VIDEO_H
#define INF224_VIDEO_H

#include <stdint.h>
#include <iostream>

#include "media.h"

class Picture : public Media
{
private:
    uint32_t width{};
    uint32_t height{};

public:
    Picture() {};
    Picture(std::string name, std::string pathname, uint32_t width, uint32_t height) : Media(name, pathname)
    {
        this->width = width;
        this->height = height;
    };

    uint32_t getWidth() { return this->width; };
    uint32_t getHeight() { return this->height; };

    void setWidth(uint32_t width) { this->width = width; };
    void setHeight(uint32_t height) { this->height = height; };

    void display(std::ostream &sout) const
    {
        sout << "[Picture]" << std::endl
             << "\tname: \"" << this->getName() << "\"\n"
             << "\tpathname: \"" << this->getPathname() << "\"\n"
             << "\twidth: \"" << this->width << "\"\n"
             << "\theight: \"" << this->height << "\"\n";
    }

    void play() {
        std::string cmd = std::string("imagej ");
        cmd += this->getPathname();
        cmd += " &";

        system(cmd.data());
    }
};

#endif
