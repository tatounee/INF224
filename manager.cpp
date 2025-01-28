#include <list>
#include <string>
#include <fstream>
#include <iostream>

#include "manager.h"
#include "serde.h"

#define TMP_KEY std::string("tmp-195a12a9-a5ab-40c1-a382-332102174f91")

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

std::string Manager::serialize(symboles_list &symboles) const
{
    if (symboles.end() != std::find(symboles.begin(), symboles.end(), MANAGER_SYMB))
        return std::string();
    symboles.push_back(MANAGER_SYMB);

    std::stringstream ss;
    std::stringstream group_media_ss;

    ss << ":" << MANAGER_SYMB << std::endl;
    ss << "-Manager" << std::endl;
    ss << "-";

    int i = 0;
    for (auto &group : this->groups)
    {
        if (i++ > 0)
            ss << ",";
        ss << group.second->getSymbole();

        group_media_ss << group.second->serialize(symboles);
    }

    ss << std::endl;
    ss << "-";

    i = 0;
    for (auto &media : this->medias)
    {
        if (i++ > 0)
            ss << ",";
        ss << media.second->getSymbole();

        group_media_ss << media.second->serialize(symboles);
    }

    ss << std::endl;

    ss << group_media_ss.str();

    return ss.str();
}

void Manager::save(std::string filename) const
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Could not open file \"" << filename << "\"." << std::endl;
        return;
    }

    symboles_list symboles;
    file << this->serialize(symboles);

    file.close();
}

void Manager::deserialize(std::list<std::string> data, symbole_map symboles)
{
    auto it = data.begin();
    std::string group_list = *it++;
    std::string media_list = *it++;

    std::string name;

    std::stringstream media_ss(media_list);
    std::getline(media_ss, name, ',');
    while (name != "")
    {
        serde_data_t symbole_data = symboles[name];

        if (symbole_data.initialized_ptr != nullptr)
        {
            std::shared_ptr<Media> *media = (std::shared_ptr<Media> *)symbole_data.initialized_ptr;
            this->medias[name] = *media;
        }
        else
        {
            media_ptr media;

            if (symbole_data.class_name == "Picture")
                media = this->create_picture(TMP_KEY, {}, {}, {});
            else if (symbole_data.class_name == "Video")
                media = this->create_video(TMP_KEY, {}, {});
            else if (symbole_data.class_name == "Movie")
                media = this->create_movie(TMP_KEY, {}, {}, {}, {});

            (*media).deserialize(symbole_data.data, symboles);
            this->medias.erase(TMP_KEY);
            this->medias[media->getName()] = media;

            // symboles[name].initialized_ptr = (void *)&media;
            symbole_data.initialized_ptr = (void*)(&this->medias[media->getName()]);
            symboles[name] = symbole_data;
        }

        name.clear();
        std::getline(media_ss, name, ',');
    }

    std::stringstream groups_ss(group_list);
    std::getline(groups_ss, name, ',');
    while (name != "")
    {
        serde_data_t symbole_data = symboles[name];

        if (symbole_data.initialized_ptr != nullptr)
        {
            std::shared_ptr<Group> *group = (std::shared_ptr<Group> *)symbole_data.initialized_ptr;
            this->groups[name] = *group;
        }
        else
        {
            group_ptr group = this->create_group(name);
            (*group).deserialize(symbole_data.data, symboles);
            this->groups.erase(name);
            this->groups[group->getName()] = group;

            symbole_data.initialized_ptr = (void *)&group;
        }

        name.clear();
        std::getline(groups_ss, name, ',');
    }
}

void Manager::load(const std::string filename)
{
    std::ifstream file = std::ifstream(filename);

    if (!file.is_open())
    {
        std::cerr << "Could not open file \"" << filename << "\"." << std::endl;
        return;
    }

    symbole_map symboles = parse_symboles(file);
    // print_symboles_map(symboles);
    this->deserialize(symboles[MANAGER_SYMB].data, symboles);

    file.close();
}
