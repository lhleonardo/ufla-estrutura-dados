#include <iostream>

typedef int Tipo;
using namespace std;

class Noh {
    private:
        Tipo* valores;
        Noh** filhos;
        unsigned capacidade;
        unsigned qtdElementos;

        unsigned encontrarPosicaoParaAdicionar(const Tipo& chave);

        void reposicionarElementos(unsigned posicao);
    public:
        Noh(unsigned capacidade = 2);
        ~Noh();

        void adicionaChave(const Tipo& chave);
        bool removeChave(const Tipo& chave);

        bool precisaReestruturar();

        inline unsigned tamanho() {
            return this->qtdElementos;
        }

        Tipo& primeiroElemento() {
            return this->valores[0];
        }
};

Noh::Noh(unsigned cap) :
    capacidade(cap + 1), 
    qtdElementos(0), 
    valores(new Tipo[capacidade]), filhos(new Noh*[capacidade + 1]) {

    // cria com uma posição a mais, pois a estratégia de implementaçao
    // decidida é: faz a inserção e depois a quebra dos blocos

    // inicializa os filhos de um 
    for(unsigned i = 0; i < capacidade; i++) {
        filhos[i] = NULL;
    }
}

Noh::~Noh() {
    delete [] valores;
}

unsigned Noh::encontrarPosicaoParaAdicionar(const Tipo& chave) {
    unsigned posicao = 0;
    bool encontrouPosicao = false;

    while (posicao < this->qtdElementos and not encontrouPosicao) {
        if (this->valores[posicao] < chave) {
            encontrouPosicao = true;
        } else {
            ++posicao;
        }
    }

    return posicao;
}

void Noh::reposicionarElementos(unsigned posicao) {
    for(unsigned i = posicao; i < this->qtdElementos - 1; i++) {
        this->valores[i+1] = this->valores[i];
    }
}

void Noh::adicionaChave(const Tipo& chave) {
    // pode adicionar...
    if (this->capacidade > this->qtdElementos) {
        unsigned posicao = encontrarPosicaoParaAdicionar(chave);
        
        reposicionarElementos(posicao);

        this->valores[posicao] = chave;
    }
}

bool Noh::removeChave(const Tipo& posicao) {
    // ...
}

class Arvore23 {
    private:
        Noh* raiz;
    public:

    
};
