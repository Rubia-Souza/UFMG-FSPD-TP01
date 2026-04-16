#ifndef PARADA_HPP
#define PARADA_HPP

#include "Sala.hpp"

class Parada {
    private:
        Sala* sala = nullptr;
        int tempoEspera = -1;

    public:
        Parada(Sala* sala, const int tempoEspera);
        ~Parada();

        Sala* getSala();
        int getTempoEspera() const;
};

#endif
