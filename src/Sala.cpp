#include "Sala.hpp"

#include <pthread.h>

#include "Entidade.hpp"

#define QUANTIDADE_THREADS_POR_SALA 3

Sala::Sala(const int id) {
    this->id = id;
    this->quantidadeEntidadesPresentes = 0;
    this->quantidadeEntidadesEmEspera = 0;
    this->estaVazia = true;
    this->entradaDisponivel = false;

    this->mutexSala = PTHREAD_MUTEX_INITIALIZER;
    this->condicaoSalaDisponivel = PTHREAD_COND_INITIALIZER;
}

Sala::~Sala() {
    this->id = -1;
    this->quantidadeEntidadesPresentes = -1;
    this->quantidadeEntidadesEmEspera = -1;
    this->estaVazia = false;
    this->entradaDisponivel = false;
}

void Sala::entrar(Entidade* entidadeEntrando) {
    pthread_mutex_lock(&this->mutexSala);
    
    this->quantidadeEntidadesEmEspera++;

    if(this->ehPossivelFormarUmTrio()) {
        this->entradaDisponivel = this->ehPossivelEntrarNaSala();

        if(this->entradaDisponivel) {
            pthread_cond_broadcast(&this->condicaoSalaDisponivel);
        }
    }

    while(!this->entradaDisponivel) {
        pthread_cond_wait(&this->condicaoSalaDisponivel, &this->mutexSala);
    }

    entidadeEntrando->setSalaAtual(this);

    this->quantidadeEntidadesPresentes++;
    this->quantidadeEntidadesEmEspera--;
    // TODO: Talvez guardar uma lista das threads em espera e na sala

    bool ehUltimaDoTrioEntrando = (this->estaVazia && this->quantidadeEntidadesPresentes == QUANTIDADE_THREADS_POR_SALA);
    if(ehUltimaDoTrioEntrando) {
        this->estaVazia = false;
        this->entradaDisponivel = false;
    }

    pthread_mutex_unlock(&this->mutexSala);
}

void Sala::sair(Entidade* entidadeSaindo) {
    pthread_mutex_lock(&this->mutexSala);

    entidadeSaindo->setSalaAnterior(this);

    this->quantidadeEntidadesPresentes--;

    if(this->salaFicouDisponivel()) {
        this->estaVazia = true;
        this->entradaDisponivel = this->ehPossivelEntrarNaSala();

        if(this->entradaDisponivel) {
            pthread_cond_broadcast(&this->condicaoSalaDisponivel);
        }
    }

    pthread_mutex_unlock(&this->mutexSala);
}

int Sala::getId() const {
    return this->id;
}

bool Sala::ehPossivelFormarUmTrio() const {
    return this->quantidadeEntidadesEmEspera >= QUANTIDADE_THREADS_POR_SALA;
}

bool Sala::ehPossivelEntrarNaSala() const {
    return this->estaVazia && this->ehPossivelFormarUmTrio();
}

bool Sala::salaFicouDisponivel() const {
    return !this->estaVazia && this->quantidadeEntidadesPresentes == 0;
}
