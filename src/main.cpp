#include <iostream>
#include <vector>

#include "External.hpp"
#include "VariaveisGlobais.hpp"
#include "Sala.hpp"
#include "Entidade.hpp"
#include "Parada.hpp"

void lerDadosEntrada();
void dispararThreadsEntidades();
void* runThreadEntidade(void* args);
void esperarExecucaoThreads();
void limparVariaveisGlobais();
void printDadosEntrada();

int main() {
    lerDadosEntrada();
    printDadosEntrada();
    dispararThreadsEntidades();
    esperarExecucaoThreads();
    limparVariaveisGlobais();

    return 0;
}

void lerDadosEntrada() {
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

            Sala* salaAlvo = getSalaByID(identificadorSala);
            novaEntidade->adicionarParada(salaAlvo, tempoEsperaSala);
        }

        entidades.push_back(novaEntidade);
    }
}

void dispararThreadsEntidades() {
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

    passa_tempo(entidade->getId(), 0, entidade->getTempoEsperaInicial());

    for(Parada parada : caminho) {
        Sala* proximaSala = parada.getSala();
        Sala* salaAnterior = entidade->getSalaAtual();

        proximaSala->entrar(entidade);
        if(salaAnterior != nullptr) {
            salaAnterior->sair(entidade);
        }

        passa_tempo(entidade->getId(), entidade->getSalaAtual()->getId(), parada.getTempoEspera());
    }

    entidade->getSalaAtual()->sair(entidade);
    entidade->setSalaAtual(nullptr);

    return NULL;
}

void esperarExecucaoThreads() {
    for(Entidade* entidade : entidades) {
        pthread_join(*entidade->getIdThread(), NULL);
    }
}

void limparVariaveisGlobais() {
    for(unsigned int i = 0; i < salas.size(); i++) {
        delete salas[i];
    }

    for(unsigned int i = 0; i < entidades.size(); i++) {
        delete entidades[i];
    }
}

void printDadosEntrada() {
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
