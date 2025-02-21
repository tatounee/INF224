
#ifndef INF224_VIDEO_H
#define INF224_VIDEO_H

#include <string>
#include <sstream>
#include <iostream>
#include <stdint.h>
#include <algorithm>

#include "media.h"

class Manager;

/// @brief Représente une image, avec un nom, un fichier associé, une largeur et une hauteur.
class Picture : public Media
{
    friend class Manager;

private:
    uint32_t width{};
    uint32_t height{};

protected:
    /// @brief Constructeur par défaut.
    Picture() {};

    /// @brief Constructeur avec paramètres.
    /// @param name Le nom de l'image.
    /// @param pathname Le chemin du fichier associé.
    /// @param width La largeur de l'image.
    /// @param height La hauteur de l'image.
    Picture(
        std::string name,
        std::string pathname,
        uint32_t width, uint32_t height) : Media(name, pathname),
                                           width{width},
                                           height{height} {};

    static std::shared_ptr<Picture> new_shared(std::string name, std::string pathname, uint32_t width, uint32_t height)
    {
        // Astuce pour permettre la création de shared_ptr<Picture> malgré que tous ses constructeurs soient protected.
        // See : https://stackoverflow.com/questions/8147027/how-do-i-call-stdmake-shared-on-a-class-with-only-protected-or-private-const/#answer-25069711
        struct NonProtectedPicture : public Picture
        {
        public:
            NonProtectedPicture(std::string name, std::string pathname, uint32_t width, uint32_t height) : Picture(name, pathname, width, height) {}
        };

        return std::static_pointer_cast<Picture>(std::make_shared<NonProtectedPicture>(name, pathname, width, height));
    }

public:
    uint32_t getWidth() { return this->width; };
    uint32_t getHeight() { return this->height; };

    void setWidth(uint32_t width) { this->width = width; };
    void setHeight(uint32_t height) { this->height = height; };

    /// @brief Affiche les informations de l'image.
    /// @param sout
    void display(std::ostream &sout) const
    {
        sout << "[Picture]" << std::endl
             << "\tname: \"" << this->getName() << "\"\n"
             << "\tpathname: \"" << this->getPathname() << "\"\n"
             << "\twidth: \"" << this->width << "\"\n"
             << "\theight: \"" << this->height << "\"\n";
    }

    /// @brief Affiche l'image avec `imagej`.
    void play() const override
    {
        std::string cmd = std::string("imagej ");
        cmd += this->getPathname();
        cmd += " &";

        system(cmd.data());
    }

    void serialize(symboles_map &symboles) const override
    {
        if (symboles.end() != symboles.find(this->getSymbole()))
            return;

        serde_data_t data;

        data.class_name = "Picture";
        data.data.push_back(this->getName());
        data.data.push_back(this->getPathname());
        data.data.push_back(std::to_string(this->width));
        data.data.push_back(std::to_string(this->height));

        symboles[this->getSymbole()] = data;
    };

    std::string getSymbole() const override
    {
        auto name = this->getName();
        std::replace(name.begin(), name.end(), ' ', '_');

        return std::string("picture_") + name;
    }

    void deserialize(serde_data_t serde_data, symboles_map symboles) override
    {
        if (serde_data.class_name != "Picture")
            throw WrongClass("Picture", serde_data.class_name);

        if (serde_data.data.size() != 4)
            throw NotEnoughData("Picture", 4, serde_data.data.size());

        auto it = serde_data.data.begin();

        std::string name = *it;
        std::string pathname = *++it;
        uint32_t width, height;

        try
        {
            width = std::stoi(*++it);
        }
        catch (const std::exception &e)
        {
            throw CanNotInterpretData("Picture", "uint32_t", *it);
        }

        try
        {
            height = std::stoi(*++it);
        }
        catch (const std::exception &e)
        {
            throw CanNotInterpretData("Picture", "uint32_t", *it);
        }

        this->setName(name);
        this->setPathname(pathname);
        this->setWidth(width);
        this->setHeight(height);
    }
};

#endif
