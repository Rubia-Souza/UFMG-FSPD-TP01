#include "Entidade.hpp"

#include <vector>

#include "Sala.hpp"
#include "Parada.hpp"

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

    salaAtual = nullptr;
    salaAnterior = nullptr;
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

Sala* Entidade::getSalaAtual() {
    return this->salaAtual;
}

void Entidade::setSalaAtual(Sala* sala) {
    this->setSalaAnterior(this->salaAtual);
    this->salaAtual = sala;
}

Sala* Entidade::getSalaAnterior() {
    return this->salaAnterior;
}

void Entidade::setSalaAnterior(Sala* sala) {
    this->salaAnterior = sala;
}

pthread_t* Entidade::getIdThread() {
    return &this->idThread;
}

void Entidade::setIdThread(pthread_t id) {
    this->idThread = id;
}
