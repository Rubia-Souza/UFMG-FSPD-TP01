#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <vector>
#include <pthread.h>

#include "Sala.hpp"
#include "Parada.hpp"

class Sala;
class Parada;

class Entidade {
    private:
        int id = -1;
        pthread_t idThread;
        int tempoEsperaInicial = -1;

        int quantidadeSalasCaminho = -1;
        std::vector<Parada> caminho;

        Sala* salaAtual = nullptr;
        Sala* salaAnterior = nullptr;

    public:
        Entidade(const int id, const int tempoEsperaInicial, const int quantidadeSalasCaminho);
        ~Entidade();

        void adicionarParada(Sala* sala, const int tempoEspera);

        int getId() const;
        int getTempoEsperaInicial() const;
        int getQuantidadeSalasCaminho() const;
        std::vector<Parada> getCaminho() const;

        Sala* getSalaAtual();
        void setSalaAtual(Sala* sala);

        Sala* getSalaAnterior();
        void setSalaAnterior(Sala* sala);

        pthread_t* getIdThread();
        void setIdThread(pthread_t id);
};

#endif
