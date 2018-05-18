#ifndef TORNEIO_H
#define TORNEIO_H

typedef int Dado;

class Torneio {
	private:
		Dado** elementos;
		unsigned int capacidade;
		unsigned int qtdElementos;
		
		void classifica();
		unsigned int qtdPares();
		bool elementosValidos(unsigned int numero);
	public:
		Torneio(Dado* valores, unsigned int qtdElementos);
		~Torneio();
		Dado* obterGanhador();

		void imprime();
};

#endif
