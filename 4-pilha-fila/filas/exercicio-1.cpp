#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado; 

class No {
    friend class Fila;
    private:
        Dado dado; 
        No* proximo;
    public:
        No(Dado d = 0);
};

No::No(Dado d): dado(d) {}

class Fila {
    private:
        No* inicio;
        No* fim;
        int tamanho;	
    public:
        Fila();
        void enfileira(Dado valor);
        Dado desenfileira();
        Dado espia();

        inline bool vazia();
};

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
        cerr << "Nao ha elementos para desenfileirar!" << endl;
        //exit(EXIT_FAILURE);
    }
    
    return -1;
}

Dado Fila::espia() {
    return this->inicio->dado;
}

int main() {
    Fila fila;
    fila.enfileira(10);
    fila.enfileira(20);
    fila.enfileira(30);
    fila.enfileira(40);
    fila.enfileira(50);

    cout << "Vazia? " << (fila.vazia() ? "Sim" : "Nao") << endl;

    while(not fila.vazia()) {
        cout << fila.desenfileira() << endl;
    }

    cout << "Vazia? " << (fila.vazia() ? "Sim" : "Nao") << endl;
    
    fila.enfileira(1);
    fila.enfileira(2);
    fila.enfileira(3);
    fila.enfileira(4);
    
    //~ fila.desenfileira();
    cout << "Vazia? " << (fila.vazia() ? "Sim" : "Nao") << endl;
    
    cout << fila.espia() << endl;
    

    return 0;
}
