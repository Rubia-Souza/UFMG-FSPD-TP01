#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <vector>

#include "Sala.hpp"
#include "Parada.hpp"

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
