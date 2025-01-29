#ifndef INF224_SERDE_H
#define INF224_SERDE_H

#include <list>
#include <string>
#include <map>
#include <iostream>

/// @brief Structure des données de sérialisation/desérialisation.
/// @param class_name Le nom de la classe.
/// @param data Les données de la classe.
/// @param initialized_ptr Le pointeur vers l'objet initialisé.
typedef struct serde_data
{
    std::string class_name;
    std::list<std::string> data;
    void *initialized_ptr;
} serde_data_t;

typedef std::list<std::string> symboles_list;
typedef std::map<std::string, serde_data_t> symbole_map;

/// @brief Interface de sérialisation.
class Serialize
{
public:
    /// @brief Sérialise l'objet.
    /// @param symboles La liste des symboles déjà sérialisés.
    /// @return La sérialisation de l'objet.
    virtual std::string serialize(symboles_list &symboles) const = 0;

    /// @brief Retourne le symbole de l'objet.
    /// @return Le symbole de l'objet.
    virtual std::string getSymbole() const = 0;
};

/// @brief Interface de désérialisation.
class Deserialize
{
public:
    /// @brief Désérialise l'objet à partir des données sérialisées.
    /// @param data La liste des données sérialisées.
    /// @param symboles La liste des symboles existants, potentiellement déjà désérialisés.
    virtual void deserialize(std::list<std::string> data, symbole_map symboles) = 0;
};

// / @brief Parse les données d'objet serialisés avec `Serialize`.
/// @param data Les données sérialisées.
/// @return La liste des symboles sérialisés et leurs données associées.
symbole_map parse_symboles(std::istream &data);

/// @brief Affiche une list de symboles.
/// @param symboles La liste des symboles.
void print_symboles(symboles_list &symboles);

/// @brief Affiche un dictionnaire de symboles et leurs données associées.
/// @param symboles Le dictionnaire des symboles.
void print_symboles_map(symbole_map &symboles);

#endif