#include "heap.hpp"

#include <iostream>

using std::swap;
using std::cout;
using std::endl;

Heap::Heap(unsigned int capacidade) {
	this->capacidade = capacidade;
	this->qtdElementos = 0;
	this->elementos = new Dado[this->capacidade];
}

Heap::Heap(Dado* valores, unsigned int qtdElementos, unsigned int capacidade) {
	// se for zero, o cara nao informou o valor e pegou
	// o valor padrao
	this->capacidade = capacidade == 0 ? qtdElementos : capacidade;
	this->qtdElementos = qtdElementos;
	
	this->elementos = new Dado[this->capacidade];
	
	for(unsigned int i = 0; i < qtdElementos; i++) {
		this->elementos[i] = valores[i];
	}
	
	arruma();
}

void Heap::arruma() {
	for(int i = (this->qtdElementos-1)/2; i >= 0; i--) {
		corrigeDescendo(i);
	}
}

int Heap::filhoDireita(unsigned int posicao) {
	return (posicao*2) + 2;
}

int Heap::filhoEsquerda(unsigned int posicao) {
	return (posicao * 2) + 1;
}

int Heap::pai(unsigned int posicao) {
	return (posicao +2 / 2) -1;
	
}

void Heap::corrigeDescendo(unsigned int posicao) {
	unsigned int direita = this->filhoDireita(posicao);
	unsigned int esquerda = this->filhoEsquerda(posicao);
	
	unsigned int posMenor;
	
	if (direita < qtdElementos and this->elementos[direita] > this->elementos[posicao]) {
		posMenor = direita;
	} else {
		posMenor = posicao;
	}
	
	if (esquerda < this->qtdElementos and this->elementos[esquerda] > this->elementos[posMenor]) {
		posMenor = esquerda;
	}
	
	if (posMenor != posicao) {
		swap(this->elementos[posMenor], this->elementos[posicao]);
		corrigeDescendo(posMenor);
	}
}

void Heap::corrigeSubindo(unsigned int posicao) {
	int pai = this->pai(posicao);
	
	if (pai >= 0 and this->elementos[posicao] > this->elementos[pai]) {
		swap(this->elementos[pai], this->elementos[posicao]);
		corrigeSubindo(pai);
	}
}

void Heap::adiciona(Dado& valor) {
	if (this->qtdElementos < this->capacidade) {
		this->elementos[qtdElementos] = valor;
		corrigeSubindo(qtdElementos);
		qtdElementos++;
	} else {
		cout << "HEAP cheio!" << endl;
	}
}

void Heap::heapsort() {
	unsigned int tamanhoAntigo = this->qtdElementos;
	unsigned int ultimo;
	
	do {
		ultimo = this->qtdElementos-1;
		swap(this->elementos[0], this->elementos[ultimo]);
		this->qtdElementos--;
		arruma();
	} while(this->qtdElementos > 1);

	this->qtdElementos = tamanhoAntigo;
}

void Heap::imprime() {
	cout << "[";
	for(unsigned int i = 0; i < this->qtdElementos; i++) {
		cout << this->elementos[i];
		if (i != this->qtdElementos - 1) {
			cout << ", ";
		}
	}
	
	cout << "]" << endl;
}
