
#ifndef INF224_MANAGER_H
#define INF224_MANAGER_H

#include <string>
#include <memory>
#include <map>

#include "picture.h"
#include "video.h"
#include "movie.h"
#include "group.h"

using media_dict = std::map<std::string, std::shared_ptr<Media>>;
using group_dict = std::map<std::string, std::shared_ptr<Group>>;

using media_ptr = std::shared_ptr<Media>;
using picture_ptr = std::shared_ptr<Picture>;
using video_ptr = std::shared_ptr<Video>;
using movie_ptr = std::shared_ptr<Movie>;
using group_ptr = std::shared_ptr<Group>;

class Manager
{
private:
    media_dict medias{};
    group_dict groups{};

public:
    Manager() : medias(media_dict()), groups(group_dict()) {};

    picture_ptr create_picture(std::string name, std::string pathname, uint32_t width, uint32_t height);
    video_ptr create_video(std::string name, std::string pathname, uint32_t duration);
    movie_ptr create_movie(std::string name, std::string pathname, uint32_t duration, uint32_t *chapters, uint32_t chaptersLength);
    group_ptr create_group(std::string name);

    void delete_media(std::string name);

    void display_media(std::string name, std::ostream &sout) const;
    void display_group(std::string name, std::ostream &sout) const;

    void play_media(std::string name) const;
};

#endif
