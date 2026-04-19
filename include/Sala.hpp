#ifndef SALA_HPP
#define SALA_HPP

#include <pthread.h>

#include "Entidade.hpp"

class Entidade;

/**
 * @brief Salas são onde as entidades entram em conjunto e passam
 * o tempo. Elas são responsáveis por controlar a sincronização
 * de entrada e saida das threads, durante o caminho seguido elas.
 * 
 */
class Sala {
    private:
        int id = -1;
        /// @brief Representa a quantidade de Entidades que estão dentro da sala no momento.
        int quantidadeEntidadesPresentes = -1;
        /// @brief Representa a quantidade de Entidades que estão esperando para entrar na sala.
        int quantidadeEntidadesEmEspera = -1;
        /// @brief Indica se a sala esta vazia. Ou seja, sem Entidades dentro dela.
        bool estaVazia = false;
        /// @brief Indica se as Entidades que estão esperando para entrar podem entrar na sala.
        bool entradaDisponivel = false;

        /// @brief Mutex que sincroniza a entrada e saida das Entidades.
        pthread_mutex_t mutexSala;
        /// @brief Condição que notifica as Entidades em espera que a entrada na sala está disponível.
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
