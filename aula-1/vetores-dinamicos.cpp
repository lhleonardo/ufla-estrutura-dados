#include <iostream>

using namespace std;

class Vetor {
    public: 
        Vetor(unsigned int capacidade);
        ~Vetor();

        int tamanho();
        
        int obter(unsigned int posicao);
        bool altera(unsigned int posicao, int valor);
        
        void adiciona(int elemento);
        void adiciona(unsigned int posicao, int elemento);
        
        void ordena();
        int obterProdutoInterno();
        
        void apagaDuplicados();
        void apaga(unsigned int posicao);
        void apagaIntersecao(Vetor obj);
        
        bool posicaoOcupada(unsigned int posicao);
    
    protected:
        bool posicaoValida(unsigned int posicao);
        bool ficouCheio();
        
        void redimensiona();
        
        int capacidade();
        
    private: 
        int* __valores;
        unsigned int  __capacidade;
        unsigned int  __qtdInserida;
        
        void deslocaParaEsquerda(int inicio, int fim);
        void deslocaParaDireita(int inicio, int fim);
};

Vetor::Vetor(unsigned int capacidade) {
    __capacidade = capacidade;
    __qtdInserida = 0;
    __valores = new int[__capacidade];
}

Vetor::~Vetor() {
    delete [] __valores;
}

bool Vetor::posicaoValida(unsigned int posicao) {
    return posicao >= 0 and posicao < __qtdInserida;
}

bool Vetor::ficouCheio() {
    return __qtdInserida == __capacidade;
}

int Vetor::capacidade() {
    return __capacidade;
}

int Vetor::tamanho() {
    return __qtdInserida;
}

int Vetor::obter(unsigned int posicao) {
    if (posicaoValida(posicao)) {
        return __valores[posicao];
    } else {
        return 0;
    }
}

bool Vetor::altera(unsigned int posicao, int valor) {
    if (posicaoValida(posicao)) {
        __valores[posicao] = valor;
        return true;
    }
    
    return false;
}

bool Vetor::posicaoOcupada(unsigned int posicao) {
	if (posicao <= __qtdInserida - 1) {
		return true;
	}
	
	return false;
}

void Vetor::adiciona(int elemento) {
    this->adiciona(__qtdInserida, elemento);
}

void Vetor::adiciona(unsigned int posicao, int elemento) {
    if (ficouCheio()) {
        redimensiona();
    }
     
    if (posicaoOcupada(posicao)) {
		cout << "Tem que deslocar" << endl;
        deslocaParaDireita(posicao, __qtdInserida);
    }
    __valores[posicao] = elemento;
    
    __qtdInserida++;
    
}

// bubble sort
void Vetor::ordena() {
    bool alterou;
    
    do {
        alterou = false;
        for(unsigned int i = 0; i < __qtdInserida - 1; i++) {
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
    
    for(unsigned int i = 0; i < __qtdInserida; i++) {
        resultado *= __valores[i];
    }
    
    return resultado;
}


void Vetor::deslocaParaDireita(int inicio, int fim) {
    int aux = __valores[inicio];
    do {
        int proxima = __valores[inicio+1];
        
        __valores[inicio+1] = aux;
        
        aux = proxima;
        
        inicio++;
    } while(inicio < fim);
}

void Vetor::deslocaParaEsquerda(int inicio, int fim) {
    for(int i = inicio; i < fim; i++) 
        __valores[i-1] = __valores[i];
}



void Vetor::apagaDuplicados() {
    if (__qtdInserida == 0) return;
    
    for(unsigned int i = 0; i < __qtdInserida -1; i++) {
        for(unsigned int j = i+1; j < __qtdInserida; j++) {
            if (__valores[i] == __valores[j]) {
                apaga(j);
            }
        } 
    }
}

void Vetor::apaga( unsigned int posicao) {
    if (not posicaoValida(posicao)) 
        return;
        
    deslocaParaEsquerda(posicao+1, __qtdInserida);
    
    __qtdInserida--;
}

void Vetor::apagaIntersecao(Vetor outro) {
    for(int i = 0; i < outro.tamanho(); i++) {
        unsigned int j = 0;
        do {
            if (outro.obter(i) == this->obter(j)) {
                this->apaga(j);
            }
            
            j++;
        } while(j < __qtdInserida);
    }
}

void Vetor::redimensiona() {
    __capacidade *= 2;
    int* valores = new int[__capacidade];
    
    for(unsigned int i = 0; i < __capacidade; i++) 
        valores[i] = __valores[i];
    
    delete [] __valores;
    
    __valores = valores;

}

ostream& operator<<(ostream& os, Vetor &obj){
      os << "[";
      for (int i = 0; i < obj.tamanho(); i++) {
          os << obj.obter(i);
          
          if (i != (obj.tamanho() - 1)) {
              os << ", ";
          }
      }
      
      os << "]" << endl;
      return os;
}

int main() {
    Vetor lista(5);
    
    for (int i = 0; i < 6; i++) {
        lista.adiciona(i+1);
    }

    cout << lista << endl;
    
	lista.adiciona(4, 16);
	
	cout << lista << endl;
    
    return 0;
}
