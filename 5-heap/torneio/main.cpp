#include "torneio.hpp"
#include <iostream>

using namespace std;

int main() {
	Dado valores[] = {2, 3, 7, 1, 9, 5, 41, 40};
	Torneio torneio(valores, 8);
	
	// Dado* atual = torneio.obterGanhador();
	// int i = 1;
	// while (atual != NULL) {
	// 	cout << i << "a posicao: " << *atual << endl;
	// 	atual = torneio.obterGanhador();
	// 	i++;
	// }

	torneio.imprime();

	return 0;
}
