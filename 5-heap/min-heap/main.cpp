#include "heap.hpp"

int main() {
	Dado valores[] = {10, 14, 2, 7, 9, 1, 13, 17, 21, 5, 4};
	
	Heap meuHeap(valores, 11, 12);
	
	meuHeap.imprime();
	int valor = 0;
	meuHeap.adiciona(valor);
	
	meuHeap.imprime();
	
	meuHeap.heapsort();
	
	meuHeap.imprime();
	
	return 0;
}
