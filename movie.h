
#ifndef INF224_MOVIE_H
#define INF224_MOVIE_H

#include <string>
#include <iostream>
#include <stdint.h>

#include "video.h"

/// @brief Représente un film, avec un nom, un fichier associé, une durée et des chapitres.
class Movie : public Video
{
public:
    uint32_t *chapters{};
    size_t chaptersLength{};

public:
    /// @brief Constructeur par défaut.
    Movie() {};

    /// @brief Constructeur avec paramètres.
    /// @param name Le nom du film.
    /// @param pathname Le chemin du fichier associé.
    /// @param duration La durée du film.
    /// @param chapters Les chapitres du film.
    Movie(
        std::string name,
        std::string pathname,
        uint32_t duration,
        uint32_t *chapters,
        uint32_t chaptersLength) : Video(name, pathname, duration)
    {
        this->setChapters(chapters, chaptersLength);
    };

    Movie(const Movie& from);
    Movie &operator=(const Movie &from);

    ~Movie()
    {
        if (this->chapters)
            delete[] this->chapters;
    }

    const uint32_t *getChapters() const { return this->chapters; };
    uint32_t getChaptersLength() const { return this->chaptersLength; };

    void setChapters(const uint32_t *chapters, uint32_t chaptersLength);

    /// @brief Affiche les informations du film.
    void display(std::ostream &sout) const;
};

#endif
