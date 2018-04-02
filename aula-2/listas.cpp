#include <iostream>

using namespace std;

typedef int Dado;

class No {
    friend class Lista;
    private:
        Dado dado;
        No* proximo;
        No* anterior;
    public: 
        No(const No& outro);
        
        Dado valor();
        No(Dado d = 0);
};

No::No(const No& outro) {
    cout << "construtor de copia no" << endl;
    this->dado = outro.dado;
    
    this->anterior = outro.anterior;
    this->proximo = outro.proximo;
}

No::No(Dado d) : dado(d) {
    this->proximo = NULL;
    this->anterior = NULL;
}

Dado No::valor() { return dado; }

class Lista {
    private:
        No* primeiro;
        No* ultimo;
        unsigned int qtdElementos;
    public: 
        Lista();
        Lista(const Lista& outra);
        ~Lista();
        
        void insere(Dado dado);
        void insereNoFim(Dado dado);
        void insereNoInicio(Dado dado);
        void insereNaPosicao(unsigned int posicao, Dado dado);
        
        void imprime();
        void imprimeReverso();
        
        inline bool vazia();
        inline bool posicaoValida(unsigned int posicao);
        
        void remove(unsigned int posicao);
        unsigned int procura(Dado valor); // retorna a posicao
        No* acessaPosicao(unsigned int posicao); 
        
        Lista& operator = (const Lista& outra); 
        
        void trocaPosicoes(unsigned int x, unsigned int y); 
        
};

Lista::Lista() {
    primeiro = NULL;
    ultimo = NULL;
    qtdElementos = 0;
}

Lista::Lista(const Lista& outra) {
    cout << "construtor de copia lista" << endl;
    
    this->qtdElementos = outra.qtdElementos;
    
    No primeiro = (*outra.primeiro);
    No ultimo = (*outra.ultimo);
    
    this->primeiro = &primeiro;
    this->ultimo = &ultimo;
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
        // primeiro elemento da lista
        primeiro = elemento;
        ultimo = elemento;
    } else {
        // Se o elemento A eh o ultimo elemento da lista, e o elemento 
        // B eh inserido no fim, de forma com que o A seja antecessor a 
        // B, entao:
        // 
        // [... , A, B] => A <-> B
        // A tem como sucessor B e B por sua vez tem como antecessor A
        
        // A -> B
        ultimo->proximo = elemento;
        // A <- B
        elemento->anterior = ultimo;
        ultimo = elemento;
    }
    
    qtdElementos++;
}

void Lista::insereNoInicio(Dado dado) {
    No* elemento = new No(dado);
    
    if (vazia()) {
        // primeiro elemento da lista vazia
        primeiro = elemento;
        ultimo = elemento;
    } else {
        // Seja uma lista que possui o elemento A no seu inicio, e agora
        // o elemento B devera ser o novo primeiro elemento, pode-se dizer
        // que: 
        // 
        // 1) A tera como antecessor B
        // 2) B tera como sucessor A
        
        // B -> A
        elemento->proximo = primeiro;
        // B <- A
        primeiro->anterior = elemento;
        primeiro = elemento;
    }
    qtdElementos++;
}

inline bool Lista::posicaoValida(unsigned int posicao) {
    return posicao >=0 and posicao <= qtdElementos;
}

void Lista::insereNaPosicao(unsigned int posicao, Dado dado) {
    No* elemento = new No(dado);
    
    if (posicaoValida(posicao)) {
        if (vazia()) { // ou ta vazia
            primeiro = elemento;
            ultimo = elemento;
        } else if (posicao == 0) { // ou ta no inicio
            elemento->proximo = primeiro;
            primeiro = elemento;
        } else if (posicao == qtdElementos) { // ou ta no fim
            // Olhar o metodo: insereNoFim();
            ultimo->proximo = elemento;
            elemento->anterior = ultimo;
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
            
            // Seja os elementos A e B, em sequencia, e o elemento C, que
            // deve ser adicionado entre A e B. A disposicao destes 
            // elementos, em relacao a seus antecessores e sucessores, sera:
            //
            // 1) O elemento A nao tem antecessor e seu sucessor sera C
            // 2) O elemento B nao tera sucessor e seu antecessor sera C
            // 3) O elemento C tera A como antecessor e B como sucessor,
            //
            // Assim ficando: A <-> C <-> B
            elemento->proximo = aux->proximo;
            elemento->anterior = aux;
            elemento->proximo->anterior = elemento;
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
        
        // Seja os elementos A, B e C, dispostos assim em sequencia, e o 
        // elemento B eh removido desta lista, pode-se afirmar que, em sua
        // nova disposicao:
        //
        // 1) A tera como sucessor C;
        // 2) C tera como antecessor A
        
        No* selecionado = aux->proximo;
        // A -> C
        aux->proximo = selecionado->proximo;
        // A <- C
        aux->proximo->anterior = aux;        
        delete selecionado;
        qtdElementos--;        
    } else {
        cerr << "Não foi possivel realizar a remocao. Posicao invalida ou inexistente" << endl;
    }
}

unsigned int Lista::procura(Dado elemento) {
    No* atual = primeiro;
    unsigned int contador = 0;
    
    while(atual != NULL) {
        if (atual->dado == elemento) {
            return contador;
        }
        
        contador++;
        atual = atual->proximo;
    }
    
    return -1;
}

void Lista::imprimeReverso() {
    cout << "[";
    
    No* atual = ultimo;
    
    while(atual != NULL) {
        cout << atual->dado;
       
        if (atual->anterior != NULL) cout << ", ";
        
        //cout << endl;
        atual = atual->anterior;
    }
    
    cout << "]";
}

No* Lista::acessaPosicao(unsigned int posicao) {
    if(posicaoValida(posicao)) {
        No* elemento = primeiro;
        
        for(unsigned int i = 0; i < posicao; i++)
            elemento = elemento->proximo;
        
        return elemento;
    } else {
        cerr << "Posicao invalida!" << endl;
        return NULL;
    }
}

void Lista::trocaPosicoes(unsigned int x, unsigned int y) {
    No* posX = this->acessaPosicao(x);
    No* anteriorX = posX->anterior;
    No* proximoX = posX->proximo;
    
    No* posY = this->acessaPosicao(y);
    No* anteriorY = posY->anterior;
    No* proximoY = posY->proximo;
    
    
    posX->anterior = posY;
    posY->anterior = posX;
    posX->proximo = posY->proximo;
    posY->anterior = proximoX;
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
    
    lista.imprime();
    
    cout << "Digite as posicoes que deverao ser trocadas: ";
    unsigned int x, y;
    
    cin >> x >> y;
    
    lista.trocaPosicoes(x, y);
    lista.imprime();
    
    return 0;
}
