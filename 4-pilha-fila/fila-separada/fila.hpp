#ifndef FILA_HPP

#define FILA_HPP

typedef int Dado; 

class No {
    friend class Fila;
    private:
        Dado dado; 
        No* proximo;
    public:
        No(Dado d = 0);
};

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

        void imprime();

        inline bool vazia();
        unsigned int qtdElementos() { return this->tamanho;}
};

#endif