#ifndef INF244_COMMANDS_H
#define INF244_COMMANDS_H

#include <string>
#include <map>

#include "manager.h"

typedef std::map<std::string, void (*)(std::string &response, std::string &data, Manager &manager)> commands_t;

extern commands_t commands;

void init_commands();

#endif