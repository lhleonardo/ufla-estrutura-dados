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
       No(Dado d = 0);
};

No::No(Dado d) : dado(d) {
    this->proximo = NULL;
    this->anterior = NULL;
}

class Lista {
    private:
        No* primeiro;
        No* ultimo;
        unsigned int qtdElementos;
        void apagaTudo();
        void trocaPosicaoFim(No* posX, No* posY);
        void trocaPosicaoInicio(No* posX, No* posY);
    public: 
        Lista();
        Lista(Dado* dados, unsigned int quantidade);
        Lista(const Lista& outra);
        ~Lista();
        
        inline bool vazia();
        inline bool posicaoValida(unsigned int posicao);

        void insere(Dado dado);
        void insereNoFim(Dado dado);
        void insereNoInicio(Dado dado);
        void insereNaPosicao(unsigned int posicao, Dado dado);
        
        void imprime();
        void imprimeReverso();
        
        void remove(unsigned int posicao);
        void remove(Lista& outra);

        No* acessaPosicao(unsigned int posicao); 
        int procura(Dado valor); // retorna a posicao

        void trocaPosicoes(unsigned int x, unsigned int y); 
        
        Lista divide(unsigned int n);
        
        Lista& operator+(const Lista& outra);
        Lista& operator+=(const Lista& outra); 
};

Lista::Lista() {
    primeiro = NULL;
    ultimo = NULL;
    qtdElementos = 0;
}

Lista::Lista(const Lista& outra) {
    primeiro = NULL;
    ultimo = NULL;
    qtdElementos = 0;
    
    No* atual = outra.primeiro;
    
    while(atual != NULL) {
        this->insere(atual->dado);
        atual = atual->proximo;        
    }
}

Lista::Lista(Dado* dados, unsigned int quantidade) {
    primeiro = NULL;
    ultimo = NULL;
    qtdElementos = 0;
    
    for(unsigned int i = 0; i < quantidade; i++)
        this->insere(dados[i]);
}

void Lista::apagaTudo() {
    No* atual = primeiro;
    No* temp;

    while(atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        delete temp;
    }
    
    qtdElementos = 0;
    primeiro = NULL;
    ultimo = NULL;
}


Lista::~Lista() {
    apagaTudo();
}

inline bool Lista::vazia() {
    return primeiro == NULL;
}

inline bool Lista::posicaoValida(unsigned int posicao) {
    return posicao >=0 and posicao <= qtdElementos;
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

void Lista::remove(unsigned int posicao) {
    if(posicaoValida(posicao)) {
        
        
        // Seja os elementos A, B e C, dispostos assim em sequencia, e o 
        // elemento B eh removido desta lista, pode-se afirmar que, em sua
        // nova disposicao:
        //
        // 1) A tera como sucessor C;
        // 2) C tera como antecessor A
        
        if (posicao == 0) {
            // primeiro
            No* elemento = primeiro;
            primeiro = elemento->proximo;
            elemento->anterior = NULL;
            delete elemento;
        } else if (posicao == (qtdElementos-1)) {
            // ultimo
            No* elemento = ultimo;
            ultimo = elemento->anterior;
            ultimo->proximo = NULL;
            delete elemento;
        } else {
            No* elemento = this->acessaPosicao(posicao);
            No* antecessor = elemento->anterior;
            antecessor->proximo = elemento->proximo;
            elemento->proximo->anterior = antecessor;
            delete elemento;
        }
        qtdElementos--;
    } else {
        cerr << "Não foi possivel realizar a remocao. Posicao invalida ou inexistente" << endl;
    }
}

void Lista::remove(Lista& outra) {
    No* atual = primeiro;
    unsigned int posicaoAtual = 0;
    bool apagou = false;
    
    while(atual != NULL) {
        if (apagou) {
            apagou = false;
            atual = primeiro;
            posicaoAtual = 0;
        }
        if (outra.procura(atual->dado) != -1) {
            this->remove(posicaoAtual);
            apagou = true;
        }
        
        atual = atual->proximo;
        posicaoAtual++;
    }
    
}

int Lista::procura(Dado elemento) {
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

void Lista::trocaPosicaoInicio(No* posX, No* posY) {
    No* proximoX = posX->proximo;
    No* anteriorY = posY->anterior;
    No* proximoY = posY->proximo;

    posX->anterior = anteriorY;
    anteriorY->proximo = posX;

    posX->proximo = proximoY;
    proximoY->anterior = posX;

    posY->proximo = proximoX;
    posY->anterior = NULL;

    primeiro = posY;
}

void Lista::trocaPosicaoFim(No* posX, No* posY) {
    No* anteriorY = posY->anterior;
    posY->anterior = posX->anterior;
    posX->anterior->proximo = posY;
    posY->proximo = posX->proximo;

    posX->proximo = NULL;
    posX->anterior = anteriorY;
    anteriorY->proximo = posX;
    ultimo = posX;           
}

void Lista::trocaPosicoes(unsigned int pos1, unsigned int pos2) {
    unsigned 
    int x, y;
    if (pos1 > pos2) {
        y = pos1;
        x = pos2;
    } else {
        x = pos1;
        y = pos2;
    }
    No* posX = this->acessaPosicao(x);
    No* posY = this->acessaPosicao(y);

    if ((y - x) == 1) {
        // podem ser adjacentes, mas pode que um deles tambem esteja nos extremos.
        // ou os dois, vai que a lista so tem 2 elementos
        if (x==0) {
            posX->proximo = posY->proximo;
            posX->proximo->anterior = posX;
            posX->anterior = posY;
            
            posY->proximo = posX;
            posY->anterior = NULL;
            primeiro = posY;
        } else if (y == (qtdElementos-1)) {
            posY->anterior = posX->anterior;
            posY->anterior->proximo = posY;
            
            posY->proximo = posX;
            posX->anterior = posY;
            posX->proximo = NULL;
            
            ultimo = posX;            
        } else {
            No* anteriorX = posX->anterior;
            No* proximoY = posY->proximo;
            
            posY->anterior = anteriorX;
            anteriorX->proximo = posY;
            posY->proximo = posX;
            
            posX->anterior = posY;
            posX->proximo = proximoY;
            proximoY->anterior = posX;     
        }
    } else if(x == 0 and y == (qtdElementos-1)) {
        No* proximoX = posX->proximo;
        No* anteriorY = posY->anterior; 
        
        posX->anterior = anteriorY;
        anteriorY->proximo = posX;
        posX->proximo = NULL;     
        
        posY->anterior = NULL;
        posY->proximo = proximoX;
        proximoX->anterior = posY;
        
        primeiro = posY;
        ultimo = posX;  
        
    } else if (x == 0) {
        trocaPosicaoInicio(posX, posY);

    } else if (y == (qtdElementos-1)){ 
        trocaPosicaoFim(posX, posY);

    } else {    
        No* anteriorX = posX->anterior;
        No* proximoX = posX->proximo;

        posX->anterior = posY->anterior;
        posX->proximo = posY -> proximo;

        posY->anterior = anteriorX;
        posY->proximo = proximoX;

        posX->anterior->proximo = posX;
        posX->proximo->anterior = posX;

        posY->anterior->proximo = posY;
        posY->proximo->anterior = posY;
    }
}

Lista Lista::divide(unsigned int n) {
    
    if (this->posicaoValida(n)) {
        Lista nova;
        
        No* atual = this->acessaPosicao(n+1);
        
        while(atual != NULL) {
            nova.insere(atual->dado);
            atual = atual->proximo;
        }
        
        this->remove(nova);
        
        return nova;
    } else {
        return Lista();
    }
}

Lista& Lista::operator+(const Lista& outra) {
    No* atual = outra.primeiro;
    
    while(atual != NULL) {
        this->insere(atual->dado);
        atual = atual->proximo;
    }
    
    return *this;
}

Lista& Lista::operator+=(const Lista& outra) {
    No* atual = outra.primeiro;
    
    while(atual != NULL) {
        this->insere(atual->dado);
        atual = atual->proximo;
    }
    
    return *this;
}



int main() {
    Lista l1;
    
    for(int i = 0; i < 10; i++) {
        l1.insere(i+1);
    }
    
    l1.imprime();
    
    int pos;
    cin >> pos;
    
    Lista l2 = l1.divide(pos);
    
    l1.imprime();
    l2.imprime();
    

    return 0;
}
