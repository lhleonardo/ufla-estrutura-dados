typedef int Dado; 

class No {
    friend class fila;
    private:
        Dado dado; 
        No* proximo;
    public:
        No(Dado d = 0);
};


class fila {
    private:
        No* inicio;
        No* fim;
        int tamanho;	
    public:
        fila();
        void enfileira(Dado valor);
        Dado desenfileira();
        Dado espia();
};
