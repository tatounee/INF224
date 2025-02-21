
#ifndef INF224_MEDIA_H
#define INF224_MEDIA_H

#include <iostream>
#include <string>

#include "../serde/serde.h"

/// @brief Représente un média, avec un nom et un ficher associé.
class Media : public Serialize, public Deserialize
{
private:
    std::string name{};
    std::string pathname{};

protected:
    /// @brief Constructeur par défaut.
    Media() : name(std::string()), pathname(std::string()) {};

    /// @brief  Constructeur avec paramètres.
    /// @param name Le nom du média.
    /// @param pathname Le chemin du fichier associé.
    Media(std::string name, std::string pathname) : name{name}, pathname{pathname} {};

public:
    std::string getName() const { return this->name; };
    std::string getPathname() const { return this->pathname; };

    void setName(std::string name) { this->name = name; };
    void setPathname(std::string pathname) { this->pathname = pathname; };

    /// @brief Affiche les informations du média.
    /// @param sout Le flux de sortie.
    void display(std::ostream &sout) const
    {
        sout << "[Media]" << std::endl
             << "\tname: \"" << this->name << "\"\n"
             << "\tpathname: \"" << this->pathname << "\"\n";
    };

    /// @brief Joue le média.
    virtual void play() const {};
};

#endif
