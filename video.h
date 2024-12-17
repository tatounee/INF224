
#ifndef INF224_PICTURE_H
#define INF224_PICTURE_H

#include <stdint.h>
#include <iostream>

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
};

#endif
