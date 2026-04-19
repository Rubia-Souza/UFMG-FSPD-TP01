#include <iostream>
#include <vector>
#include <pthread.h>

#include "External.hpp"
#include "Sala.hpp"
#include "Entidade.hpp"
#include "Parada.hpp"

/**
 * @brief Função responsável por ler os dados de entrada e inicializar os vetores
 * de salas e entidades, instanciando os respectivos objetos com os valores lidos.
 * 
 * @param salas O vetor com as salas que as entidades podem entrar.
 * @param entidades O vetor em com as entidades que representam as threads.
 */
void lerDadosEntrada(std::vector<Sala*>& salas, std::vector<Entidade*>& entidades);

/**
 * @brief Encontra uma sala com o ID especificado no vetor de salas.
 * 
 * @param id O ID da sala que será buscada.
 * @param salas O vetor de salas onde ocorrerá a busca.
 * @return Sala* Uma referência para a sala encontrada ou nullptr caso não encontrada.
 */
Sala* getSalaByID(const int id, std::vector<Sala*>& salas);

/**
 * @brief Função que inicializa as threads de cada entidade e associa o ID da thread
 * a entidade.
 * 
 * @param entidades O vetor com as entidades que serão associadas às threads.
 */
void dispararThreadsEntidades(std::vector<Entidade*>& entidades);

/**
 * @brief Função executada por cada entidade que simula o movimento entre as salas.
 * 
 * @param args A entidade associada a thread em execução.
 * @return void* nullptr.
 */
void* runThreadEntidade(void* args);

/**
 * @brief Função que faz a main() esperar até o fim da execução de todas as threads.
 * 
 * @param entidades O vetor com as entidades em execução.
 */
void esperarExecucaoThreads(const std::vector<Entidade*>& entidades);

/**
 * @brief Função que desaloca as salas e entidades instanciadas.
 * 
 * @param salas O vetor com as salas.
 * @param entidades O vetor com as entidades.
 */
void limparDadosAlocados(std::vector<Sala*>& salas, std::vector<Entidade*>& entidades);

/**
 * @brief Função auxiliar que imprime os dados lidos na entrada e armazenados em cada
 * sala e entidade instanciada.
 * 
 * @param salas O vetor com as salas.
 * @param entidades O vetor com as entidades.
 */
void printDadosEntrada(const std::vector<Sala*>& salas, const std::vector<Entidade*>& entidades);

int main() {
    // O vetor de salas contém as salas em que as entidades podem entrar e sair durante a execução.
    std::vector<Sala*> salas;

    // O vetor de entidades contém as entidades que estão associadas, cada uma, a sua respectiva thread.
    std::vector<Entidade*> entidades;

    lerDadosEntrada(salas, entidades);
    // TODO: Remover print antes de enviar
    printDadosEntrada(salas, entidades);
    dispararThreadsEntidades(entidades);
    esperarExecucaoThreads(entidades);
    limparDadosAlocados(salas, entidades);

    return 0;
}

void lerDadosEntrada(std::vector<Sala*>& salas, std::vector<Entidade*>& entidades) {
    int quantidadeSalas = -1;
    int quantidadeThreads = -1;

    std::cin >> quantidadeSalas >> quantidadeThreads;

    for(int i = 0; i < quantidadeSalas; i++) {
        salas.push_back(new Sala(i + 1));
    }

    for(int i = 0; i < quantidadeThreads; i++) {
        int identificadorThread = -1;
        int tempoInicialEspera = -1;
        int quantidadeSalasCaminho = -1;

        std::cin >> identificadorThread >> tempoInicialEspera >> quantidadeSalasCaminho;

        Entidade* novaEntidade = new Entidade(identificadorThread, tempoInicialEspera, quantidadeSalasCaminho);
        for(int j = 0; j < novaEntidade->getQuantidadeSalasCaminho(); j++) {
            int identificadorSala = -1;
            int tempoEsperaSala = -1;

            std::cin >> identificadorSala >> tempoEsperaSala;

            Sala* salaAlvo = getSalaByID(identificadorSala, salas);
            novaEntidade->adicionarParada(salaAlvo, tempoEsperaSala);
        }

        entidades.push_back(novaEntidade);
    }
}

Sala* getSalaByID(const int id, std::vector<Sala*>& salas) {
    for(Sala* sala : salas) {
        if(sala->getId() == id) {
            return sala;
        }
    }

    return nullptr;
}

void dispararThreadsEntidades(std::vector<Entidade*>& entidades) {
    for(Entidade* entidade : entidades) {
        if(pthread_create(entidade->getIdThread(), NULL, runThreadEntidade, (void*) entidade) != 0) {
            std::cout << "[ERROR]: Erro ao criar thread para entidade de ID: " << entidade->getId() << "." << std::endl;
            throw "[ERROR]: Erro ao criar thread para entidade.";
        }
    }
}

void* runThreadEntidade(void* args) {
    Entidade* entidade = static_cast<Entidade*>(args);
    std::vector<Parada> caminho = entidade->getCaminho();

    // O tempo de espera inicial antes da entidade entrar no tabuleiro.
    passa_tempo(entidade->getId(), 0, entidade->getTempoEsperaInicial());

    // A entidade começa a percorrer o caminho dela.
    for(Parada parada : caminho) {
        Sala* proximaSala = parada.getSala();
        Sala* salaAnterior = entidade->getSalaAtual();

        // Tenta entrar na próxima sala. Neste ponto, ela pode entrar em espera.
        proximaSala->entrar(entidade);
        // Quando consegue entrar na próxima sala, ela sai da sala que estava anteriormente.
        if(salaAnterior != nullptr) {
            salaAnterior->sair(entidade);
        }

        // Passa o tempo até a próxima iteração.
        passa_tempo(entidade->getId(), entidade->getSalaAtual()->getId(), parada.getTempoEspera());
    }

    // A entidade saí da última sala.
    entidade->getSalaAtual()->sair(entidade);
    entidade->setSalaAtual(nullptr);

    return NULL;
}

void esperarExecucaoThreads(const std::vector<Entidade*>& entidades) {
    for(Entidade* entidade : entidades) {
        pthread_join(*entidade->getIdThread(), NULL);
    }
}

void limparDadosAlocados(std::vector<Sala*>& salas, std::vector<Entidade*>& entidades) {
    for(unsigned int i = 0; i < salas.size(); i++) {
        delete salas[i];
    }
    salas.clear();

    for(unsigned int i = 0; i < entidades.size(); i++) {
        delete entidades[i];
    }
    entidades.clear();
}

void printDadosEntrada(const std::vector<Sala*>& salas, const std::vector<Entidade*>& entidades) {
    std::cout << "============================" << std::endl;
    std::cout << "===== Salas: =====" << std::endl;
    for(Sala* sala : salas) {
        std::cout << "Sala: " << sala->getId() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "===== Entidades: =====" << std::endl;
    for(Entidade* entidade : entidades) {
        std::cout << "Entidade " << entidade->getId() << ":" << std::endl;
        std::cout << "\tTempo Espera Inicial: " << entidade->getTempoEsperaInicial() << "ds." << std::endl;

        std::vector<Parada> caminho = entidade->getCaminho();
        std::cout << "\tCaminho - Tamanho " << entidade->getQuantidadeSalasCaminho() << " salas:" << std::endl;
        for(Parada parada : caminho) {
            std::cout << "\t\tSala: " << parada.getSala()->getId() << " - tempo espera " << parada.getTempoEspera() << "ds." << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "============================" << std::endl;
}
