#ifndef SALA_H
#define SALA_H

class Sala {
    private:
        int id = -1;
        int quantidadeEntidadesPresentes = -1;

    public:
        Sala(const int id);
        ~Sala();

        void entrar();
        void sair();

        int getId() const;
        int getQuantidadeEntidadesPresentes() const;
};

#endif
