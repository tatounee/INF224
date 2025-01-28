
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

    std::string serialize(symboles_list &symboles) const override
    {
        if (symboles.end() != std::find(symboles.begin(), symboles.end(), this->getSymbole()))
            return std::string();

        symboles.push_back(this->getSymbole());

        std::stringstream ss;

        ss << ":" << this->getSymbole() << std::endl;
        ss << "-Video" << std::endl;
        ss << "-" << this->getName() << std::endl;
        ss << "-" << this->getPathname() << std::endl;
        ss << "-" << this->duration << std::endl;

        return ss.str();
    };

    std::string getSymbole() const override
    {
        return std::string("video_") + this->getName();
    };

    void deserialize(std::list<std::string> data, symbole_map symboles) override {
        auto it = data.begin();
        this->setName(*it++);
        this->setPathname(*it++);
        this->setDuration(std::stoi(*it++));
    }
};

#endif
