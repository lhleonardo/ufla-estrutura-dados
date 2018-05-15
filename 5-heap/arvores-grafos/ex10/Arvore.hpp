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
        bool filhosCheios();
        void inicializa();
    public:
        // cria um No que, por padrao, ja tem espaco para 5 filhos
        No(const Dado valor, unsigned int qtdFilhos = 5);
        No(const Dado valor, No** filhos, unsigned int qtdFilhos, unsigned int capacidade = 0);
        ~No();

        void adicionaFilho(Dado valor);

        void removeFilho(Dado valor);

        bool procura(Dado valor, int *posicao);
};

class Arvore {
    private:
        No* raiz;
    public:
        Arvore();
        Arvore(No* raiz);
        ~Arvore();

        // por padrao sempre adiciona no filho do ultimo noh da arvore
        void add(No* elemento);
        // adiciona o elemento como filho de raizDoElemento, que eh um No ja informado por padrao
        void add(No* raizDoElemento, No* elemento);

        Dado remove(No* elemento);
        Dado remove(unsigned int posicaoValida);

        No* procura(Dado valor);
};

#endif