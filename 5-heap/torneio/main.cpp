#include "torneio.hpp"
#include <iostream>

using namespace std;

int main() {
	Dado valores[] = {2, 3, 7, 1, 9, 5, 11, 40};
	Torneio torneio(valores, 8);
	if (torneio.obterGanhador()!= NULL) {
		cout << "Ganhador: " << torneio.obterGanhador() << endl;
	}
	return 0;
}
