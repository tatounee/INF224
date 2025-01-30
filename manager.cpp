#include <list>
#include <string>
#include <fstream>
#include <iostream>

#include "manager.h"
#include "serde.h"
#include "serializer.h"
#include "deserializer.h"

#define TMP_KEY std::string("tmp-195a12a9-a5ab-40c1-a382-332102174f91")

picture_ptr Manager::create_picture(std::string name, std::string pathname, uint32_t width, uint32_t height)
{
    auto media = this->medias.find(name);
    if (media != this->medias.end())
        throw NameAlreadyTaken(name);

    picture_ptr picture = Picture::new_shared(name, pathname, width, height);
    this->medias[name] = picture;
    return picture;
}

video_ptr Manager::create_video(std::string name, std::string pathname, uint32_t duration)
{
    auto media = this->medias.find(name);
    if (media != this->medias.end())
        throw NameAlreadyTaken(name);

    video_ptr video = Video::new_shared(name, pathname, duration);
    this->medias[name] = video;
    return video;
}

movie_ptr Manager::create_movie(std::string name, std::string pathname, uint32_t duration, uint32_t *chapters, uint32_t chaptersLength)
{
    auto media = this->medias.find(name);
    if (media != this->medias.end())
        throw NameAlreadyTaken(name);

    movie_ptr movie = Movie::new_shared(name, pathname, duration, chapters, chaptersLength);
    this->medias[name] = movie;
    return movie;
}

group_ptr Manager::create_group(std::string name)
{
    auto group_ = this->groups.find(name);
    if (group_ != this->groups.end())
        throw NameAlreadyTaken(name);

    group_ptr group = Group::new_shared(name);
    this->groups[name] = group;
    return group;
}

manager_error Manager::delete_media(std::string name)
{
    auto deleted = this->medias.erase(name);
    if (deleted == 0)
        return manager_error::MEDIA_NOT_FOUND;

    for (auto &group : this->groups)
        group.second->remove_if([name](media_ptr media)
                                { return name == media->getName(); });

    return manager_error::NONE;
}

manager_error Manager::delete_group(std::string name)
{
    auto group = this->groups.find(name);

    if (group == this->groups.end())
        return manager_error::GROUP_NOT_FOUND;

    std::list<std::string> media_names;
    for (auto item = group->second->begin(); item != group->second->end(); item++)
        media_names.push_back((*item)->getName());

    for (auto media_name : media_names)
        group->second->remove_if([media_name](media_ptr media)
                                 { return media_name == media->getName(); });

    this->groups.erase(name);

    return manager_error::NONE;
}

manager_error Manager::display_media(std::string name, std::ostream &sout) const
{
    auto media = this->medias.find(name);
    if (media == this->medias.end())
        return manager_error::MEDIA_NOT_FOUND;

    media->second->display(sout);

    return manager_error::NONE;
}

manager_error Manager::display_group(std::string name, std::ostream &sout) const
{
    auto group = this->groups.find(name);
    if (group == this->groups.end())
        return manager_error::GROUP_NOT_FOUND;

    group->second->display(sout);

    return manager_error::NONE;
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

manager_error Manager::play_media(std::string name) const
{
    auto media = this->medias.find(name);
    if (media == this->medias.end())
        return manager_error::MEDIA_NOT_FOUND;

    media->second->play();

    return manager_error::NONE;
}

void Manager::serialize(symboles_map &symboles) const
{
    if (symboles.end() != symboles.find(MANAGER_SYMB))
        return;

    serde_data_t data;

    data.class_name = "Manager";

    int i = 0;
    std::stringstream media_ss;
    for (auto &media : this->medias)
    {
        if (i++ > 0)
            media_ss << ' ';
        media_ss << media.second->getSymbole();

        media.second->serialize(symboles);
    }
    data.data.push_back(media_ss.str());

    i = 0;
    std::stringstream groups_ss;
    for (auto &group : this->groups)
    {
        if (i++ > 0)
            groups_ss << ' ';
        groups_ss << group.second->getSymbole();

        group.second->serialize(symboles);
    }
    data.data.push_back(groups_ss.str());

    symboles[MANAGER_SYMB] = data;
}

void Manager::deserialize(serde_data_t serde_data, symboles_map symboles)
{
    if (serde_data.class_name != "Manager")
        throw WrongClass("Manager", serde_data.class_name);

    if (serde_data.data.size() != 2)
        throw NotEnoughData("Manager", 2, serde_data.data.size());

    auto it = serde_data.data.begin();

    Manager tmp_manager;

    std::string name;

    std::stringstream media_ss(*it++);
    std::getline(media_ss, name, ' ');
    while (name != "")
    {
        if (symboles.find(name) == symboles.end())
            throw UndefinedSymbole(name);

        serde_data_t symbole_data = symboles[name];

        if (symbole_data.initialized_ptr != nullptr)
        {
            std::shared_ptr<Media> *media = (std::shared_ptr<Media> *)symbole_data.initialized_ptr;
            tmp_manager.medias[name] = *media;
        }
        else
        {
            media_ptr media;

            if (symbole_data.class_name == "Picture")
                media = tmp_manager.create_picture(TMP_KEY, {}, {}, {});
            else if (symbole_data.class_name == "Video")
                media = tmp_manager.create_video(TMP_KEY, {}, {});
            else if (symbole_data.class_name == "Movie")
                media = tmp_manager.create_movie(TMP_KEY, {}, {}, {}, {});
            else
                throw WrongClass("Picture, Video or Movie", symbole_data.class_name);

            tmp_manager.medias.erase(TMP_KEY);

            (*media).deserialize(symbole_data, symboles);
            tmp_manager.medias.erase(TMP_KEY);
            tmp_manager.medias[media->getName()] = media;

            tmp_manager.medias[media->getName()] = media;

            symbole_data.initialized_ptr = (void *)(&tmp_manager.medias[media->getName()]);
            symboles[name] = symbole_data;
        }

        name.clear();
        std::getline(media_ss, name, ' ');
    }

    std::stringstream groups_ss(*it++);
    std::getline(groups_ss, name, ' ');
    while (name != "")
    {
        if (symboles.find(name) == symboles.end())
            throw UndefinedSymbole(name);

        serde_data_t symbole_data = symboles[name];

        if (symbole_data.initialized_ptr != nullptr)
        {
            std::shared_ptr<Group> *group = (std::shared_ptr<Group> *)symbole_data.initialized_ptr;
            tmp_manager.groups[name] = *group;
        }
        else
        {
            group_ptr group = tmp_manager.create_group(name);
            (*group).deserialize(symbole_data, symboles);
            tmp_manager.groups.erase(name);
            tmp_manager.groups[group->getName()] = group;

            symbole_data.initialized_ptr = (void *)&group;
        }

        name.clear();
        std::getline(groups_ss, name, ' ');
    }

    this->medias = tmp_manager.medias;
    this->groups = tmp_manager.groups;
}

manager_error Manager::save(std::string filename) const
{
    std::ofstream file(filename);

    if (!file.is_open())
        return manager_error::UNABLE_TO_OPEN_FILE;

    symboles_map symboles;
    this->serialize(symboles);

    serializer(file, symboles);

    file.close();

    return manager_error::NONE;
}

manager_error Manager::load(const std::string filename)
{
    std::ifstream file = std::ifstream(filename);

    if (!file.is_open())
        return manager_error::UNABLE_TO_OPEN_FILE;

    symboles_map symboles;
    deserializer(file, symboles);
    // print_symboles_map(symboles);

    this->deserialize(symboles[MANAGER_SYMB], symboles);

    file.close();

    return manager_error::NONE;
}
