#include <list>

#include "manager.h"

picture_ptr Manager::create_picture(std::string name, std::string pathname, uint32_t width, uint32_t height)
{
    picture_ptr picture = Picture::new_shared(name, pathname, width, height);
    this->medias[name] = picture;
    return picture;
}

video_ptr Manager::create_video(std::string name, std::string pathname, uint32_t duration)
{
    video_ptr video = Video::new_shared(name, pathname, duration);
    this->medias[name] = video;
    return video;
}

movie_ptr Manager::create_movie(std::string name, std::string pathname, uint32_t duration, uint32_t *chapters, uint32_t chaptersLength)
{
    movie_ptr movie = Movie::new_shared(name, pathname, duration, chapters, chaptersLength);
    this->medias[name] = movie;
    return movie;
}

group_ptr Manager::create_group(std::string name)
{
    group_ptr group = Group::new_shared(name);
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

void Manager::delete_group(std::string name)
{
    auto group = this->groups.find(name);

    if (group == this->groups.end())
        return;

    std::list<std::string> media_names;
    for (auto item = group->second->begin(); item != group->second->end(); item++)
        media_names.push_back((*item)->getName());

    for (auto media_name : media_names)
        group->second->remove_if([media_name](media_ptr media)
                                 { return media_name == media->getName(); });

    this->groups.erase(name);
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

std::list<std::string> Manager::list_media() const
{
    std::list<std::string> media_names;
    for (auto &media : this->medias)
        media_names.push_back(media.first);

    return media_names;
}

std::list<std::string> Manager::list_group() const
{
    std::list<std::string> group_names;
    for (auto &group : this->groups)
        group_names.push_back(group.first);

    return group_names;
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
