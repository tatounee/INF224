
#ifndef INF224_MOVIE_H
#define INF224_MOVIE_H

#include <string>
#include <iostream>
#include <stdint.h>

#include "video.h"

class Movie : public Video
{
public:
    uint32_t *chapters{};
    size_t chaptersLength{};

public:
    Movie() {};
    Movie(
        std::string name,
        std::string pathname,
        uint32_t duration,
        uint32_t *chapters,
        uint32_t chaptersLength) : Video(name, pathname, duration)
    {
        this->setChapters(chapters, chaptersLength);
    };

    ~Movie()
    {
        if (this->chapters)
            delete[] this->chapters;
    }


    const uint32_t *getChapters() const { return this->chapters; };
    uint32_t getChaptersLength() const { return this->chaptersLength; };

    void setChapters(const uint32_t *chapters, uint32_t chaptersLength);

    void display(std::ostream &sout) const;
};

#endif
