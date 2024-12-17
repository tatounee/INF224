
#include <string>
#include <iostream>
#include <stdint.h>

#include "movie.h"
#include "video.h"

Movie::Movie(const Movie &from) : Video(from)
{
    if (from.chaptersLength == 0)
        return;

    this->chaptersLength = from.chaptersLength;
    this->chapters = new uint32_t[this->chaptersLength];

    for (size_t i = 0; i < this->chaptersLength; i++)
        this->chapters[i] = from.getChapters()[i];
}

Movie &Movie::operator=(const Movie &from)
{
    Video::operator=(from);

    Movie temp(from);

    std::swap(this->chaptersLength, temp.chaptersLength);
    std::swap(this->chapters, temp.chapters);

    return *this;
}

void Movie::setChapters(const uint32_t *chapters, uint32_t chaptersLength)
{
    if (this->chapters)
    {
        delete[] this->chapters;
        this->chapters = nullptr;
        this->chaptersLength = 0;
    }

    if (chaptersLength == 0)
        return;

    this->chapters = new uint32_t[chaptersLength];
    this->chaptersLength = chaptersLength;

    for (size_t i = 0; i < chaptersLength; i++)
        this->chapters[i] = chapters[i];
};

void Movie::display(std::ostream &sout) const
{
    sout << "[Movie]" << std::endl
         << "\tname: \"" << this->getName() << "\"\n"
         << "\tpathname: \"" << this->getPathname() << "\"\n"
         << "\tduration: " << this->getDuration() << std::endl
         << "\tchapters: [";

    for (size_t i = 0; i < this->chaptersLength; i++)
    {
        if (i != 0)
            sout << ", ";
        sout << this->chapters[i];
    }
    sout << "]" << std::endl;
};
