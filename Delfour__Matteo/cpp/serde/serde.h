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
#include <stdexcept>

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

/// @brief Erreur de sérialisation/désérialisation.
class SerdeError : public std::runtime_error
{
public:
    SerdeError(const std::string &message) : std::runtime_error(message) {};
};

/// @brief Cette erreur est levée lorsqu'il n'y a pas assez de données pour désérialiser un objet.
class NotEnoughData : public SerdeError
{
public:
    NotEnoughData(const std::string &class_name, const int &expected, const int &got)
        : SerdeError(
              "Not enough data for deserialize class " + class_name + ". Expected " + std::to_string(expected) + " but got " + std::to_string(got) + ".") {}

    const char *what() const noexcept override
    {
        return SerdeError::what();
    }
};

/// @brief Cette erreur est levée lorqu'une donnée ne peut pas être interprétée.
class CanNotInterpretData : public SerdeError
{
public:
    CanNotInterpretData(const std::string &class_name, const std::string &expected, const std::string &value)
        : SerdeError(
              "Can not interpret data for deserialize class " + class_name + ". Expected " + expected + " but can not interpret \"" + value + "\" as this.") {}

    const char *what() const noexcept override
    {
        return SerdeError::what();
    }
};

/// @brief Cette erreur est levée lorsqu'un objet dépend d'un autre objet X et que : X n'est pas initialisé, l'objet qu'il ne peut pas initialiser X lui même.
class ObjectMustBeInitialized : public SerdeError
{
public:
    ObjectMustBeInitialized(const std::string &class_name, const std::string &symbole)
        : SerdeError("Symbole " + symbole + ", object " + class_name + " must be initialized.") {}

    const char *what() const noexcept override
    {
        return SerdeError::what();
    }
};

/// @brief Cette erreur est levée lorsqu'un symbole n'est pas défini.
class UndefinedSymbole : public SerdeError
{
public:
    UndefinedSymbole(const std::string &symbole)
        : SerdeError("Symbole " + symbole + " is not defined.") {}

    const char *what() const noexcept override
    {
        return SerdeError::what();
    }
};

/// @brief Cette erreur est levée lorsqu'une donnée à désérialiser ne correspond pas à la classe de l'objet.
class WrongClass : public SerdeError
{
public:
    WrongClass(const std::string &expected, const std::string &got)
        : SerdeError("Wrong class for deserialize data. Expected " + expected + " but got " + got + ".") {}

    const char *what() const noexcept override
    {
        return SerdeError::what();
    }
};

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
    /// @throw `NotEnoughData` Si les données ne sont pas suffisantes pour désérialiser l'objet.
    /// @throw `CanNotInterpretData` Si les données ne peuvent pas être interprétées.
    /// @throw `ObjectMustBeInitialized` Si l'objet dépent d'un autre objet X et que : X n'est pas initialisé, l'objet qu'il ne peut pas initialiser X lui même.
    /// @throw `UndefinedSymbole` Si un symbole n'est pas défini.
    /// @throw `WrongClass` Si les donnée à désérialiser ne corresponde pas à la classe de l'objet.
    /// @param data La liste des données sérialisées.
    /// @param symboles La liste des symboles existants, potentiellement déjà désérialisés.
    virtual void deserialize(serde_data_t serde_data, symboles_map symboles) = 0;
};

/// @brief Affiche un dictionnaire de symboles et leurs données associées.
/// @param symboles Le dictionnaire des symboles.
void print_symboles_map(symboles_map &symboles);

#endif