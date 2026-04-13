#ifndef ENTIDADE_H
#define ENTIDADE_H

#include <vector>

#include "Sala.h"
#include "Parada.h"

class Entidade {
    private:
        int id = -1;
        int tempoEsperaInicial = -1;

        int quantidadeSalasCaminho = -1;
        std::vector<Parada> caminho;

    public:
        Entidade(const int id, const int tempoEsperaInicial, const int quantidadeSalasCaminho);
        ~Entidade();

        void adicionarParada(Sala* sala, const int tempoEspera);

        int getId() const;
        int getTempoEsperaInicial() const;
        int getQuantidadeSalasCaminho() const;
        std::vector<Parada> getCaminho() const;
};

#endif
