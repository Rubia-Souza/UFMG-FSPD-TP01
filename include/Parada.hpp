#ifndef PARADA_HPP
#define PARADA_HPP

#include "Sala.hpp"

class Sala;

/**
 * @brief Representa uma Parada que deve ser feita no caminho
 * de uma Entidade, associando uma Sala a um tempo de espera.
 * 
 */
class Parada {
    private:
        /// @brief A sala onde a entidade deve entrar.
        Sala* sala = nullptr;
        /// @brief O tempo que a entidade deve esperar dentro da sala.
        int tempoEspera = -1;

    public:
        /**
         * @brief Construtor que cria um novo objeto Parada.
         * 
         * @param sala A sala onde a entidade deverar entrar e esperar.
         * @param tempoEspera O tempo que a entidade deve esperar dentro da sala.
         */
        Parada(Sala* sala, const int tempoEspera);

        /**
         * @brief Destrutor que destroi o objeto Parada.
         * 
         */
        ~Parada();

        /**
         * @brief Método que retorna a sala que a entidade deve esperar.
         * 
         * @return Sala* A sala que a entidade deve esperar.
         */
        Sala* getSala();

        /**
         * @brief Método que retorna o tempo que a entidade deve esperar na sala.
         * 
         * @return int O tempo que a entidade deve esperar na sala.
         */
        int getTempoEspera() const;
};

#endif
