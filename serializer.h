#ifndef INF224_SERIALIZER_H
#define INF224_SERIALIZER_H

#include <ostream>
#include <string>

#include "serde.h"

/// @brief Sérialise des données dans un `std::ostream`.
/// @param sout Endroit où écrire les données sérialisées.
/// @param symboles Les données à sérialiser.
void serializer(std::ostream &sout, symboles_map &symboles);

#endif
