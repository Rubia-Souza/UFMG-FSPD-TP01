#include "Parada.hpp"

#include "Sala.hpp"

Parada::Parada(Sala* sala, const int tempoEspera) {
    this->sala = sala;
    this->tempoEspera = tempoEspera;
}

Parada::~Parada() {
    this->sala = nullptr;
    this->tempoEspera = -1;
}

Sala* Parada::getSala() {
    return this->sala;
}

int Parada::getTempoEspera() const {
    return this->tempoEspera;
}
