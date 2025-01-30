/// @file serde.h
/// @brief Définit les class Serialize et Deserialize.
///
/// La sérialisation et la désérialisation des objets convertissent les objets en `symbole_map`.
///
/// Un `symbole_map` est un dictionnaire de symboles et de données associées.
/// C'est une structure de données intermediare qui permet de convertir les objets en chaînes de caractères et vice versa.
///
/// Ce dictionnaire peut ensuite être donné à un `serializer` pour être converti en chaîne de caractères.
/// Il peut également être donné à un `deserializer` pour être converti en objets.

#ifndef INF224_SERDE_H
#define INF224_SERDE_H

#include <list>
#include <string>
#include <map>
#include <iostream>

/// @brief Structure des données de sérialisation/desérialisation.
/// @details Pour plus d'informations, voir `serde.h`.
/// @param class_name Le nom de la classe.
/// @param data Les données de la classe.
/// @param initialized_ptr Si l'objet à été désérialisé, un pointeur vers l'objet initialisé. Sinon, `nullptr`.
typedef struct serde_data
{
    std::string class_name;
    std::list<std::string> data;
    void *initialized_ptr;
} serde_data_t;

/// @brief Dictionnaire des symboles et leurs données associées.
/// @details Pour plus d'informations, voir `serde.h`.
typedef std::map<std::string, serde_data_t> symboles_map;

/// @brief Interface de sérialisation.
class Serialize
{
public:
    /// @brief Sérialise l'objet dans `symboles`.
    /// @param symboles Dictionnaire des symboles déjà sérialisés.
    /// Endroit où écrire les données sérialisées.
    virtual void serialize(symboles_map &symboles) const = 0;

    /// @brief Retourne le symbole de l'objet. Les espaces '␣" sont interdits.
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
    virtual void deserialize(serde_data_t serde_data, symboles_map symboles) = 0;
};

/// @brief Affiche un dictionnaire de symboles et leurs données associées.
/// @param symboles Le dictionnaire des symboles.
void print_symboles_map(symboles_map &symboles);

#endif