#ifndef VARIAVEIS_GLOBAIS_HPP
#define VARIAVEIS_GLOBAIS_HPP

#include <vector>

#include "Sala.hpp"
#include "Entidade.hpp"

extern std::vector<Sala*> salas;
extern std::vector<Entidade*> entidades;

Sala* getSalaByID(const int id);

#endif
