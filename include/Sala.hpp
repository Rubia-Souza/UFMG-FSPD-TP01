#ifndef SALA_HPP
#define SALA_HPP

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
