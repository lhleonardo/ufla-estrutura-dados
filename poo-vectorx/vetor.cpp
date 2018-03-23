#include <iostream>

using namespace std;

class Vetor {
    public: 
        Vetor(unsigned int capacidade);
        ~Vetor();
        
        int capacidade();
        int qtdInserida();
        
        int obter(int posicao);
        bool altera(int posicao, int valor);
        void adiciona(int elemento);
        
        
        void ordena();
        int obterProdutoInterno();
        
        void apagaDuplicados();
        void apaga( int posicao);
        void apagaIntersecao(Vetor obj);
    
    protected:
        bool posicaoValida(int posicao);
        bool temVaga();
        
        void redimensiona();
        
    private: 
        int* __valores;
        int  __capacidade;
        int  __qtdInserida;
        
        void deslocaParaEsquerda(int inicio, int fim);
        void deslocaParaDireita(int inicio, int fim);
};

Vetor::Vetor(unsigned int capacidade) {
    __capacidade = capacidade;
    __qtdInserida = 0;
    __valores = new int[__capacidade];
}

Vetor::~Vetor() {
    // pq o erro?
    //delete [] __valores;
}

bool Vetor::posicaoValida(int posicao) {
    return posicao >= 0 and posicao < __qtdInserida;
}

bool Vetor::temVaga() {
    return __qtdInserida < __capacidade;
}

int Vetor::capacidade() {
    return __capacidade;
}

int Vetor::qtdInserida() {
    return __qtdInserida;
}

int Vetor::obter(int posicao) {
    if (posicaoValida(posicao)) {
        return __valores[posicao];
    } else {
        return 0;
    }
}

bool Vetor::altera(int posicao, int valor) {
    if (posicaoValida(posicao)) {
        __valores[posicao] = valor;
        return true;
    }
    
    return false;
}

void Vetor::adiciona(int elemento) {
    if (not temVaga()) {
        redimensiona();
    }
    __valores[__qtdInserida] = elemento;
    __qtdInserida++;
}

// bubble sort
void Vetor::ordena() {
    bool alterou;
    
    do {
        alterou = false;
        for(int i = 0; i < __qtdInserida - 1; i++) {
            if (__valores[i] > __valores[i+1]) {
                int aux = __valores[i];
                __valores[i] = __valores[i+1];
                __valores[i+1] = aux;
                alterou = true;
            }
        }
        
    } while(alterou);
}

int Vetor::obterProdutoInterno() {
    if (__qtdInserida == 0) return 0;
    
    int resultado = 1;
    
    for(int i = 0; i < __qtdInserida; i++) {
        resultado *= __valores[i];
    }
    
    return resultado;
}

void Vetor::deslocaParaEsquerda(int inicio, int fim) {
	for(int i = inicio; i < fim; i++) 
		__valores[i-1] = __valores[i];
}

void Vetor::apagaDuplicados() {
	if (__qtdInserida == 0) return;
    
    for(int i = 0; i < __qtdInserida -1; i++) {
        for(int j = i+1; j < __qtdInserida; j++) {
            if (__valores[i] == __valores[j]) {
                apaga(j);
            }
        } 
	}
}

void Vetor::apaga( int posicao) {
    if (not posicaoValida(posicao)) 
        return;
        
    deslocaParaEsquerda(posicao+1, __qtdInserida);
    
    __qtdInserida--;
}

void Vetor::apagaIntersecao(Vetor outro) {
	for(int i = 0; i < outro.qtdInserida(); i++) {
		int j = 0;
		do {
			if (outro.obter(i) == this->obter(j)) {
				this->apaga(j);
			}
			
			j++;
		} while(j < __qtdInserida);
	}
}

void Vetor::redimensiona() {
	
	int capacidade = __capacidade + 10;
	int* novoVetor = new int[capacidade];
	
	for(int i = 0; i < __qtdInserida; i++) 
		novoVetor[i] = __valores[i];
		
	delete [] __valores;
	
	__valores = novoVetor;	
	
	
}

ostream& operator<<(ostream& os, Vetor &obj){
      os << "[";
      for (int i = 0; i < obj.qtdInserida(); i++) {
          os << obj.obter(i);
          
          if (i != (obj.qtdInserida() - 1)) {
              os << ", ";
          }
      }
      
      os << "]" << endl;
      return os;
}

int main() {
    Vetor lista(5);
    
    for(int i = 0; i < 20; i++)
		lista.adiciona(i+1);
		
	cout << lista << endl;
    
    return 0;
}


