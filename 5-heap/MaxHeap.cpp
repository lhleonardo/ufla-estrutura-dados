#include <iostream>

using namespace std;

typedef int Dado;

class MaxHeap {
    public:
        MaxHeap(unsigned int capacidade);
        MaxHeap(int vetor[], unsigned int qtdElementos, unsigned int capacidade = 0);
        
        void imprime();
    private: 
        Dado* valores;
        unsigned int qtdElementos;
        unsigned int capacidade;
        
        inline unsigned int pai(unsigned int posicao);
        inline unsigned int filhoEsquerda(unsigned int posicao);
        inline unsigned int filhoDireita(unsigned int posicao);
        
        void arruma();
        void corrigeSubindo(unsigned int posicao);
        void corrigeDescendo(unsigned int posicao);
};

MaxHeap::MaxHeap(unsigned int capacidade) {
    this->capacidade = capacidade;
    this->qtdElementos = 0;
    this->valores = new Dado[this->capacidade];
}

MaxHeap::MaxHeap(int vetor[], unsigned int qtdElementos, unsigned int capacidade) {
    this->capacidade = capacidade == 0 ? qtdElementos : capacidade;
    this->qtdElementos = qtdElementos;
    this->valores = new Dado[this->capacidade];
    
    for(unsigned int i = 0; i < qtdElementos; i++) {
        valores[i] = vetor[i];
    }
    
    arruma();
}

inline unsigned int MaxHeap::pai(unsigned int posicao) {
    return (posicao-1) / 2;
}

inline unsigned int MaxHeap::filhoDireita(unsigned int posicao) {
    return 2*posicao + 2;
}

inline unsigned int MaxHeap::filhoEsquerda(unsigned int posicao) {
    return 2*posicao + 1;
}

void MaxHeap::arruma() {
    for(int i = (this->qtdElementos/2 -1); i >= 0; i--) {
        //cout << "asdfasfd " << i << endl;
        corrigeDescendo(i);
    }
}

void MaxHeap::corrigeDescendo(unsigned int atual) {
    unsigned int direita = filhoDireita(atual);
    unsigned int esquerda = filhoEsquerda(atual);
    
    unsigned int posicaoMaior;
    
    cout << "--------------------------------" << endl;
    cout << "direita: " << direita << endl;
    cout << "esquerda: " << esquerda << endl;
    
    cout << this->valores[direita] << " < " << this->valores[atual] << "?" << endl;
    cout << this->valores[esquerda] << " < " << this->valores[atual] << "?" << endl;
    
    if (direita < this->qtdElementos and 
            this->valores[direita] > this->valores[atual]) {
        posicaoMaior = direita;
    } else {
        posicaoMaior = atual;
    }
    
    if (esquerda < this->qtdElementos and 
            this->valores[esquerda] > this->valores[posicaoMaior]) {
        posicaoMaior = esquerda;
    }
    
    if (posicaoMaior != atual) {
        cout << "vai trocar " << this->valores[posicaoMaior] << " com " << this->valores[atual] << endl; 
        swap(this->valores[posicaoMaior], this->valores[atual]);
        corrigeDescendo(posicaoMaior);
    }
}

void MaxHeap::imprime() {
    cout << "[";
    for(unsigned int i = 0; i < this->qtdElementos; i++) {
        cout << this->valores[i];
        if (i != this->qtdElementos - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

int main() {
    int valores[] = {1, 9, 4, 3, 5, 11, 7, 14, 15, 19, 30, 12, 20};
    int tamanho = 13;
    
    cout << "qye" << endl;
    MaxHeap heap(valores, tamanho);
    heap.imprime();
    return 0;
}
