#ifndef ENTIDADE_HPP
#define ENTIDADE_HPP

#include <vector>
#include <pthread.h>

#include "Sala.hpp"
#include "Parada.hpp"

class Sala;
class Parada;

/**
 * @brief Uma Entidade é uma representação de uma thread associada
 * responsável por realizar a simulação de movimento, entrando e 
 * saindo das salas que compõem o seu caminho.
 * 
 */
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
        /**
         * @brief Construtor que cria um novo objeto Entidade.
         * 
         * @param id O ID que identifica uma entidade em específico.
         * @param tempoEsperaInicial O tempo que a entidade espera inicialmente antes de entrar no tabuleiro.
         * @param quantidadeSalasCaminho A quantidade de salas que compõem o caminho que a entidade deve seguir.
         */
        Entidade(const int id, const int tempoEsperaInicial, const int quantidadeSalasCaminho);

        /**
         * @brief Destrutor que destroi o objeto Entidade.
         * 
         */
        ~Entidade();

        /**
         * @brief Método que adiciona uma Parada ao caminho da entidade.
         * 
         * @param sala A sala onde a entidade deverá entrar.
         * @param tempoEspera O tempo que a entidade deve esperar nesta respectiva sala.
         */
        void adicionarParada(Sala* sala, const int tempoEspera);

        /**
         * @brief Método que retorna o ID da entidade.
         * 
         * @return int O ID da entidade.
         */
        int getId() const;

        /**
         * @brief Método que retorna o tempo de espera inicial da entidade.
         * 
         * @return int O tempo de espera inicial da entidade.
         */
        int getTempoEsperaInicial() const;

        /**
         * @brief Método que retorna a quantidade de salas no caminho da entidade.
         * 
         * @return int A quantidade de salas no caminho da entidade.
         */
        int getQuantidadeSalasCaminho() const;

        /**
         * @brief Método que retorna o caminho que a entidade deve seguir.
         * 
         * @return std::vector<Parada> O caminho que a entidade deve seguir.
         */
        std::vector<Parada> getCaminho() const;

        /**
         * @brief Método que retorna a sala que a entidade está ocupando atualmente.
         * 
         * @return Sala* A referência para a sala que a entidade está ocupando atualmente.
         */
        Sala* getSalaAtual();

        /**
         * @brief Método que define a sala que a entidade passará a ocupar. Automaticamente,
         * definine a sala que estava antes como a sala anterior.
         * 
         * @param sala A sala que a entidade entrará.
         */
        void setSalaAtual(Sala* sala);

        /**
         * @brief Método que retorna a sala anterior que a entidade estava ocupando.
         * 
         * @return Sala* A referência para a sala que a entidade estava ocupando anteriormente.
         */
        Sala* getSalaAnterior();

        /**
         * @brief Método que define a sala que a entidade estava ocupando anteriormente.
         * 
         * @param sala A sala que a entidade estava ocupando anteriormente.
         */
        void setSalaAnterior(Sala* sala);

        /**
         * @brief Método que retorna o ID da thread associada a entidade.
         * 
         * @return pthread_t* A referência ao ID da thread associada a entidade.
         */
        pthread_t* getIdThread();

        /**
         * @brief Método que define o ID da thread que será associada a entidade.
         * 
         * @param id O ID da thread que será associada a entidade.
         */
        void setIdThread(pthread_t id);
};

#endif
