#ifndef SALA_HPP
#define SALA_HPP

#include <pthread.h>

#include "Entidade.hpp"

class Entidade;

class Sala {
    private:
        int id = -1;
        int quantidadeEntidadesPresentes = -1;
        int quantidadeEntidadesEmEspera = -1;
        bool estaVazia = false;
        bool entradaDisponivel = false;

        pthread_mutex_t mutexSala;
        pthread_cond_t condicaoSalaDisponivel;

    public:
        Sala(const int id);
        ~Sala();

        void entrar(Entidade* entidadeEntrando);
        void sair(Entidade* entidadeSaindo);

        int getId() const;
    
    private:
        bool ehPossivelFormarUmTrio() const;
        bool ehPossivelEntrarNaSala() const;
        bool salaFicouDisponivel() const;
};

#endif
