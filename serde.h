#ifndef INF224_SERDE_H
#define INF224_SERDE_H

#include <list>
#include <string>
#include <map>
#include <iostream>

typedef struct serde_data
{
    std::string class_name;
    std::list<std::string> data;
    void *initialized_ptr;
} serde_data_t;

typedef std::list<std::string> symboles_list;
typedef std::map<std::string, serde_data_t> symbole_map;

class Serialize
{
public:
    virtual std::string serialize(symboles_list &symboles) const = 0;
    virtual std::string getSymbole() const = 0;
};

class Deserialize
{
public:
    virtual void deserialize(std::list<std::string> data, symbole_map symboles) = 0;
};

symbole_map parse_symboles(std::istream &data);
void print_symboles(symboles_list &symboles);
void print_symboles_map(symbole_map &symboles);

#endif