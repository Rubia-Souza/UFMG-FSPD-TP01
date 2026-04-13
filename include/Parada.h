#ifndef PARADA_H
#define PARADA_H

#include "Sala.h"

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
