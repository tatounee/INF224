
#ifndef INF224_VIDEO_H
#define INF224_VIDEO_H

#include <stdint.h>
#include <iostream>

#include "media.h"

/// @brief Représente une image, avec un nom, un fichier associé, une largeur et une hauteur.
class Picture : public Media
{
private:
    uint32_t width{};
    uint32_t height{};

public:
    /// @brief Constructeur par défaut.
    Picture() {};
    /// @brief Constructeur avec paramètres.
    /// @param name Le nom de l'image.
    /// @param pathname Le chemin du fichier associé.
    /// @param width La largeur de l'image.
    /// @param height La hauteur de l'image.
    Picture(std::string name, std::string pathname, uint32_t width, uint32_t height) : Media(name, pathname)
    {
        this->width = width;
        this->height = height;
    };

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
    void play() const override {
        std::string cmd = std::string("imagej ");
        cmd += this->getPathname();
        cmd += " &";

        system(cmd.data());
    }
};

#endif
