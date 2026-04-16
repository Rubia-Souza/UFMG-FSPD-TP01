#include <iostream>
#include <vector>

#include "External.hpp"
#include "Sala.hpp"
#include "Entidade.hpp"
#include "Parada.hpp"

void lerDadosEntrada(std::vector<Sala*>& salas, std::vector<Entidade*>& entidades);
Sala* getSalaByID(const int id, std::vector<Sala*>& salas);
void dispararThreadsEntidades(std::vector<Entidade*>& entidades);
void* runThreadEntidade(void* args);
void esperarExecucaoThreads(std::vector<Entidade*>& entidades);
void limparDadosAlocados(std::vector<Sala*>& salas, std::vector<Entidade*>& entidades);
void printDadosEntrada(std::vector<Sala*>& salas, std::vector<Entidade*>& entidades);

int main() {
    std::vector<Sala*> salas;
    std::vector<Entidade*> entidades;

    lerDadosEntrada(salas, entidades);
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

void esperarExecucaoThreads(std::vector<Entidade*>& entidades) {
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

void printDadosEntrada(std::vector<Sala*>& salas, std::vector<Entidade*>& entidades) {
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
