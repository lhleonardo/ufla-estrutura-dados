#include "torneio.hpp"
#include <iostream>
#include <cmath>

using std::runtime_error;

bool Torneio::elementosValidos(unsigned int numero) {
	return log10(numero) / log10(2);
}

int Torneio::qtdPares() {
	return log2(this->qtdElementos);
}

Torneio::Torneio(Dado* valores, unsigned int qtdElementos) {
	if (not numeroValido(qtdElementos)) {
		throw runtime_error("Para realizar um torneio, a quantidade de elementos deve ser 2^n.");
	}
	
	// a capacidade dos valores, tratando como uma arvore binaria
	// vai ser sempre o dobro de elementos informados menos um. 
	// ou seja, a arvore binaria que representa um torneio de 8 valores
	// terá 15 nós.
	this->capacidade = 2*qtdElementos-1;
	
	this->elementos = new Dado*[this->capacidade];
	this->qtdElementos = qtdElementos;
	
	// inicializa os valores
	for(unsigned int i = 0; i < this->capacidade; i++) {
		this->elementos[i] = NULL;
	}
	
	// da ultima posicao, enquanto tiver valores informados devera ser armazenado
	// na mesma ordem do que foi informado
	
	unsigned int limite = this->capacidade - this->qtdElementos;
	for(unsigned int i = capacidade-1; i >= limite; i--) {
		// crio um novo ponteiro para o valor informado, ja que o torneio vai levando o maior
		// pra cima, entao nada mais facil que levar o endereco da memoria
		this->elementos[i] = new int(valores[i]);
	}
}

void Torneio::corrigeSubindo(unsigned int posicao) {
	
}

Dado& Torneio::obterGanhador() {
	
}
