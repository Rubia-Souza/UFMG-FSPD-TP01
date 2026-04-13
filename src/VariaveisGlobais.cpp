#include "VariaveisGlobais.h"

#include <vector>

#include "Sala.h"
#include "Entidade.h"

std::vector<Sala*> salas;
std::vector<Entidade*> entidades;

Sala* getSalaByID(const int id) {
    for(Sala* sala : salas) {
        if(sala->getId() == id) {
            return sala;
        }
    }

    return nullptr;
}
