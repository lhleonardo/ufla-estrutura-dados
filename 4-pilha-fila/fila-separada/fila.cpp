#include "fila.hpp"

#include <iostream>

using namespace std;

No::No(Dado d): dado(d) {}

Fila::Fila() {
    this->inicio = NULL;
    this->fim = NULL;
    this->tamanho = 0;
}

inline bool Fila::vazia() {
    return this->tamanho == 0;
}

void Fila::enfileira(Dado valor) {
    No* elemento = new No(valor);

    if (this->fim != NULL) {
        cout << "Ultimo: " << this->fim->dado << endl;;
        this->fim->proximo = elemento;
    }
    
    if (vazia()) {
        this->inicio = elemento;
    }
    this->fim = elemento; 
    this->tamanho++;
}

Dado Fila::desenfileira() {
    if (not vazia()) {
        No* elemento = this->inicio;
        
        Dado valor = elemento->dado;
        this->inicio = elemento->proximo;

        if (vazia()) {
            this->inicio = NULL;
        }

        delete elemento;
        this->tamanho--;

        if (this->tamanho == 1) {
            this->inicio = this->fim;
        }

        return valor;
    } else {
        throw "Não há elementos para desenfileirar";
        //exit(EXIT_FAILURE);
    }
    
    return -1;
}

Dado Fila::espia() {
    return this->inicio->dado;
}

void Fila::imprime() {
    cout << "[";
    No* atual = inicio;
    while(atual != NULL) {
        cout << atual->dado;
        if (atual->proximo != NULL) {
            cout << ", ";
        } 
        atual = atual->proximo;
    }
    cout << "]" << endl;
}