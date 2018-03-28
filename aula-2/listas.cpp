#include <iostream>

using namespace std;

typedef int Dado;

class No {
    friend class Lista;
    private:
        Dado dado;
        No* proximo;
    public: 
        No(Dado d = 0);
};

No::No(Dado d) : dado(d) {
    this->proximo = NULL;
}

class Lista {
    private:
        No* primeiro;
        No* ultimo;
        unsigned int qtdElementos;
    public: 
        Lista();
        ~Lista();
        void insere(Dado dado);
        void insereNoFim(Dado dado);
        void insereNoInicio(Dado dado);
        void insereNaPosicao(unsigned int posicao, Dado dado);
        void imprime();
        inline bool vazia();
        void remove(unsigned int posicao);
        bool posicaoValida(unsigned int posicao);
        int procura(Dado valor); // retorna a posicao
        void imprimeReverso();
        No* acessaPosicao(unsigned int posicao); 
};

Lista::Lista() {
    primeiro = NULL;
    ultimo = NULL;
    qtdElementos = 0;
}

Lista::~Lista() {
    delete primeiro;
    delete ultimo;    
}

inline bool Lista::vazia() {
    return primeiro == NULL;
}

void Lista::insere(Dado dado) {
    insereNoFim(dado);
}

void Lista::insereNoFim(Dado dado) {
    No* elemento = new No(dado);
    
    if (vazia()) {
        // primeiro elemento
        primeiro = elemento;
        ultimo = elemento;
    } else {
        ultimo->proximo = elemento;
        ultimo = elemento;        
    }
    
    qtdElementos++;
}

void Lista::insereNoInicio(Dado dado) {
    No* elemento = new No(dado);
    
    if (vazia()) {
        primeiro = elemento;
        ultimo = elemento;
    } else {
        elemento->proximo = primeiro;
        primeiro = elemento;
    }
    qtdElementos++;
}

bool Lista::posicaoValida(unsigned int posicao) {
    return posicao >=0 and posicao <= qtdElementos;
}

void Lista::insereNaPosicao(unsigned int posicao, Dado dado) {
    No* elemento = new No(dado);
    
    if (posicaoValida(posicao)) {
        if (vazia()) { // ou ta vazia
            primeiro = elemento;
            ultimo = elemento;
        } else if (posicao == 0) { // ou ta no inicio
            primeiro->proximo = elemento;
            primeiro = elemento;
        } else if (posicao == qtdElementos) { // ou ta no fim
            ultimo->proximo = elemento;
            ultimo = elemento;
        } else { // ou ta no meio da lista
            No* aux = primeiro;
            unsigned int pos;
            
            // para antes da posicao que deseja
            for(pos = 0; pos < (posicao - 1); pos++) 
                aux = aux->proximo;
            
            // coloca o elemento na frente do aux, fazendo
            // com que seu proximo elemento seja o proximo definido
            // pelo aux
            elemento->proximo = aux->proximo;
            aux->proximo = elemento;
        }
        qtdElementos++;
    } else {
        cerr << "Posição inválida ou inexistente!" << endl;
    }
}

void Lista::imprime() {
    No* aux = this->primeiro;
    
    cout << "[";
    while(aux != NULL) {
        cout << aux->dado;
        if (aux->proximo != NULL) cout << ", ";
        
        aux = aux->proximo;
    }
    cout << "]" << endl;
}

void Lista::remove(unsigned int posicao) {
    if(posicaoValida(posicao)) {
        No* aux = primeiro;
        
        for(unsigned int i = 1; i < (posicao-1); i++)
            aux = aux->proximo;
        
        No* selecionado = aux->proximo;
        
        aux->proximo = selecionado->proximo;
        delete selecionado;
        qtdElementos--;        
    } else {
        cerr << "Não foi possivel realizar a remocao. Posicao invalida ou inexistente" << endl;
    }
}

int main() {
    Lista lista;
    
    lista.insere(10);
    lista.insere(20);
    lista.insere(30);
    lista.insere(40);
    lista.insere(50);
    
    lista.insereNaPosicao(1, 15);
    lista.insereNaPosicao(3, 25);
    lista.insereNaPosicao(4, 28);
    
    lista.insereNoFim(55);
    
    
    lista.imprime();
    
    lista.insereNoInicio(5);
    
    lista.remove(6);
    
    lista.imprime();
    
    return 0;
}
