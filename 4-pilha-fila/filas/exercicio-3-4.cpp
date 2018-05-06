#include <iostream>

using namespace std;

typedef char Dado;

class No {
    friend class Pilha;
    private:
        No* proximo;
        Dado dado;
    public:
        No(Dado dado, No* proximo = NULL);
};

No::No(Dado d, No* proximo): dado(d) {
    this->proximo = proximo;
}

class Pilha {
    public:
        Pilha ();
        ~Pilha ();

        void empilha (Dado valor);
        Dado desempilha ();

        void imprime ();
        int espia ();

        void limpaPilha ();
        
        void exercicio3 ();
        void exercicio4 ();
        //~ void exercicio5 ();
    private:
        No* topo;
        unsigned int qtdElementos;
};

Pilha :: Pilha () {
    topo = NULL;
    qtdElementos = 0;
}

Pilha :: ~Pilha () {
    No *aux;
    for (unsigned int i = 0 ; i < qtdElementos ; i++) {
        aux = topo;
        topo = aux->proximo;
        delete aux;
    }
}

void Pilha :: empilha  (Dado valor) {
    if (qtdElementos == 0){
        No *aux = new No(valor);
        topo = aux;
        qtdElementos++;
    }else{
        No* aux = new No(valor);
        aux->proximo = topo;
        topo =  aux; 
        qtdElementos ++ ;
    }
}

Dado Pilha :: desempilha () {
    int removido=topo->dado;
    if (qtdElementos == 1) {
        delete topo;
        topo = NULL;
        qtdElementos--;
    } else {
        No *aux;
        aux = topo->proximo;
        delete topo;
        topo = aux;
        qtdElementos --;
    }
    return removido;
 }

void Pilha::imprime () {
    //  DEBUG DEBUG DEBUG DEBUG 
    No *aux =topo;
    while (aux != NULL){
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
}

int Pilha :: espia (){
    return topo->dado;
}

void Pilha :: limpaPilha () {
    while (topo != NULL){
        cout << desempilha () << " ";
    }
}

void Pilha::exercicio4() {
    No* atual = topo;
    Dado valor = espia();
    int contador1 = 0, contador2 = 0, contador3 = 0;
    
    int termos = qtdElementos, inuteis = 2;
    
    while(atual != NULL and valor != 'B') {
        valor = desempilha();
        if (valor == 'A') {
            contador1++;
        }
        
        atual = topo;
    }
    
    desempilha();
    
    atual = topo;
    valor = espia();
    
    while(atual != NULL and valor != 'B') {
        if (valor == 'C') {
            contador2++;
        }
        
        valor = desempilha();
        atual = topo;
    }
    
    atual = topo;
    valor = espia();
    
    while(atual != NULL) {
        if (valor == 'A') {
            contador3++;
        }
        valor = desempilha();
        atual = topo;
    }
    
    if ((contador1 + contador2 + contador3 + inuteis) == termos) {
        double segundoTermo = contador2 / double(2);
        if (segundoTermo == contador1 and segundoTermo == contador3) {
            cout << "verdadeiro" << endl;
        } else {
            cout << "falso" << endl;
        }
    } else {
        cout << "falso" << endl;
    }
    
}

int main () {
    Pilha p;
    p.empilha('A');
    p.empilha('A');
    p.empilha('B');
    p.empilha('C');
    p.empilha('C');
    p.empilha('C');
    p.empilha('C');
    p.empilha('B');
    p.empilha('A');
    p.empilha('A');
    
    p.exercicio4();
    return 0;
}
