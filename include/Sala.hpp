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
        /**
         * @brief Construtor que cria um novo objeto Sala.
         * 
         * @param id O ID que identifica uma sala em específico.
         */
        Sala(const int id);

        /**
         * @brief Destrutor que destroi o objeto Sala.
         * 
         */
        ~Sala();

        /**
         * @brief Método para permitir uma Entidade entrar na Sala.
         * É responsável por realizar a sincronização de entrada e 
         * saída das entidades, além de verificar as condições para
         * permitir a entrada.
         * 
         * Além disso, ela define a sala atual da entidade como a
         * respectiva sala que o método está sendo chamado.
         * 
         * @param entidadeEntrando A entidade que entrará na sala.
         */
        void entrar(Entidade* entidadeEntrando);

        /**
         * @brief Método para permitir uma Entidade sair da Sala.
         * É responsável por auxiliar na sincronização da entrada
         * e saida das entidades das salas, além de definir a sala
         * anteriormente ocupada pela entidade.
         * 
         * @param entidadeSaindo A entidade que sairá da sala.
         */
        void sair(Entidade* entidadeSaindo);

        /**
         * @brief Método que retorna o ID da sala.
         * 
         * @return int O ID da sala.
         */
        int getId() const;
    
    private:
        /**
         * @brief Indentifica se é possível formar um trio de entidades
         * com o conjunto de threads em espera para entrar nesta sala.
         * 
         * @return true Se for possível formar um trio de entidades para entrar na sala.
         * @return false Se não for possível formar um trio de entidades para entrar na sala.
         */
        bool ehPossivelFormarUmTrio() const;

        /**
         * @brief Indentifica se as condições para entrar na sala foram
         * atendidas. Ou seja, a sala está vazia e é possível formar um
         * trio de entidades para entrar.
         * 
         * @return true Se as condições para entrar na sala foram atendidas.
         * @return false Se as condições para entrar na sala não foram atendidas.
         */
        bool ehPossivelEntrarNaSala() const;

        /**
         * @brief Identifica se a sala ficou disponível para novas entidades
         * entrarem logo após a última entidade do trio anterior sair da sala.
         * 
         * @return true Se a sala ficou disponível para o próximo trio entrar.
         * @return false Se a sala ainda não ficou disponível para o próximo trio entrar.
         */
        bool salaFicouDisponivel() const;
};

#endif
