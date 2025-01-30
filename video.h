
#ifndef INF224_PICTURE_H
#define INF224_PICTURE_H

#include <string>
#include <stdint.h>
#include <iostream>
#include <algorithm>

#include "media.h"

class Manager;

/// @brief Représente une vidéo, avec un nom, un fichier associé et une durée.
class Video : public Media
{
    friend class Manager;

private:
    uint32_t duration{};

protected:
    /// @brief Constructeur par défaut.
    Video() {};

    /// @brief Constructeur avec paramètres.
    /// @param name Le nom de la vidéo.
    /// @param pathname Le chemin du fichier associé.
    /// @param duration La durée de la vidéo.
    Video(std::string name,
          std::string pathname,
          uint32_t duration) : Media(name, pathname),
                               duration{duration} {};

    static std::shared_ptr<Video> new_shared(std::string name, std::string pathname, uint32_t duration)
    {
        struct NonProtectedVideo : public Video
        {
        public:
            NonProtectedVideo(std::string name, std::string pathname, uint32_t duration) : Video(name, pathname, duration) {}
        };

        return std::static_pointer_cast<Video>(std::make_shared<NonProtectedVideo>(name, pathname, duration));
    }

public:
    uint32_t getDuration() const { return this->duration; };
    void setDuration(uint32_t duration) { this->duration = duration; };

    /// @brief Affiche les informations de la vidéo.
    void display(std::ostream &sout) const
    {
        sout << "[Video]" << std::endl
             << "\tname: \"" << this->getName() << "\"\n"
             << "\tpathname: \"" << this->getPathname() << "\"\n"
             << "\tduration: \"" << this->duration << "\"\n";
    }

    /// @brief Joue la vidéo avec `mpv`.
    void play() const override
    {
        std::string cmd = std::string("mpv ");
        cmd += this->getPathname();
        cmd += " &";

        system(cmd.data());
    }

    void serialize(symboles_map &symboles) const override
    {
        if (symboles.end() != symboles.find(this->getSymbole()))
            return;

        serde_data_t data;

        data.class_name = "Video";
        data.data.push_back(this->getName());
        data.data.push_back(this->getPathname());
        data.data.push_back(std::to_string(this->duration));

        symboles[this->getSymbole()] = data;
    };

    std::string getSymbole() const override
    {
        auto name = this->getName();
        std::replace(name.begin(), name.end(), ' ', '_');

        return std::string("video_") + name;
    };

    void deserialize(serde_data_t serde_data, symboles_map symboles) override
    {
        if (serde_data.class_name != "Video")
            throw WrongClass("Video", serde_data.class_name);

        if (serde_data.data.size() != 3)
            throw NotEnoughData("Video", 3, serde_data.data.size());

        auto it = serde_data.data.begin();

        std::string name = *it;
        std::string pathname = *++it;
        uint32_t duration;

        try
        {
            duration = std::stoi(*++it);
        }
        catch (const std::exception &e)
        {
            throw CanNotInterpretData("Video", "uint32_t", *it);
        }

        this->setName(name);
        this->setPathname(pathname);
        this->setDuration(duration);
    }
};

#endif
