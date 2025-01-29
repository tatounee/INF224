
#include <sstream>
#include <algorithm>

#include "manager.h"
#include "commands.h"

/// @brief Recherche un média et l'affiche dans `response`.
/// @param response Le string où écrire le résultat.
/// @param data Le nom du média.
/// @param manager Le manager de média et de groupes.
void find_media(std::string &response, std::string &data, Manager &manager)
{
    std::stringstream result = {};
    manager.display_media(data, result);

    response = result.str();
    std::replace(response.begin(), response.end(), '\n', ';');
}

/// @brief Recherche un groupe et l'affiche dans `response`.
/// @param response Le string où écrire le résultat.
/// @param data Le nom du groupe.
/// @param manager Le manager de média et de groupes.
void find_group(std::string &response, std::string &data, Manager &manager)
{
    std::stringstream result = {};
    manager.display_group(data, result);

    response = result.str();
    std::replace(response.begin(), response.end(), '\n', ';');
}

/// @brief Supprime un média.
/// @param response Le string où écrire le résultat.
/// @param data Le nom du média.
/// @param manager Le manager de média et de groupes.
void delete_media(std::string &response, std::string &data, Manager &manager)
{
    manager.delete_media(data);
    response = "OK";
}

/// @brief Supprime un groupe.
/// @param response Le string où écrire le résultat.
/// @param data Le nom du groupe.
/// @param manager Le manager de média et de groupes.
void delete_group(std::string &response, std::string &data, Manager &manager)
{
    manager.delete_group(data);
    response = "OK";
}

/// @brief Liste tous les médias.
/// @param response Le string où écrire le résultat.
/// @param data Inutilisé.
/// @param manager Le manager de média et de groupes.
void list_media(std::string &response, std::string &data, Manager &manager)
{
    std::list<std::string> media_names = manager.list_media();
    std::stringstream result = {};
    for (auto &media_name : media_names)
        result << media_name << std::endl;

    response = result.str();
    std::replace(response.begin(), response.end(), '\n', ';');
}

/// @brief Liste tous les groupes.
/// @param response Le string où écrire le résultat.
/// @param data Inutilisé.
/// @param manager Le manager de média et de groupes.
void list_group(std::string &response, std::string &data, Manager &manager)
{
    std::list<std::string> group_names = manager.list_group();
    std::stringstream result = {};
    for (auto &group_name : group_names)
        result << group_name << std::endl;

    response = result.str();
    std::replace(response.begin(), response.end(), '\n', ';');
}

/// @brief Joue un média.
/// @param response Le string où écrire le résultat.
/// @param data Le nom du média.
/// @param manager Le manager de média et de groupes.
void play(std::string &response, std::string &data, Manager &manager)
{
    manager.play_media(data);
    response = "OK";
}

/// @brief Affiche l'aide des commands.
/// @param response Le string où écrire le résultat.
/// @param data Inutilisé.
/// @param manager Inutilisé.
void help(std::string &response, std::string &data, Manager &manager)
{
    std::stringstream result = {};
    result << "findmedia <name> \t: Display media <name>" << std::endl;
    result << "findgroup <name> \t: Display group <name>" << std::endl;
    result << "deletemedia <name> \t: Delete media <name>" << std::endl;
    result << "deletegroup <name> \t: Delete group <name>" << std::endl;
    result << "listmedia \t\t: List all media" << std::endl;
    result << "listgroup \t\t: List all groups" << std::endl;
    result << "play <name> \t\t: Play media <name>" << std::endl;
    result << "help \t\t\t: Display this help" << std::endl;

    response = result.str();
}

commands_t commands;

void init_commands()
{
    commands["findmedia"] = find_media;
    commands["findgroup"] = find_group;
    commands["deletemedia"] = delete_media;
    commands["deletegroup"] = delete_group;
    commands["listmedia"] = list_media;
    commands["listgroup"] = list_group;
    commands["play"] = play;
    commands["help"] = help;
}