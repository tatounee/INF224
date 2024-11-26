
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
    Media() : name(std::string()), pathname(std::string()) {};
    Media(std::string name, std::string pathname);

    std::string getName() const;
    std::string getPathname() const;

    void setName(std::string name);
    void setPathname(std::string name);

    void display(std::ostream &sout) const;
};

#endif
