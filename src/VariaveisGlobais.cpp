#include "VariaveisGlobais.hpp"

#include <vector>

#include "Sala.hpp"
#include "Entidade.hpp"

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
