
#ifndef INF224_MANAGER_H
#define INF224_MANAGER_H

#include <string>
#include <memory>
#include <map>
#include <stdexcept>

#include "picture.h"
#include "video.h"
#include "movie.h"
#include "group.h"
#include "serde.h"

#define MANAGER_SYMB ("manager")

using media_dict = std::map<std::string, std::shared_ptr<Media>>;
using group_dict = std::map<std::string, std::shared_ptr<Group>>;

using media_ptr = std::shared_ptr<Media>;
using picture_ptr = std::shared_ptr<Picture>;
using video_ptr = std::shared_ptr<Video>;
using movie_ptr = std::shared_ptr<Movie>;
using group_ptr = std::shared_ptr<Group>;

enum manager_error
{
    NONE = 0,
    MEDIA_NOT_FOUND,
    GROUP_NOT_FOUND,
    MEDIA_ALREADY_EXISTS,
    GROUP_ALREADY_EXISTS,
    UNABLE_TO_OPEN_FILE,
};

class ManagerError : public std::runtime_error
{
public:
    ManagerError(const std::string &message) : std::runtime_error(message) {};
};

class NameAlreadyTaken : public ManagerError
{
public:
    NameAlreadyTaken(const std::string &name)
        : ManagerError("Name \"" + name + "\" is already taken") {}

    const char *what() const noexcept override
    {
        return ManagerError::what();
    }
};

/// @brief Représente un gestionnaire de médias. Permet de créer, supprimer, afficher et jouer des médias et des groupes.
class Manager : Serialize,
                Deserialize
{
private:
    media_dict medias{};
    group_dict groups{};

public:
    /// @brief Constructeur par défaut.
    Manager() : medias(media_dict()), groups(group_dict()) {};

    /// @brief Crée une image gérer par le manager.
    /// @throw `NameAlreadyTaken` Si le nom est déjà pris.
    /// @param name Le nom de l'image.
    /// @param pathname Le chemin du fichier associé.
    /// @param width La largeur de l'image.
    /// @param height La hauteur de l'image.
    /// @return Un pointeur partagé vers l'image.
    picture_ptr create_picture(std::string name, std::string pathname, uint32_t width, uint32_t height);

    /// @brief Crée une vidéo gérer par le manager.
    /// @throw `NameAlreadyTaken` Si le nom est déjà pris.
    /// @param name Le nom de la vidéo.
    /// @param pathname Le chemin du fichier associé.
    /// @param duration La durée de la vidéo.
    /// @return Un pointeur partagé vers la vidéo.
    video_ptr create_video(std::string name, std::string pathname, uint32_t duration);

    /// @brief Crée un film gérer par le manager.
    /// @throw `NameAlreadyTaken` Si le nom est déjà pris.
    /// @param name Le nom du film.
    /// @param pathname Le chemin du fichier associé.
    /// @param duration La durée du film.
    /// @param chapters Les chapitres du film.
    /// @param chaptersLength La longueur du tableau de chapitres.
    /// @return Un pointeur partagé vers le film.
    movie_ptr create_movie(std::string name, std::string pathname, uint32_t duration, uint32_t *chapters, uint32_t chaptersLength);

    /// @brief Crée un groupe gérer par le manager.
    /// @throw `NameAlreadyTaken` Si le nom est déjà pris.
    /// @param name Le nom du groupe.
    /// @return Un pointeur partagé vers le groupe.
    group_ptr create_group(std::string name);

    /// @brief Affiche les informations d'un média.
    /// @param name Le nom du média.
    /// @param sout Le flux de sortie.
    /// @return `manager_error::MEDIA_NOT_FOUND` si le média n'existe pas, `manager_error::NONE` sinon.
    manager_error display_media(std::string name, std::ostream &sout) const;

    /// @brief Affiche les informations d'un groupe.
    /// @param name Le nom du groupe.
    /// @param sout Le flux de sortie.
    /// @return `manager_error::GROUP_NOT_FOUND` si le groupe n'existe pas, `manager_error::NONE` sinon.
    manager_error display_group(std::string name, std::ostream &sout) const;

    /// @brief Supprime un média gérer par le manager.
    /// @param name Le nom du média.
    /// @return `manager_error::MEDIA_NOT_FOUND` si le média n'existe pas, `manager_error::NONE` sinon.
    manager_error delete_media(std::string name);

    /// @brief Supprime un groupe gérer par le manager.
    /// @param name Le nom du groupe.
    /// @return `manager_error::GROUP_NOT_FOUND` si le groupe n'existe pas, `manager_error::NONE` sinon.
    manager_error delete_group(std::string name);

    /// @brief Liste les médias gérer par le manager.
    /// @return La liste des noms des médias.
    std::list<std::string> list_media() const;

    /// @brief Liste les groupes gérer par le manager.
    /// @return La liste des noms des groupes.
    std::list<std::string> list_group() const;

    /// @brief Joue un média.
    /// @param name Le nom du média.
    /// @return `manager_error::MEDIA_NOT_FOUND` si le média n'existe pas, `manager_error::NONE` sinon.
    manager_error play_media(std::string name) const;

    void serialize(symboles_map &symboles) const override;
    std::string getSymbole() const override { return MANAGER_SYMB; };
    void deserialize(serde_data_t serde_data, symboles_map symboles) override;

    /// @brief Sauvegarde les médias et les groupes dans un fichier.
    /// @param filename Le nom du fichier.
    /// @return `manager_error::UNABLE_TO_OPEN_FILE` si le fichier ne peut pas être ouvert, `manager_error::NONE` sinon.
    manager_error save(std::string filename) const;

    /// @brief Charge les médias et les groupes depuis un fichier.
    /// @throw `SerdeError` Si une erreur survient lors de la lecture du fichier.
    /// @param filename Le nom du fichier.
    /// @return `manager_error::UNABLE_TO_OPEN_FILE` si le fichier ne peut pas être ouvert, `manager_error::NONE` sinon.
    manager_error load(std::string filename);
};

#endif
