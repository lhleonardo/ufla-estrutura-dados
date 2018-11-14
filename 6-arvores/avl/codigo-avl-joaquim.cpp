#include <cstdlib>
#include <iostream>

using namespace std;

typedef int Dado;

class noh {
    friend class avl;
    friend int calcAutura(noh* umNoh);
    friend int calcBal(noh* umNoh);

  private:
    Dado valor;
    noh* esq;
    noh* dir;
    noh* pai;
    // int altura;
  public:
    int altura;
    int fatorBalanceamento();
    noh(Dado d = 0);
    ~noh();
};

noh ::noh(Dado d) {
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
    altura = 1;
}

noh ::~noh() {
    delete esq;
    delete dir;
}

int calcAltura(noh* umNoh) {
    if (umNoh == NULL) {
        return 0;
    } else {
        return umNoh->altura;
    }
}

int calcBal(noh* umNoh) {
    if (umNoh == NULL) {
        return 0;
    } else {
        return umNoh->fatorBalanceamento();
    }
}

int noh ::fatorBalanceamento() {
    return calcAltura(esq) - calcAltura(dir);
}

class avl {
  private:
    noh* raiz;
    void percorreEmOrdemAux(noh* atual, int nivel);
    void percorrePreOrdemAux(noh* atual);
    void percorrePosOrdemAux(noh* atual);
    // menor e maior valor de uma subarvore com pai em raizSub
    noh* minimoAux(noh* raizSub);
    noh* maximoAux(noh* raizSub);
    // transplanta o nó novo para o local onde estaa o nó antigo
    void transplanta(noh* antigo, noh* novo);
    noh* rotacaoEsquerda(noh* umNoh);
    noh* rotacaoDireita(noh* umNoh);
    noh* arrumaBalanceamento(noh* umNoh);
    noh* insereAux(noh* umNoh, Dado d);
    noh* removeAux(noh* umNoh, Dado d);
    bool verificaNoh(noh* umNoh);  // verifica se os ponteiros do nó esta ok
    bool percorreVerificandoAux(noh* umNoh);

  public:
    avl();
    ~avl();
    void insere(Dado d);
    void remove(Dado d);
    noh* busca(Dado d);
    Dado minimo();
    Dado maximo();
    void percorreEmOrdem();
    void percorrePreOrdem();
    void percorrePosOrdem();
    bool percorreVerificando();
};

avl ::avl() {
    raiz = NULL;
}

avl ::~avl() {
    delete raiz;
}

noh* avl ::busca(Dado d) {
    noh* atual = raiz;

    while (atual != NULL) {
        if (atual->valor == d) {
            return atual;
        } else if (atual->valor > d) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    return atual;
}

void avl ::insere(Dado dado) {
    raiz = insereAux(raiz, dado);
}

noh* avl ::insereAux(noh* umNoh, Dado dado) {
    // se chegou em uma folha nula, insere aqui
    if (umNoh == NULL) {
        noh* novo = new noh(dado);
        return novo;
    }

    // se não é uma folha nula, checa se insere a esquerda ou direita
    if (dado < umNoh->valor) {
        umNoh->esq = insereAux(umNoh->esq, dado);
        umNoh->esq->pai = umNoh;
    } else if (dado > umNoh->valor) {
        umNoh->dir = insereAux(umNoh->dir, dado);
        umNoh->dir->pai = umNoh;
    } else {  // não temos elementos repetidos
        cerr << "Elemento repetido : " << dado << endl;
        return umNoh;
    }
    // ajusta a árvore após a inserção
    return arrumaBalanceamento(umNoh);
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários

noh* avl ::arrumaBalanceamento(noh* umNoh) {
    // atualiza altura
    umNoh->altura = 1 + max(calcAltura(umNoh->esq), calcAltura(umNoh->dir));

    // checa o balanceamento
    int bal = umNoh->fatorBalanceamento();

    // retorna o nó acima na arvore, caso esteja balanceado
    if ((bal >= -1) and (bal <= 1)) {
        return umNoh;
    }

    // Caso o nó esteja desbalanceado, há 4 situaçoes
    // 1. desbalanceamento esquerda esquerda
    if ((bal > 1) && (calcBal(umNoh->esq) >= 0)) {
        return rotacaoDireita(umNoh);
    }

    // 2. Desbalanceamento Esquerda Direita
    if ((bal > 1) && (calcBal(umNoh->esq) < 0)) {
        umNoh->esq = rotacaoEsquerda(umNoh->esq);
        // umNoh->esq->pai = umNoh; //não certo se precisa disso
        return rotacaoDireita(umNoh);
    }

    // 3.Desbalanceamento Direita Direita
    if ((bal < -1) && (calcBal(umNoh->dir) <= 0)) {
        return rotacaoEsquerda(umNoh);
    }

    // 4. Desbalanceamento Direita Esquerda

    if ((bal < -1) && (calcBal(umNoh->dir) > 0)) {
        umNoh->dir = rotacaoDireita(umNoh->dir);
        // umNoh->dir->pai = umNoh; // nao certo se precisa disso
        return rotacaoEsquerda(umNoh);
    }

    // apenas para evitar warning
    // retorno deve ocorrer em um dos ifs anteriores
    cerr << "Não deveria chegar aqui" << endl;
    return NULL;
}

// rotacao a esquerda na subarvore com raiz em umNoh
// retor o novo pai da subarvore

noh* avl ::rotacaoEsquerda(noh* umNoh) {
    // acha o nó filho à direita do umNoh
    noh* nohAux = umNoh->dir;

    // armazena subarvore à esquerda de nohAux
    // como filho à direita de umNoh
    umNoh->dir = nohAux->esq;

    // atualiza o pai do nó à esquerda de umNoh
    if (nohAux->esq != NULL) {
        nohAux->esq->pai = umNoh;
    }
    // Atualiza o pao de nohAux
    nohAux->pai = umNoh->pai;

    // colocando nohAux no lugar de umNoh
    if (umNoh->pai != NULL) {
        if (umNoh == umNoh->pai->esq) {
            umNoh->pai->esq = nohAux;
        } else {
            umNoh->pai->dir = nohAux;
        }
    }
    // faz umNoh como filho a esquerda de nohAux
    nohAux->esq = umNoh;
    umNoh->pai = nohAux;

    // atualiza altras

    umNoh->altura = 1 + max(calcAltura(umNoh->esq), calcAltura(umNoh->dir));

    nohAux->altura = 1 + max(calcAltura(nohAux->esq), calcAltura(nohAux->dir));

    return nohAux;
}

// rotação a direita na subarvore com raiz em umNoh
// retor o novo pai da subarvore

noh* avl ::rotacaoDireita(noh* umNoh) {
    // acha o nó'filho à esquerda de umNoh
    noh* nohAux = umNoh->esq;

    // armazena subarvore à direita de nohAux
    // como filho a esquerda de umNoh
    umNoh->esq = nohAux->dir;

    // atualiza o pai do nó à direita de umNoh
    if (nohAux->dir != NULL) {
        nohAux->dir->pai = umNoh;
    }

    // ataliza o pai de nohAux

    nohAux->pai = umNoh->pai;

    // colocando nohAux no lugar de umNoh

    if (umNoh->pai != NULL) {
        if (umNoh == umNoh->pai->esq) {
            umNoh->pai->esq = nohAux;
        } else {
            umNoh->pai->dir = nohAux;
        }
    }

    // faz umNoh como filho à direita de nohaux

    nohAux->dir = umNoh;
    umNoh->pai = nohAux;

    // atualiza alturas
    umNoh->altura = 1 + max(calcAltura(umNoh->esq), calcAltura(umNoh->dir));
    nohAux->altura = 1 + max(calcAltura(nohAux->esq), calcAltura(nohAux->dir));

    return nohAux;
}

Dado avl::minimo() {
    if (raiz == NULL) {
        cerr << "Arvore vazia!" << endl;
        exit(EXIT_FAILURE);
    } else {
        noh* nohMin = minimoAux(raiz);
        return nohMin->valor;
    }
}

noh* avl ::minimoAux(noh* raizSub) {
    while (raizSub->esq != NULL) {
        raizSub = raizSub->esq;
    }
    return raizSub;
}

Dado avl ::maximo() {
    if (raiz == NULL) {
        cerr << "Árvore vazia !" << endl;
        exit(EXIT_FAILURE);
    } else {
        noh* nohMax = maximoAux(raiz);
        return nohMax->valor;
    }
}

noh* avl ::maximoAux(noh* raizSub) {
    while (raizSub->dir != NULL) {
        raizSub = raizSub->dir;
    }
    return raizSub;
}

// transplanta muda uma arvore com raiz em novo para o local onde
// antes estava o nó antigo

void avl ::transplanta(noh* antigo, noh* novo) {
    if (raiz == antigo) {
        raiz = novo;
    } else if (antigo == antigo->pai->esq) {
        antigo->pai->esq = novo;
    } else {
        antigo->pai->dir = novo;
    }
    if (novo != NULL) {
        novo->pai = antigo->pai;
    }
}

void avl ::remove(Dado dado) {
    raiz = removeAux(raiz, dado);
}

noh* avl ::removeAux(noh* umNoh, Dado dado) {
    // inicialmento caminhamos na arvore para encontra o nó
    // busca recursiva

    // se chegamos  a um nó nulo, entao o valor nao esta na arvore

    if (umNoh == NULL) {
        cerr << "valor não está na arvore" << endl;
        return umNoh;
    }

    // valor é menor que nó atual, entao vai para subarvore esquerda
    if (dado < umNoh->valor) {
        umNoh->esq = removeAux(umNoh->esq, dado);
    }

    // valor é maior que nó atual, entao vai para subarvore direita

    else if (dado > umNoh->valor) {
        umNoh->dir = removeAux(umNoh->dir, dado);
    }

    // valor é igual ao armazenado no nó atual, que deve ser apagado
    else {  // dado == umNoh->valor
        noh* aux;
        // nó nao tem filhos à esquerda
        if (umNoh->esq == NULL) {
            aux = umNoh->dir;
            transplanta(umNoh, umNoh->dir);
        }
        // nó não tem filhos à direita
        else if (umNoh->dir == NULL) {
            aux = umNoh->esq;
            transplanta(umNoh, umNoh->esq);
        }
        // nó tem dois filhos... substituimos pelo sucessor
        else {
            noh* sucessor = minimoAux(umNoh->dir);
            aux = sucessor;
            if (sucessor->pai != umNoh) {
                transplanta(sucessor, sucessor->dir);
                // atualiza a altura de sucessor->pai até umNoh->dir
                noh* aux = sucessor->pai;
                while (aux != umNoh->dir) {
                    aux->altura = 1 + max(calcAltura(aux->esq), calcAltura(aux->dir));
                    aux = aux->pai;
                }
                sucessor->dir = arrumaBalanceamento(umNoh->dir);
                sucessor->dir->pai = sucessor;
            }
            transplanta(umNoh, sucessor);
            sucessor->esq = umNoh->esq;
            sucessor->esq->pai = umNoh;
        }
        // ponteiros ajustador, apagamos o nó
        umNoh->esq = NULL;
        umNoh->dir = NULL;
        delete umNoh;

        // assumimos a nova raiz para fazermos ajustes
        umNoh = aux;

    }

    // caso a nova raiz seja nula, devolva-a
    if (umNoh == NULL) {
        return umNoh;
    }

    // verifica e arruma o balanceamento em umNoh
    return arrumaBalanceamento(umNoh);
}

void avl ::percorreEmOrdem() {
    percorreEmOrdemAux(raiz, 0);
    cout << endl;
}

void avl ::percorreEmOrdemAux(noh* atual, int nivel) {
    if (atual != NULL) {
        percorreEmOrdemAux(atual->esq, nivel + 1);
        cout << atual->valor << "/" << nivel << " ";
        percorreEmOrdemAux(atual->dir, nivel + 1);
    }
}

void avl ::percorrePreOrdem() {
    percorrePreOrdemAux(raiz);
}

void avl ::percorrePreOrdemAux(noh* atual) {
    if (atual != NULL) {
        cout << atual->valor << " ";
        percorrePreOrdemAux(atual->esq);
        percorrePreOrdemAux(atual->dir);
    }
}

void avl ::percorrePosOrdem() {
    percorrePosOrdemAux(raiz);
    cout << endl;
}

void avl ::percorrePosOrdemAux(noh* atual) {
    if (atual != NULL) {
        percorrePosOrdemAux(atual->esq);
        percorrePosOrdemAux(atual->dir);
        cout << atual->valor << " ";
    }
}

bool avl ::verificaNoh(noh* umNoh) {
    noh* pai = umNoh->pai;
    noh* esq = umNoh->esq;
    noh* dir = umNoh->dir;

    if ((pai != NULL) and (pai->esq != umNoh) and (pai->dir != umNoh)) {
        return false;  // pai nao sabe que nó é seu filho
    }
    if ((esq != NULL) and (esq->pai != umNoh)) {
        return false;  // filhos esquerdo nao reconhece nó como pai
    }
    if ((dir != NULL) and (dir->pai != umNoh)) {
        return false;  // filho direito nao reconhece nó como pai
    }
    // todos os ponteiros do nó em seus devidos lugares
    return true;
}

bool avl ::percorreVerificando() {
    return percorreVerificandoAux(raiz);
}

bool avl ::percorreVerificandoAux(noh* atual) {
    bool verEsq;
    bool verDir;
    bool verAtual;

    if (atual != NULL) {
        // verifica subarvore esquerda
        verEsq = percorreVerificandoAux(atual->esq);
        // verificando o propio nó
        verAtual = verificaNoh(atual);
        // se tem problemas, aponta local do erro
        if (not verAtual) {
            cerr << "deu erro com nó com valor " << atual->valor << endl;
        }
        // erifica subarvore direita
        verDir = percorreVerificandoAux(atual->dir);

        // retorna resultado das combinaçoes

        return (verAtual and verEsq and verDir);
    } else {  // tudo ok com nós nulos
        return true;
    }
}

int main() {
    avl tree;

    tree.insere(100);
    tree.percorreEmOrdem();

    tree.insere(100);
    tree.percorreEmOrdem();

    tree.insere(100);
    tree.percorreEmOrdem();

    tree.insere(5);
    tree.insere(2);
    tree.insere(1);
    tree.insere(21);
    tree.insere(7);
    tree.insere(18);
    tree.insere(12);
    tree.insere(13);
    tree.insere(4);
    tree.insere(8);
    tree.insere(25);
    tree.insere(32);
    tree.insere(6);

    return 0;
}
