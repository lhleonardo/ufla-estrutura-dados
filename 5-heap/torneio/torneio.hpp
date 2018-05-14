#ifndef TORNEIO_H
#define TORNEIO_H

typedef int Dado;

class Torneio {
	private:
		Dado** elementos;
		unsigned int capacidade;
		unsigned int qtdElementos;
		
		void corrigeSubindo(unsigned int posicao);
		unsigned int qtdPares();
		bool elementosValidos();
	public:
		Torneio(Dado* valores, unsigned int qtdElementos);

		Dado& obterGanhador();
};

#endif
