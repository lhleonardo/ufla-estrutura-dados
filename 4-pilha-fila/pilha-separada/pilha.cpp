#ifndef PILHA_H
#define PILHA_H

#include <iostream>

using namespace std;

template <class Type> class No {
    private:    
        No* proximo;
        Type dado;
};


template <class Type> class Pilha {
    private: 
        No<Type>* topo;
        unsigned int qtdElementos;
    public:
        Pilha();
        ~Pilha();

        void empilha(Type valor);
        
        Type desempilha();
        Type espia();

        void depura();

        inline bool vazia() {
            return this->qtdElementos == 0;
        }
        inline int tamanho() {
            return this->qtdElementos;
        }
};

bool Pilha::comparaIgualdade(const Pilha& outra) {
    if (this->qtdElementos != outra.qtdElementos) {
        return false;
    }

    bool iguais = true;

    // ou tamanhoPilhas = outra.qtdElementos;
    unsigned int tamanhoPilhas = this->qtdElementos;    
    Dado valor1, valor2;

    for(unsigned int i = 0; i < tamanhoPilhas and iguais; i++) {
        valor1 = this->desempilha();
        valor2 = outra.desempilha();

        if (valor1 != valor2) {
            iguais = false;
        }
    }

    return iguais;
}

#endif