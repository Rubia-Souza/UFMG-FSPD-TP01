#include <iostream>

#include "Sala.h"
#include "Entidade.h"
#include "VariaveisGlobais.h"

void lerDadosEntrada();
void limparVariaveisGlobais();

int main() {
    lerDadosEntrada();

    std::cout << "===== Salas: =====" << std::endl;
    for(Sala* sala : salas) {
        std::cout << "Sala: " << sala->getId() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "===== Entidades: =====" << std::endl;
    for(Entidade* entidade : entidades) {
        std::cout << "Entidade: " << entidade->getId() << std::endl;
        std::cout << "\tTempo Espera Inicial: " << entidade->getTempoEsperaInicial() << std::endl;

        std::vector<Parada> caminho = entidade->getCaminho();
        std::cout << "\tCaminho: Tamanho " << caminho.size() << std::endl;
        for(Parada parada : caminho) {
            std::cout << "\t\tSala: " << parada.getSala()->getId() << " - tempo espera " << parada.getTempoEspera() << std::endl;
        }
    }
    std::cout << std::endl;

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

void limparVariaveisGlobais() {
    for(unsigned int i = 0; i < salas.size(); i++) {
        delete salas[i];
    }

    for(unsigned int i = 0; i < entidades.size(); i++) {
        delete entidades[i];
    }
}
