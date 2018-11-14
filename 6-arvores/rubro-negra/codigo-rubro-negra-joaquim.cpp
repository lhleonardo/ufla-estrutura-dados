#include <iostream>

using namespace std;

const unsigned PRETO = 0;
const unsigned VERMELHO = 1;

class noh {
    friend class arvoreRN;

  private:
    noh* pai;
    noh* esq;
    noh* dir;
    unsigned cor;
    unsigned chave;
};

//~ noh :: noh(unsigned c){
//~ chave = c;
//~ cor = VERMELHO;
//~ pai = NULL;
//~ esq = NULL;
//~ dir = NULL;
//~ }

class arvoreRN {
  private:
    noh* raiz;
    bool insereAux(noh* umNoh);
    void percorreEmOrdemAux(noh* umNoh, int nivel);
    bool arrumaInsercao(noh* umNoh);
    void rotacaoEsquerda(noh* umNoh);
    void rotacaoDireita(noh* umNoh);

  public:
    arvoreRN();
    ~arvoreRN();
    bool insere(unsigned c);
    void percorreEmOrdem();
};

arvoreRN ::arvoreRN() {
    raiz = NULL;
}

arvoreRN ::~arvoreRN() {
    delete raiz;
}

bool arvoreRN ::insere(unsigned c) {
    noh* novo = new noh;
    novo->chave = c;
    novo->esq = NULL;
    novo->dir = NULL;

    if (raiz == NULL) {
        novo->cor = PRETO;
        novo->pai = NULL;
        raiz = novo;
        return true;
    }
    noh* atual = raiz;
    noh* anterior;
    while (atual != NULL) {
        anterior = atual;
        if (c > atual->chave) {
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    novo->pai = anterior;
    novo->cor = VERMELHO;
    if (anterior->chave < novo->chave) {
        anterior->dir = novo;
    } else {
        anterior->esq = novo;
    }

    return arrumaInsercao(novo);
}

bool arvoreRN ::arrumaInsercao(noh* umNoh) {
    noh* tio;
    while ((umNoh != raiz) and (umNoh->pai->cor == VERMELHO)) {
		// encontrando o tio
        if (umNoh->pai != raiz) {
            if (umNoh == umNoh->pai->pai->esq) {
                tio = umNoh->pai->pai->dir;
            } else {
                tio = umNoh->pai->pai->esq;
            }
        } else {
            tio = NULL;
        }


        if ((tio != NULL) and (tio->cor == VERMELHO)) {
            // alterar as cores do pai, tio e avô
            umNoh->pai->cor = PRETO;
            umNoh->pai->pai->cor = VERMELHO;
            tio->cor = PRETO;
            // mover umNoh para o avô para continuar a verificação
            umNoh = umNoh->pai->pai;
        } else {
            // tio preto e pai é vermelho
            // CASO 1 : Rotação a esquerda simples (LL)
            if ((umNoh == umNoh->pai->esq) and (umNoh->pai == umNoh->pai->pai->esq)) {
                tio->cor = PRETO;
				umNoh->pai->cor = PRETO;
                umNoh->pai->pai->cor = VERMELHO;
                rotacaoDireita(umNoh->pai->pai);
                continue;
            }
            // CASO 2 : Rotação Esquerda-Direita (LR)
            if ((umNoh->pai == umNoh->pai->pai->esq) and (umNoh == umNoh->pai->dir)) {
                umNoh = umNoh->pai;
				rotacaoEsquerda(umNoh);
				umNoh->pai->cor = PRETO;
                umNoh->pai->pai->cor = VERMELHO;
                rotacaoDireita(umNoh->pai->pai);
                continue;
            }

            // CASO 3 : Rotação a direita simples (RR)
            if ((umNoh->pai == umNoh->pai->pai->dir) and (umNoh == umNoh->pai->dir)) {
                umNoh->pai->cor = PRETO;
                umNoh->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(umNoh->pai->pai);
                continue;
            }
            // CASO 4 : Rotação Direita-Esquerda (RL)
            if ((umNoh->pai = umNoh->pai->pai->dir) and (umNoh == umNoh->pai->esq)) {
                umNoh = umNoh->pai;
                rotacaoDireita(umNoh);
                umNoh->pai->cor = PRETO;
                umNoh->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(umNoh->pai->pai);
                continue;
            }
        }
    }
    raiz->cor = PRETO;
    return true;
}

void arvoreRN ::percorreEmOrdem() {
    percorreEmOrdemAux(raiz, 0);
    cout << endl;
}

void arvoreRN ::percorreEmOrdemAux(noh* umNoh, int nivel) {
    if (umNoh != NULL) {
        percorreEmOrdemAux(umNoh->esq, nivel + 1);
        cout << umNoh->chave << "/";
		cout << (umNoh->cor == VERMELHO ? "V/" : "P/") << nivel << "  ";
        percorreEmOrdemAux(umNoh->dir, nivel + 1);
    }
}

void arvoreRN ::rotacaoDireita(noh* umNoh) {
    noh* aux = umNoh->esq;
    umNoh->esq = aux->dir;
    if (aux->dir != NULL) {
        aux->dir->pai = umNoh;
    }
    aux->dir = umNoh;
    if (umNoh == umNoh->pai->esq) {
        umNoh->pai->esq = aux;
    } else {
        umNoh->pai->dir = aux;
    }
    aux->pai = umNoh->pai;
    umNoh->pai = aux;
}

void arvoreRN ::rotacaoEsquerda(noh* umNoh) {
    noh* aux = umNoh->dir;
    umNoh->dir = aux->esq;
    if (aux->esq != NULL) {
        aux->esq->pai = umNoh;
    }
    aux->esq = umNoh;
    if (umNoh->pai == NULL) {
        raiz = aux;
    }

    else if (umNoh->pai != NULL) {
        if (umNoh == umNoh->pai->esq) {
            umNoh->pai->esq = aux;
        } else {
            umNoh->pai->dir = aux;
        }
    }
    aux->pai = umNoh->pai;
    umNoh->pai = aux;
}

int main() {
    arvoreRN tree;
    tree.insere(10);
    tree.insere(11);
    tree.insere(12);
    tree.insere(13);
    tree.percorreEmOrdem();
    return 0;
}
