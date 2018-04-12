#include <iostream>

using namespace std;

const unsigned int PRIMO = 31;

class No {
	friend class ListaHash;
	
	private: 
		string chave;
		string valor;
		No* proximo;
	public:
		No(string chave = "", string valor="", No* proximo = NULL);
		bool operator ==(const No& outro);
		string getChave() { return this->chave; };
		string getValor() { return this->valor; };
};

No::No(string chave, string valor, No* proximo) {
	this->chave = chave;
	this->valor = valor;
	this->proximo = proximo;
}

bool No::operator ==(const No& outro) {
	return this->chave == outro.chave and this->valor == outro.valor;
}

class ListaHash {
	private: 
		No** elementos;
		unsigned int capacidade;
		unsigned int inseridos;

		int hashCode(string chave);
	public:
		ListaHash(unsigned int capacidade = 100);
		~ListaHash();
		
		bool existe(string chave, string valor);
		void insere(string chave, string valor);
		
		No* recupera(string chave);
};

ListaHash::ListaHash(unsigned int capacidade) {
	this->capacidade = capacidade;
	this->elementos = new No*[this->capacidade];
	
	for(unsigned int i = 0; i < this->capacidade; i++)
		this->elementos[i] = NULL;	
}

ListaHash::~ListaHash() {
	for(unsigned int i = 0; i < this->capacidade; i++) {
		No* atual = this->elementos[i];
		
		while(atual != NULL) {
			No* auxiliar = atual;
			atual = atual->proximo;
			delete auxiliar;
		}
	}
	delete [] elementos;
}

int ListaHash::hashCode(string chave) {
	long codigo;
	
	for(unsigned int i = 0; i < chave.length(); i++)
		codigo = (PRIMO * codigo + chave[i]) % this->capacidade;
	
	return codigo;
}

bool ListaHash::existe(string chave, string valor) {
	int posicao = this->hashCode(chave);
	No* atual = this->elementos[posicao];
	
	if (atual != NULL) {
		if (atual->chave == chave and atual->valor == valor) {
			return true;
		} else if (atual->proximo != NULL) {
			atual = atual->proximo;
			
			while(atual != NULL) {
				if (atual->chave == chave and atual->valor == valor)
					return true;
				
				atual = atual->proximo;
			}
		}
	}
	
	return false;
}

void ListaHash::insere(string chave, string valor) {
	int posicao = this->hashCode(chave);
	
	// trata duplicados
	if (not this->existe(chave, valor)) {	
		if (elementos[posicao] == NULL) {
			// nao existe ninguem na posicao, pode inserir
			elementos[posicao] = new No(chave, valor);
		} else {
			// caso de colisao dos valores
			No* atual = elementos[posicao];
			
			while(atual->proximo != NULL) {
				atual = atual->proximo;
			}
			
			atual->proximo = new No(chave, valor);
		}
	}
}

No* ListaHash::recupera(string chave) {
	int posicao = this->hashCode(chave);
	No* atual = this->elementos[posicao];
	
	if (atual != NULL) {
		if (atual->chave == chave) {
			return atual;
		} 
		
		atual = atual->proximo;
		
		while(atual != NULL) {
			if (atual->chave == chave)
				return atual;
		}
	} 
	
	return NULL;
}

int main() {
	
	ListaHash lh;
	
	lh.insere("Leonardo", "Leonardo Henrique de Braz");
	lh.insere("Luis", "Luis Wagner");
	lh.insere("Luis" , "Luis Wagner M");
	lh.insere("Guilherme", "Guilherme Melo");
	
	No* luis = lh.recupera("Luis");
	if (luis) {
		cout << luis->getChave() << ":" << luis->getValor() << endl;
	}
	return 0;
}

