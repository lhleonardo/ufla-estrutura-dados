#ifndef ARVORE_HPP
#define ARVORE_HPP

typedef int Dado;

class No {
    private:
        Dado valor;
        No** filhos;
        unsigned int qtdFilhos;
        unsigned int capacidadeFilhos;

        void redimensiona(unsigned int novoTamanho);
        bool filhosCheios;
    
    public:
        No(const Dado valor);
        No(const Dado valor, No** filhos, unsigned int qtdFilhos, unsigned int capacidade = 0);
        ~No();

        void adicionaFilho(Dado valor);
};

class Arvore {
    private:
        No* raiz;
};

#endif