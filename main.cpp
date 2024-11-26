
#include <iostream>

#include "movie.h"

int main()
{
    uint32_t chapters[] = {0, 10, 17, 23};

    Movie *mov = new Movie(
        std::string("TMS"),
        std::string("/home/tatoune/Videos/Screencasts/tsm.mp4"),
        35,
        chapters,
        4);

    mov->display(std::cout);

    uint32_t *newChapters = new uint32_t[2]{42, 666};

    mov->setChapters(newChapters, 2);
    mov->display(std::cout);

    delete[] newChapters;
    mov->display(std::cout);

    return 0;
}
