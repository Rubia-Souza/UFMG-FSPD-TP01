#ifndef VARIAVEIS_GLOBAIS_H
#define VARIAVEIS_GLOBAIS_H

#include <vector>

#include "Sala.h"
#include "Entidade.h"

extern std::vector<Sala*> salas;
extern std::vector<Entidade*> entidades;

Sala* getSalaByID(const int id);

#endif
