#ifndef INF224_DESERIALIZER_H
#define INF224_DEERIALIZER_H

#include <istream>
#include <string>

#include "serde.h"

/// @brief Désérialise des données dans une `symbole_map` depuis un `std::istream`.
/// @details Les données doivent être sérialisées sous la forme suivante :
/// ```
/// :<symbole>
/// -<class_name>
/// -<data>
/// -<data>
/// ...
/// ```
/// @param data Les données sérialiser.
/// @param symboles Les donnée à désérializer.
void deserializer(std::istream &data, symboles_map &symboles);

#endif