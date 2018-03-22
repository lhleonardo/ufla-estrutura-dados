#include <iostream>

using namespace std;

class Vetor {
    public: 
        Vetor();
        Vetor(unsigned int capacidade);
        ~Vetor();
        
        int obter(unsigned int posicao);        
        int busca(int elemento);
        void ordena();
        
        int obterProdutoInterno();
        int* obterValoresMultiplicadoPor(int numero);
        
        void removeDuplicados();
        void remove(unsigned int posicao);
        void removeIntersecao(Vetor* outro);
        
        void redimensiona();
        
        void adiciona(int valor, unsigned int posicao);
        void modifica(int valor, unsigned int posicao);
        
        unsigned int obterCapacidade();
        unsigned int qtdInserida();        
    private: 
        int* dados;
        unsigned int capacidade;
        unsigned int qtdPreenchida;
        
        void puxaValores(unsigned int inicio, unsigned int fim);
        void empurraValores(unsigned int inicio);
        void copia(int* destino, unsigned int fim);
        
};

Vetor::Vetor() {
    this->capacidade = 10;
    this->qtdPreenchida = 0;
    this->dados = new int[this->capacidade];
}

Vetor::Vetor(unsigned int capacidade) {
    this->capacidade = capacidade;
    this->qtdPreenchida = 0;
    this->dados = new int[capacidade];
}

Vetor::~Vetor() {
    this->capacidade = 0;
    this->qtdPreenchida = 0;
    delete [] this->dados;
}

int Vetor::obter(unsigned int posicao) {
    if (this->qtdPreenchida > 0 and posicao < this->capacidade) {
        return this->dados[posicao];
    }
    
    return -1;
}

int Vetor::busca(int elemento) {
    for(unsigned int i = 0; i < this->qtdPreenchida; i++) {
        if (this->dados[i] == elemento) {
            return i;
        }
    }
    
    return -1;
}

void Vetor::ordena() {
    bool alterou;
    
    do {
        alterou = false;
        for(unsigned int i = 0; i < this->qtdPreenchida - 1; i++) {
            if (this->dados[i] > this->dados[i+1]) {
                int aux = dados[i];
                dados[i] = dados[i+1];
                dados[i+1] = aux;
                alterou = true;
            }
        }
        
    } while(alterou);
}

int Vetor::obterProdutoInterno() {
    if (this->qtdPreenchida == 0) return 0;
    
    int resultado = 1;
    
    for(unsigned int i = 0; i < this->qtdPreenchida; i++) {
        resultado *= this->dados[i];
    }
    
    return resultado;
}

int* Vetor::obterValoresMultiplicadoPor(int numero) {
    int* resultado = new int[this->qtdPreenchida];

    for(unsigned int i = 0; i < this->qtdPreenchida; i++) {
        resultado[i] = this->dados[i] * numero;
    }
    
    return resultado;
}

void Vetor::puxaValores(unsigned int inicio, unsigned int fim) {
    for(unsigned int i = inicio; i < fim; i++) 
        this->dados[inicio-1] = this->dados[inicio];
        
}

void Vetor::empurraValores(unsigned int inicio) {
    if (this->capacidade == this->qtdPreenchida) {
        redimensiona();
    }
    
    int aux = this->dados[inicio];
    
    for(unsigned int i = inicio; i < this->qtdPreenchida; i++) {
        int proximo = this->dados[i+1];
        this->dados[i+1] = aux;
        
        aux = proximo;
    }
}

void Vetor::removeDuplicados() {
    if (this->qtdPreenchida == 0) return;
    
    for(unsigned int i = 0; i < this->qtdPreenchida -1; i++) {
        for(unsigned int j = i+1; j < this->qtdPreenchida; j++) {
            if (this->dados[i] == this->dados[j]) {
                this->puxaValores(j+1, this->qtdPreenchida);
                this->qtdPreenchida--;
            }
        } 
    }
}

void Vetor::remove(unsigned int posicao) {
    if (this->qtdPreenchida <= 0 or posicao >= this->capacidade) 
        return;
        
    this->puxaValores(posicao+1, this->qtdPreenchida);
}

void Vetor::removeIntersecao(Vetor* outro) {
    if (this->qtdPreenchida <= 0) 
        return; 
        
    unsigned int i = 0;
    
    do {
        for(unsigned int j = 0; j < outro->qtdInserida(); j++) {
            if (this->dados[i] == outro->obter(j)) {
                puxaValores(i+1, this->qtdPreenchida);
                this->qtdPreenchida--;
            }
        }
        
        i++;
    } while(i < this->qtdPreenchida);
}

void Vetor::copia(int* destino, unsigned int fim) {
    for(unsigned int i = 0; i < fim; i++) {
        destino[i] = this->dados[i];
    }
}

void Vetor::redimensiona() {
    
    this->capacidade *= 2;
    
    int* novosValores = new int[this->capacidade];
    
    copia(novosValores, this->capacidade / 2);
    
    delete [] this->dados;
    
    this->dados = novosValores;
    
}

void Vetor::adiciona(int valor, unsigned int posicao) {
    if (this->capacidade == this->qtdPreenchida or this->capacidade <=posicao) {
        redimensiona();
    }
    
    if (posicao <= this->qtdPreenchida) {
        empurraValores(posicao);
    }
    
    this->dados[posicao] = valor;
}

ostream& operator<<(ostream& os, Vetor &obj){
      os << "[";
      for(unsigned int i = 0; i < obj.obterCapacidade(); i++) {
          os << obj.obter(i);
          
          if (i != (obj.obterCapacidade() - 1)) {
              os << ", ";
          }
      }
      return os;
}


int main() {
    Vetor valores(10);
    
    valores.adiciona(1, 0);
    valores.adiciona(2, 1);
    valores.adiciona(3, 2);
    valores.adiciona(4, 3);
    valores.adiciona(5, 4);
    valores.adiciona(6, 5);
    valores.adiciona(12, 1);
    
    cout << valores << endl;
    return 0;
}
