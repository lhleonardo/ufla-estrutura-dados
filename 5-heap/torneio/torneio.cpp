#include "torneio.hpp"
#include <iostream>
#include <cmath>

using std::runtime_error;

bool numeroValido(unsigned int numero) {
	return log10(numero) / log10(2);
}

Torneio::Torneio(Dado* valores, unsigned int qtdElementos) {
	if (not numeroValido(qtdElementos)) {
		throw runtime_error("Para realizar um torneio, a quantidade de elementos deve ser 2^n.");
	}
	
	this->capacidade = 2*qtdElementos-1;
	this->elementos = new Dado*[this->capacidade];
	this->qtdElementos = qtdElementos;
	for(unsigned int i = 0; i < this->capacidade; i++) {
		this->elementos[i] = NULL;
	}
	
	for(unsigned int i = qtdElementos-1; i >= 0; i--) {
		this->elementos[i] = new int(valores[i]);
	}
}

void Torneio::corrigeSubindo(unsigned int posicao) {
	
}

Dado& Torneio::obterGanhador() {
	
}
