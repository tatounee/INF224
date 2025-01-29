
#ifndef INT224_GROUP_H
#define INT224_GROUP_H

#include <list>

#include "media.h"

/// @brief Représente un groupe de médias.
class Group : public std::list<Media *>
{
private:
    std::string name{};

public:
    /// @brief Constructeur par défaut.
    Group() : name(std::string()) {};

    /// @brief Constructeur avec paramètres.
    /// @param name Le nom du groupe.
    Group(std::string name) : name{name} {};

    std::string getName() const { return this->name; };
    void setName(std::string name) { this->name = name; };

    /// @brief Affiche les informations du groupe.
    void display(std::ostream &sout) const
    {
        sout << "[Group]" << std::endl
             << "\tname: \"" << this->name << "\"\n"
             << "\tmedias: [\n";

        for (auto &media : *this)
        {
            media->display(sout);
        }

        sout << "]" << std::endl;
    };
};

#endif
