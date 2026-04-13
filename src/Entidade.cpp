#include "Entidade.h"

#include <vector>

#include "Sala.h"
#include "Parada.h"

Entidade::Entidade(const int id, const int tempoEsperaInicial, const int quantidadeSalasCaminho) {
    this->id = id;
    this->tempoEsperaInicial = tempoEsperaInicial;
    this->quantidadeSalasCaminho = quantidadeSalasCaminho;
}

Entidade::~Entidade() {
    this->id = -1;
    this->tempoEsperaInicial = -1;
    this->quantidadeSalasCaminho = -1;

    this->caminho.clear();
}

void Entidade::adicionarParada(Sala* sala, const int tempoEspera) {
    Parada novaParada = Parada(sala, tempoEspera);
    this->caminho.push_back(novaParada);
}

int Entidade::getId() const {
    return this->id;
}

int Entidade::getTempoEsperaInicial() const {
    return this->tempoEsperaInicial;
}

int Entidade::getQuantidadeSalasCaminho() const {
    return this->quantidadeSalasCaminho;
}

std::vector<Parada> Entidade::getCaminho() const {
    return this->caminho;
}
