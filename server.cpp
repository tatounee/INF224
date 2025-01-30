
#include <algorithm>

#include "tcpserver.h"
#include "commands.h"
#include "manager.h"

const int PORT = 3331;

int main()
{
    init_commands();

    Manager manager;

    auto holo = manager.create_video("holo", "/home/tatoune/Pictures/holofog.png", 15);
    auto holo2 = manager.create_movie("holo2", "/home/tatoune/Pictures/holofog.png", 15, new uint32_t[2]{5, 10}, 2);
    auto ferris = manager.create_picture("ferris", "/home/tatoune/Pictures/ferris/ferris.png", 1124, 588);
    auto ferrisJE = manager.create_picture("ferrisJE", "/home/tatoune/Pictures/ferris/ferrisJE.png", 1124, 588);
    auto rust = manager.create_group("Rust");
    auto variations = manager.create_group("Variations");

    rust->push_back(ferris);
    rust->push_back(ferrisJE);
    variations->push_back(ferrisJE);

    // Cree le TCPServer
    auto *server =
        new TCPServer([&manager](std::string const &request, std::string &response)
                      {
        size_t pos = request.find_first_of(' ');
        std::string command = request.substr(0, pos);

        std::string data;
        if (pos != std::string::npos)
            data = request.substr(pos + 1);
        else
            data = std::string();

        auto command_callback = commands.find(command);
        if (command_callback != commands.end())
            command_callback->second(response, data, manager);
        else
            response = "Unknown command";

        std::replace(response.begin(), response.end(), '\n', ';');

        return true; });

    // lance la boucle infinie du serveur
    std::cout << "Starting Server on port " << PORT << std::endl;
    int status = server->run(PORT);

    // en cas d'erreur
    if (status < 0)
    {
        std::cerr << "Could not start Server on port " << PORT << std::endl;
        return 1;
    }

    return 0;
}
