#ifndef MIN_HEAP_H

#define MIN_HEAP_H

typedef int Dado;

class Heap {
    private:
        Dado* elementos;
        unsigned int qtdElementos;
        unsigned int capacidade;
        
        void arruma();
        
        void corrigeDescendo(unsigned int posicao);
        void corrigeSubindo(unsigned int posicao);
        
        int pai(unsigned int posicao);
        int filhoEsquerda(unsigned int posicao);
        int filhoDireita(unsigned int posicao);
    public:
        Heap(unsigned int capacidade = 100);
        Heap(Dado* valores, unsigned int qtdElementos, unsigned int capacidade = 0);
        
        void imprime();
        void heapsort();
        
        void adiciona(Dado& valor);
};
#endif
