
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
        if (serde_data.class_name != "Group")
            throw WrongClass("Group", serde_data.class_name);

        if (serde_data.data.size() != 2)
            throw NotEnoughData("Group", 2, serde_data.data.size());

        auto it = serde_data.data.begin();

        std::string name = *it++;
        std::list<std::shared_ptr<Media>> media_list;

        std::stringstream medias_ss(*it++);
        std::string media_name;
        std::getline(medias_ss, media_name, ' ');

        while (media_name != "")
        {
            if (symboles.find(media_name) == symboles.end())
                throw UndefinedSymbole(media_name);

            serde_data_t symbole_data = symboles[media_name];

            if (symbole_data.initialized_ptr != nullptr)
            {
                std::shared_ptr<Media> *media = (std::shared_ptr<Media> *)symbole_data.initialized_ptr;
                media_list.push_back(*media);
            }
            else
                throw ObjectMustBeInitialized("Media", media_name);

            media_name.clear();
            std::getline(medias_ss, media_name, ' ');
        }

        this->setName(name);
        this->clear();
        this->insert(this->begin(), media_list.begin(), media_list.end());
    }
};

#endif
