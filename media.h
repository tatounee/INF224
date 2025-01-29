
#ifndef INF224_MEDIA_H
#define INF224_MEDIA_H

#include <iostream>
#include <string>

/// @brief Représente un média, avec un nom et un ficher associé.
class Media
{
private:
    std::string name{};
    std::string pathname{};

public:
    /// @brief Constructeur par défaut.
    Media() : name(std::string()), pathname(std::string()) {};

    /// @brief  Constructeur avec paramètres.
    /// @param name Le nom du média.
    /// @param pathname Le chemin du fichier associé.
    Media(std::string name, std::string pathname);

    std::string getName() const;
    std::string getPathname() const;

    void setName(std::string name);
    void setPathname(std::string name);

    /// @brief Affiche les informations du média.
    /// @param sout Le flux de sortie.
    void display(std::ostream &sout) const;

    /// @brief Joue le média.
    virtual void play() const {};
};

#endif
