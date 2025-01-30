
#include <string>
#include <iostream>
#include <stdint.h>
#include <algorithm>

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
}

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

void Movie::serialize(symboles_map &symboles) const
{
    if (symboles.end() != symboles.find(this->getSymbole()))
        return;

    serde_data_t data;

    data.class_name = "Movie";
    data.data.push_back(this->getName());
    data.data.push_back(this->getPathname());
    data.data.push_back(std::to_string(this->getDuration()));
    data.data.push_back(std::to_string(this->chaptersLength));

    std::stringstream ss;
    for (size_t i = 0; i < this->chaptersLength; i++)
    {
        if (i != 0)
            ss << ' ';
        ss << this->chapters[i];
    }
    data.data.push_back(ss.str());

    symboles[this->getSymbole()] = data;
}

std::string Movie::getSymbole() const
{
    auto name = this->getName();
    std::replace(name.begin(), name.end(), ' ', '_');

    return std::string("movie_") + name;
}

void Movie::deserialize(serde_data_t serde_data, symboles_map symboles)
{
    if (serde_data.class_name != "Movie")
        throw WrongClass("Movie", serde_data.class_name);

    if (serde_data.data.size() != 5)
        throw NotEnoughData("Movie", 5, serde_data.data.size());

    auto it = serde_data.data.begin();
    
    std::string name = *it;
    std::string pathname = *++it;
    uint32_t duration, chaptersLength;

    try
    {
        duration = std::stoi(*++it);
    }
    catch (const std::exception &e)
    {
        throw CanNotInterpretData("Movie", "uint32_t", *it);
    }

    try
    {
        chaptersLength = std::stoi(*++it);
    }
    catch (const std::exception &e)
    {
        throw CanNotInterpretData("Movie", "uint32_t", *it);
    }

    uint32_t *chapters = new uint32_t[chaptersLength];

    std::stringstream ss(*++it);
    for (size_t i = 0; i < chaptersLength; i++)
    {
        std::string chapter;
        std::getline(ss, chapter, ' ');

        try
        {
            chapters[i] = std::stoi(chapter);
        }
        catch (const std::exception &e)
        {
            throw CanNotInterpretData("Movie", "uint32_t", chapter);
        }
    }

    this->setName(name);
    this->setPathname(pathname);
    this->setDuration(duration);
    this->setChapters(chapters, chaptersLength);
}
