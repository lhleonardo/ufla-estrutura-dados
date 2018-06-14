#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado;

enum posicao{dir, esq};

class noh{
    friend class abb;
    private:
        Dado valor;
        noh* esq;
        noh* dir;
        noh* pai;
    public:
        noh(Dado d = 0);
        ~noh();
};

noh :: noh(Dado d){
    valor = d;
    esq = NULL;
    pai = NULL;
    dir = NULL;
    
}

noh :: ~noh(){
    delete esq;
    delete dir;
}

class abb{
    private:
        noh* raiz;
        void percorreEmOrdemAux(noh* atual, int nivel);
        void percorrePreOrdemAux(noh* atual);
        void percorrePosOrdemAux(noh* atual);
        //menor e maior valor de uma subarvore com pai em raizSub
        noh* minimoAux(noh* raizSub);
        noh* maximoAux(noh* raizSub);
        //transplanta o nó novo para o local onde estava o nó antigo
        void transplanta(noh* antigo,noh* novo);
    public:
        abb();
        ~abb();
        void insere(Dado d);
        void remove(Dado d);
        noh* busca(Dado d);
        Dado minimo();
        Dado maximo();
        void percorreEmOrdem();
        void percorrePreOrdem();
        void percorrePosOrdem();
};

abb :: abb(){
    raiz = NULL;
}


abb :: ~abb(){
    delete raiz;
}

void abb :: insere(Dado d){
    noh* novo = new noh(d);
    posicao posInsercao;
    
    //primeiro caso -> arvore vazia
    if(raiz == NULL){
        raiz = novo;
    }
    else{
        noh* atual = raiz;
        noh* anterior;
        //encontrando o ponto de inserção
        while(atual != NULL){
            anterior = atual;   
            //trocar por >= se quiser elementos iguas
            if(atual->valor > d){
                atual = atual->esq;
                posInsercao = esq;
            }
            else{
                atual = atual->dir;
                posInsercao = dir;
            }
        }
        //inserindo o novo nó na arvore
        novo->pai = anterior;
        
        if(posInsercao == dir){
            anterior->dir = novo;
        }

        else{
            anterior->esq = novo;
        }
    }
}
        
noh* abb :: busca(Dado d){
    noh* atual = raiz;
    
    while(atual != NULL){
        if(atual->valor == d){
            return atual;
        }
        else if(atual->valor > d){
            atual = atual->esq;
        }
        else{
            atual = atual->dir;
        }
    }
    return atual;
}

Dado abb :: minimo(){
    if(raiz == NULL){
        cerr << "Árvore vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        noh* nohMin = minimoAux(raiz);
        return nohMin->valor;
    }
}

noh* abb :: minimoAux(noh* raizSub){
    cout << "DEU MERDA" << endl;
    //~ cout << raizSub->valor << endl;
    while(raizSub->esq != NULL){
        
        //~ cout << raizSub->valor << endl;
        raizSub = raizSub->esq;
        //~ cout << "SHIT" << endl;
    }
    cout << "saiu" << endl;
    return raizSub;
}

Dado abb :: maximo (){
    if(raiz == NULL){
        cerr << "Árvore vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        noh* nohMax = maximoAux(raiz);
        return nohMax->valor;
    }
}

noh* abb :: maximoAux (noh* raizSub){
    while(raizSub->dir != NULL){
        
        raizSub = raizSub->dir;
    }
    return raizSub;
}

//transplanta muda uma arvore com raiz em novo para o local
//onde antes estava o nó antigo

void abb :: transplanta (noh* antigo, noh* novo){
    if(raiz == antigo){
        raiz = novo;
    }
    else if(antigo == antigo->pai->esq){
        antigo->pai->esq = novo;
    }
    else { // antigo == antigo->pai->dir
        antigo->pai->dir = novo;
    }
    if(novo != NULL){
        novo->pai = antigo->pai;
    }
}

void abb :: remove(Dado dado){
    //achamos o nó na arvore
    //~ cout << "ENTROU" << endl;
    noh* nohRemover = busca(dado);
    
    if(nohRemover == NULL){
        cerr << "valor não está na árvore!" << endl;
    }
    else{
        //nó não tem filhos a esquerda
        if(nohRemover->esq == NULL){
            transplanta(nohRemover, nohRemover->dir);
        }
        //nó não tem filhos a direita
        else if(nohRemover->dir == NULL){
            transplanta(nohRemover,nohRemover->esq);
        }
        //nó tem dois filhos.. substituimos pelo sucessor
        else{ //((noRemover-esq) and (nohRemover->dir))
            noh* sucessor = minimoAux(nohRemover->dir);
            if(sucessor->pai != nohRemover){
                //~ noh* x = sucessor->dir;
                //~ cout << x->valor << endl;
                //~ cout << sucessor->dir->valor << endl;
                transplanta(sucessor, sucessor->dir);
                sucessor->dir = nohRemover->dir;
                sucessor->dir->pai = sucessor;
            }
            transplanta(nohRemover, sucessor);
            sucessor->esq = nohRemover->esq;
            sucessor->esq->pai = sucessor;
        }
        //ponteiros ajustados, apagamos o nó
        nohRemover->esq = NULL;
        nohRemover->dir = NULL;
        delete nohRemover;
    }
}

void abb :: percorreEmOrdem(){
    percorreEmOrdemAux(raiz,0);
    cout << endl;
}

void abb :: percorreEmOrdemAux(noh* atual, int nivel){
    if(atual != NULL){
        percorreEmOrdemAux(atual->esq, nivel+1);
        cout << atual->valor << "/" << nivel << " " << endl;
        percorreEmOrdemAux(atual->dir,nivel+1);
    }
}

void abb :: percorrePreOrdem(){
    percorrePreOrdemAux(raiz);
    cout << endl;
}

void abb :: percorrePreOrdemAux(noh* atual){
    if(atual != NULL){
        cout << atual->valor << " ";
        percorrePreOrdemAux(atual->esq);
        percorrePreOrdemAux(atual->dir);
    }
}

void abb :: percorrePosOrdem(){
    percorrePosOrdemAux(raiz);
    cout << endl;
}

void abb :: percorrePosOrdemAux(noh* atual){
    if(atual != NULL){
        percorrePosOrdemAux(atual->esq);
        percorrePosOrdemAux(atual->dir);
        cout << atual->valor << " ";
    }
}

int main (){
    
    abb tree;
    tree.insere(70);
    tree.insere(65);
    tree.insere(80);
    tree.insere(50);
    tree.insere(75);
    tree.insere(77);
    tree.insere(73);
    tree.insere(85);
    tree.insere(84);
    tree.insere(86);
    tree.remove(80);
    tree.percorreEmOrdem();
    return 0;
}
    


