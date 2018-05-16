/**
* Mostre como uma pilha pode ser implementada utilizando duas filas. 
* Analise o tempo das operações de empilhar (PUSH) e desempilhar (POP)
*
*/

#include "fila-separada/fila.hpp"

#include <iostream>

using namespace std;

class Pilha {
    private:
        Fila* registros;
        bool pegaTopo(Fila* aux, Dado* valor, bool removeTopo = false);
    public:
        Pilha();
        ~Pilha();

        void empilha(Dado valor);

        Dado desempilha();
        Dado espia();
        void imprime();
        void limpaPilha();
};

Pilha::Pilha() {
    this->registros = new Fila;
}

Pilha::~Pilha() {
    delete this->registros;
}

void Pilha::empilha(Dado valor) {
    this->registros->enfileira(valor);
}

bool Pilha::pegaTopo(Fila* aux, Dado *valor, bool removeTopo) {

    cout << "pegaTopo(): inicio" << endl;
    bool temTopo = false;    
    
    while(this->registros->qtdElementos() > 0) {
        if (this->registros->qtdElementos() == 1) {
            *valor = this->registros->espia();
            temTopo = true;

            if (not removeTopo) {
                aux->enfileira(this->registros->desenfileira());
            }
        } else {
            aux->enfileira(this->registros->desenfileira());
        }
    }

    while(aux->qtdElementos() > 0) {
        this->registros->enfileira(aux->desenfileira());
    }

    return temTopo;
}

Dado Pilha::espia() {
    Fila aux;
    Dado topo;
    if (pegaTopo(&aux, &topo)){
        return topo;
    }   
    return -1;
}

Dado Pilha::desempilha() {
    Fila aux;
    Dado topo = -1;
    // cout << "desempilha(): Vai ver se o topo existe" << endl;
    // if (pegaTopo(&aux, &topo, true)) {
    //     return topo;
    // }

    while(this->registros->qtdElementos()) {
        if (this->registros->qtdElementos() == 1) {
            topo = this->registros->espia();
        }
        aux.enfileira(this->registros->desenfileira());
    }

    while(aux.qtdElementos()) {
        this->registros->enfileira(aux.desenfileira());
    }

    return topo;
}

void Pilha::imprime() {
    this->registros->imprime();
}

int main() {
    Pilha pilha;

    pilha.empilha(1);
    pilha.empilha(2);
    pilha.empilha(3);
    pilha.empilha(4);
    pilha.empilha(5);

    pilha.imprime();

    cout << "Valor desempilhado: " << pilha.desempilha() << endl;

    pilha.imprime();
    return 0;
}