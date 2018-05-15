#include "Arvore.hpp"

void No::inicializa() {
    for(unsigned int i = 0; i < this->qtdFilhos; i++)
        this->filhos[i] = NULL;
}

bool No::filhosCheios() {
    return this->qtdFilhos == this->capacidadeFilhos;
}

No::No(const Dado valor, unsigned int qtdFilhos) {
    this->capacidadeFilhos = qtdFilhos;
    this->qtdFilhos = 0;
    this->valor = valor;
    this->filhos = new Dado*[qtdFilhos];

    this->inicializa();
}

No::No(const Dado valor, No** filhos, unsigned int qtdFilhos, unsigned int capacidade) {
    this->valor = valor;

    this->capacidadeFilhos = capacidade == 0 ? qtdFilhos : capacidade;
    this->qtdFilhos = qtdFilhos;

    this->inicializa();

    for(unsigned int i = 0; i < qtdFilhos; i++) {
        this->filhos[i] = filhos[i];
    }
}

void No::redimensiona() {
    // redimensiona o tamanho para +50%
    int novaCapacidade = qtdFilhos + (qtdFilhos / 2);
    No** valores = new No*[novaCapacidade];

    for(unsigned int i = 0; i < qtdFilhos; i++) {
        valores[i] = this->filhos[i];
    }

    delete [] filhos;

    this->capacidadeFilhos = novaCapacidade;
    this->filhos = valores;
}

void No::adicionaFilho(Dado valor) {
    if (filhosCheios()) {
        redimensiona();
    }

    this->filhos[qtdFilhos] = new No(valor);
    qtdFilhos++;
}

void No::removeFilho(Dado valor) {
    int posicao;

    if (this->procura(valor, &posicao)) {
        delete this->elementos[posicao];
    }
}

bool No::procura(Dado valor, int *posicao) {
    for(unsigned int i = 0; i < this->qtdFilhos; i++){
        if (this->filhos[i]->valor == valor) {
            posicao = i;
            return true;
        }        
    }

    posicao = -1;
    return false;
}
