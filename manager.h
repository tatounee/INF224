
#ifndef INF224_MANAGER_H
#define INF224_MANAGER_H

#include <string>
#include <memory>
#include <map>

#include "picture.h"
#include "video.h"
#include "movie.h"
#include "group.h"

using media_dict = std::map<std::string, std::shared_ptr<Media>>;
using group_dict = std::map<std::string, std::shared_ptr<Group>>;

using media_ptr = std::shared_ptr<Media>;
using picture_ptr = std::shared_ptr<Picture>;
using video_ptr = std::shared_ptr<Video>;
using movie_ptr = std::shared_ptr<Movie>;
using group_ptr = std::shared_ptr<Group>;

/// @brief Représente un gestionnaire de médias. Permet de créer, supprimer, afficher et jouer des médias et des groupes.
class Manager
{
private:
    media_dict medias{};
    group_dict groups{};

public:
    /// @brief Constructeur par défaut.
    Manager() : medias(media_dict()), groups(group_dict()) {};

    /// @brief Crée une image gérer par le manager.
    /// @param name Le nom de l'image.
    /// @param pathname Le chemin du fichier associé.
    /// @param width La largeur de l'image.
    /// @param height La hauteur de l'image.
    /// @return Un pointeur partagé vers l'image.
    picture_ptr create_picture(std::string name, std::string pathname, uint32_t width, uint32_t height);

    /// @brief Crée une vidéo gérer par le manager.
    /// @param name Le nom de la vidéo.
    /// @param pathname Le chemin du fichier associé.
    /// @param duration La durée de la vidéo.
    /// @return Un pointeur partagé vers la vidéo.
    video_ptr create_video(std::string name, std::string pathname, uint32_t duration);

    /// @brief Crée un film gérer par le manager.
    /// @param name Le nom du film.
    /// @param pathname Le chemin du fichier associé.
    /// @param duration La durée du film.
    /// @param chapters Les chapitres du film.
    /// @param chaptersLength La longueur du tableau de chapitres.
    /// @return Un pointeur partagé vers le film.
    movie_ptr create_movie(std::string name, std::string pathname, uint32_t duration, uint32_t *chapters, uint32_t chaptersLength);

    /// @brief Crée un groupe gérer par le manager.
    /// @param name Le nom du groupe.
    /// @return Un pointeur partagé vers le groupe.
    group_ptr create_group(std::string name);

    /// @brief Supprime un média gérer par le manager.
    void delete_media(std::string name);

    /// @brief Affiche les informations d'un média.
    /// @param name Le nom du média.
    /// @param sout Le flux de sortie.
    void display_media(std::string name, std::ostream &sout) const;

    /// @brief Affiche les informations d'un groupe.
    /// @param name Le nom du groupe.
    /// @param sout Le flux de sortie.
    void display_group(std::string name, std::ostream &sout) const;

    /// @brief Joue un média.
    /// @param name Le nom du média.
    void play_media(std::string name) const;
};

#endif
