#include <iostream>

using namespace std;

int main() {
    int tamanho;
    cin >> tamanho;

    int vetor[tamanho];

    for(unsigned int i = 0; i < tamanho; i++) {
        cin >> vetor[i];
    }
    int posicao;
    cin >> posicao;

    if (posicao >= 0 and posicao < tamanho) {
        int novoVetor[tamanho];
        /* 
        1 2 3 4 5
        2
        4 5 1 2 3 
        */
       int cont = 0;
       for(int i = posicao + 1; i < tamanho; i++) {
           novoVetor[cont] = vetor[i];
           cont++;
       }

       for(int i = 0; i <= posicao; i++) {
           novoVetor[cont] = vetor[i];
           cont++;
       }

       for(int i = 0; i < tamanho; i++) {
           cout << novoVetor[i] << " ";
       }
    } else {
        cout << "informou posicao errada!" << endl;
    }

    return 0;
}