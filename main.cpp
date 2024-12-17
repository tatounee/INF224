
#include <iostream>

#include "manager.h"

using MediaPtr = std::shared_ptr<Media>;


int main()
{
    Manager manager;

    manager.create_video("video", "/path/to/video/", 30);

    manager.delete_media("trololo");

    return 0;
}
