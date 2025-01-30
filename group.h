
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

    void serialize(symboles_map &symboles) const override
    {
        if (symboles.end() != symboles.find(this->getSymbole()))
            return;

        serde_data_t data;

        data.class_name = "Group";
        data.data.push_back(this->getName());

        int i = 0;
        std::stringstream ss;
        for (auto &media : *this)
        {
            if (i++ > 0)
                ss << " ";
            ss << media->getSymbole();

            media->serialize(symboles);
        }
        data.data.push_back(ss.str());

        symboles[this->getSymbole()] = data;
    };

    std::string getSymbole() const override
    {
        auto name = this->getName();
        std::replace(name.begin(), name.end(), ' ', '_');

        return std::string("group_") + name;
    };

    void deserialize(serde_data_t serde_data, symboles_map symboles) override
    {
        auto it = serde_data.data.begin();
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
