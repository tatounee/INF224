
#ifndef INT224_GROUP_H
#define INT224_GROUP_H

#include <sstream>
#include <list>
#include <memory>
#include <algorithm>

#include "serde.h"
#include "media.h"

class Manager;

/// @brief Représente un groupe de médias.
class Group : public std::list<std::shared_ptr<Media>>, public Serialize, public Deserialize
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

    std::string serialize(symboles_list &symboles) const override
    {
        if (symboles.end() != std::find(symboles.begin(), symboles.end(), this->getSymbole()))
            return std::string();
        symboles.push_back(this->getSymbole());

        std::stringstream ss;
        std::stringstream media_ss;

        ss << ":" << this->getSymbole() << std::endl;
        ss << "-Group" << std::endl;
        ss << "-" << this->getName() << std::endl;
        ss << "-";

        int i = 0;
        for (auto &media : *this)
        {
            if (i++ > 0)
                ss << " ";
            ss << media->getSymbole();

            media_ss << media->serialize(symboles);
        }

        ss << std::endl;
        ss << media_ss.str();

        return ss.str();
    };

    std::string getSymbole() const override
    {
        auto name = this->getName();
        std::replace(name.begin(), name.end(), ' ', '_');

        return std::string("group_") + name;
    };

    void deserialize(std::list<std::string> data, symbole_map symboles) override
    {
        auto it = data.begin();
        auto nnn = *it++;
        this->setName(nnn);

        std::string name;

        std::stringstream medias_ss(*it++);
        std::getline(medias_ss, name, ' ');
        while (name != "")
        {
            serde_data_t symbole_data = symboles[name];

            if (symbole_data.initialized_ptr != nullptr)
            {
                std::shared_ptr<Media> *media = (std::shared_ptr<Media> *)symbole_data.initialized_ptr;
                this->push_back(*media);
            }
            else
                std::cerr << "Media " << name << " not initialized." << std::endl;

            name.clear();
            std::getline(medias_ss, name, ' ');
        }
    }
};

#endif
