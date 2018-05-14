#include "torneio.hpp"
#include <iostream>
#include <cmath>

using std::runtime_error;
using std::cout;
using std::endl;

bool Torneio::elementosValidos(unsigned int numero) {
	return log10(numero) / log10(2);
}

unsigned int Torneio::qtdPares() {
	return log2(this->qtdElementos);
}

Torneio::Torneio(Dado* valores, unsigned int qtdElementos) {
	if (not elementosValidos(qtdElementos)) {
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
		this->elementos[i] = new Dado(valores[i]);
	}
	
	classifica();
}

void Torneio::classifica() {
	// quantas vezes deverá fazer as rodadas de um torneio
	unsigned int rodadas = this->qtdElementos/2;
	// quem foi o ultimo cara que foi avaliado, ou seja, vai guardando o
	// ultimo dos pares que foram avaliados
	unsigned int posicaoAvaliada = this->capacidade-1;
	
	unsigned int posResultado;
	do {
		for(unsigned int i = 0; i < rodadas; i++) {
			// pega o pai da devida posicao
			posResultado = ((posicaoAvaliada+1)/2)-1;
			// se alguma das duas sao nulas, quem ganha o torneio eh aquele que nao eh nulo
			if ((this->elementos[posicaoAvaliada] == NULL) or 
				(this->elementos[posicaoAvaliada-1] == NULL)) {
				// alguma das duas são nulas
				if (this->elementos[posicaoAvaliada] == NULL) {
					this->elementos[posResultado] = this->elementos[posicaoAvaliada-1];
				} else {
					this->elementos[posResultado] = this->elementos[posicaoAvaliada];
				}
			} else {
				if (this->elementos[posicaoAvaliada] > this->elementos[posicaoAvaliada-1]) {
					this->elementos[posResultado] = this->elementos[posicaoAvaliada];
				} else {
					this->elementos[posResultado] = this->elementos[posicaoAvaliada - 1];
				}
			}
			posicaoAvaliada = posicaoAvaliada - 2;
		}
		rodadas = rodadas / 2;
	} while(rodadas >=1);
}

Dado& Torneio::obterGanhador() {
	return *this->elementos[0];
}
