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
    // Trava o acesso a região crítica.
    pthread_mutex_lock(&this->mutexSala);
    
    // Indica que a entidade atual entrou na espera para entrar na sala.
    this->quantidadeEntidadesEmEspera++;

    if(this->ehPossivelFormarUmTrio()) { // Verifica se a entidade que está entrando atualmente pode formar um trio.
        // Se ela está formando um novo trio, a sala verifica se as condições para entrar na sala passaram a ser atendidas.
        this->entradaDisponivel = this->ehPossivelEntrarNaSala();

        if(this->entradaDisponivel) {
            // Se as condições para entrar passaram a ser atendidas, a sala notifica as entidades em espera para elas entrerm na sala.
            pthread_cond_broadcast(&this->condicaoSalaDisponivel);
        }
    }

    while(!this->entradaDisponivel) { // Verifica se a entrada das entidades na sala está disponível.
        // Se a entrada não está disponível, a entidade entra em espera até a entrada ficar disponível.
        pthread_cond_wait(&this->condicaoSalaDisponivel, &this->mutexSala);
    }

    // Quando a entrada fica disponível, a entidade entra nesta sala.
    entidadeEntrando->setSalaAtual(this);

    // Incrementa a contagem de entidades dentro da sala.
    this->quantidadeEntidadesPresentes++;
    // Decrementa a contagem de entidades esperando para entrar na sala.
    this->quantidadeEntidadesEmEspera--;

    bool ehUltimaDoTrioEntrando = (this->estaVazia && this->quantidadeEntidadesPresentes == QUANTIDADE_THREADS_POR_SALA);
    if(ehUltimaDoTrioEntrando) { // Verifica se é a última entidade do trio que está entrando na sala.
        // Se ela é a terceira entidade a entrar, a sala define que não está mais vazia.
        this->estaVazia = false;
        // Além disso, define que a entrada não está mais disponível.
        this->entradaDisponivel = false;
    }

    // Libera o acesso a região crítica.
    pthread_mutex_unlock(&this->mutexSala);
}

void Sala::sair(Entidade* entidadeSaindo) {
    // Trava o acesso a região crítica.
    pthread_mutex_lock(&this->mutexSala);

    // Atualiza a sala anterior da entidade para esta.
    entidadeSaindo->setSalaAnterior(this);

    // Decrementa a quantidade de entidades dentro da sala.
    this->quantidadeEntidadesPresentes--;

    if(this->salaFicouVazia()) { // Verifica se a sala ficou vazia.
        this->estaVazia = true;
        // Se sim, verifica se as condições para entrar na sala foram atendidas.
        this->entradaDisponivel = this->ehPossivelEntrarNaSala();

        if(this->entradaDisponivel) { 
            // Se a entrada está disponível, a sala notifica as entidades em espera para elas entrerm na sala.
            pthread_cond_broadcast(&this->condicaoSalaDisponivel);
        }
    }

    // Libera o acesso a região crítica.
    pthread_mutex_unlock(&this->mutexSala);
}

int Sala::getId() const {
    return this->id;
}

bool Sala::ehPossivelFormarUmTrio() const {
    // Um trio é formado, quando a quantidade de entidades esperando para entrar dentro da sala é maior ou igual a 3.
    return this->quantidadeEntidadesEmEspera >= QUANTIDADE_THREADS_POR_SALA;
}

bool Sala::ehPossivelEntrarNaSala() const {
    // Só é possível entrar na sala quando a sala está vazia e possui um trio em espera.
    return this->estaVazia && this->ehPossivelFormarUmTrio();
}

bool Sala::salaFicouVazia() const {
    // A sala fica vazia quando, antriormente, ela não estava vazia e a quantidade de entidades dentro dela chegou em 0.
    return !this->estaVazia && this->quantidadeEntidadesPresentes == 0;
}
