
#ifndef INT224_GROUP_H
#define INT224_GROUP_H

#include <list>
#include <memory>
#include "media.h"

class Manager;

/// @brief Représente un groupe de médias.
class Group : public std::list<std::shared_ptr<Media>>
{
    friend class Manager;

private:
    std::string name{};

protected:
    /// @brief Constructeur par défaut.
    Group() : name(std::string()) {};

    /// @brief Constructeur avec paramètres.
    /// @param name Le nom du groupe.
    Group(std::string name) : name{name} {};

    static std::shared_ptr<Group> new_shared(std::string name)
    {
        struct NonProtectedGroup : public Group
        {
        public:
            NonProtectedGroup(std::string name) : Group(name) {}
        };

        return std::static_pointer_cast<Group>(std::make_shared<NonProtectedGroup>(name));
    }

public:

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
