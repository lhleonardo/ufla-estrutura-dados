#ifndef TORNEIO_H
#define TORNEIO_H

typedef int Dado;

class Torneio {
	private:
		Dado** elementos;
		unsigned int capacidade;
		unsigned int qtdElementos;
		
		void corrigeSubindo(unsigned int posicao);
	public:
		Torneio(Dado* valores, unsigned int qtdElementos);

		Dado& obterGanhador();
};

#endif
