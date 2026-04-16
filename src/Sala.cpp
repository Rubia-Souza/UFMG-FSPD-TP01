#include "Sala.hpp"

Sala::Sala(const int id) {
    this->id = id;
    this->quantidadeEntidadesPresentes = 0;
}

Sala::~Sala() {
    this->id = -1;
    this->quantidadeEntidadesPresentes = -1;
}

void Sala::entrar() {
    // TODO: Implementar sincronização
    return;
}

void Sala::sair() {
    // TODO: Implementar sincronização
    return;
}

int Sala::getId() const {
    return this->id;
}

int Sala::getQuantidadeEntidadesPresentes() const {
    return this->quantidadeEntidadesPresentes;
}
