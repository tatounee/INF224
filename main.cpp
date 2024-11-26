
#include "media.h"
#include "picture.h"
#include "video.h"

int main()
{
    Picture *pic = new Picture(
        std::string("Imagination"),
        std::string("/home/tatoune/Pictures/imagination.jpg"),
        1920,
        1080);

    Video *vid = new Video(
        std::string("TMS"),
        std::string("/home/tatoune/Videos/Screencasts/tsm.mp4"),
        35);

    Media *medias[] = {
        pic,
        vid};

    for (size_t i = 0; i < 2; i++)
        medias[i]->play();

    return 0;
}
