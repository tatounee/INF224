
#include "manager.h"

picture_ptr Manager::create_picture(std::string name, std::string pathname, uint32_t width, uint32_t height)
{
    picture_ptr picture = std::make_shared<Picture>(name, pathname, width, height);
    this->medias[name] = picture;
    return picture;
}

video_ptr Manager::create_video(std::string name, std::string pathname, uint32_t duration)
{
    video_ptr video = std::make_shared<Video>(name, pathname, duration);
    this->medias[name] = video;
    return video;
}

movie_ptr Manager::create_movie(std::string name, std::string pathname, uint32_t duration, uint32_t *chapters, uint32_t chaptersLength)
{
    movie_ptr movie = std::make_shared<Movie>(name, pathname, duration, chapters, chaptersLength);
    this->medias[name] = movie;
    return movie;
}

group_ptr Manager::create_group(std::string name)
{
    group_ptr group = std::make_shared<Group>(name);
    this->groups[name] = group;
    return group;
}

void Manager::delete_media(std::string name)
{
    for (auto &group : this->groups)
    {
        group.second->remove_if([name](media_ptr media)
                                { return name == media->getName(); });
    }

    this->medias.erase(name);
}

void Manager::display_media(std::string name, std::ostream &sout) const
{
    auto media = this->medias.find(name);
    if (media == this->medias.end())
    {
        sout << "Media \"" << name << "\" not found." << std::endl;
        return;
    }

    media->second->display(sout);
}

void Manager::display_group(std::string name, std::ostream &sout) const
{
    auto group = this->groups.find(name);
    if (group == this->groups.end())
    {
        sout << "Group \"" << name << "\" not found." << std::endl;
        return;
    }

    group->second->display(sout);
}

void Manager::play_media(std::string name) const
{
    auto media = this->medias.find(name);
    if (media == this->medias.end())
    {
        std::cerr << "Media \"" << name << "\" not found." << std::endl;
        return;
    }

    media->second->play();
}
