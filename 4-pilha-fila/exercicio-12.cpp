#include <iostream>

using namespace std;
//fila adiciona no final e tira do começo

class no{
	friend class fila;
	public:
		no();
	private:
		int dado;
		no* proximo;
};

class fila{
	public:
		fila ();
		~fila();
		void enfilera(int valor);
		int desinfilera ();
		int espia();
		void imprime();
		bool vazia();
		int pegaTamanho() {
			return tamanho;
		}
	private:
		no* primeiro;
		no* ultimo;
		int tamanho;
};

no::no(){
	proximo = NULL;
}

fila::fila(){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
};

fila::~fila(){
	while(primeiro != NULL){ // para ver se tem algo naquela posicao
		desinfilera();
	}
}

void fila::enfilera(int valor){
//primeiro cria um novo no
	no* novo = new no;
	novo -> dado = valor;
	if(vazia()){
		primeiro = novo;
		ultimo = novo;
	}else if(ultimo != NULL){
		ultimo -> proximo = novo;
		ultimo = novo;
	}
	
	//compara o ultimo porque sempre adiciona no final
	tamanho ++;
}

int fila::desinfilera(){
	//retorno um valor porque se quiser tirar um elemento do meio
	//posso armazenar os anteriores em um vetor, tirar o elemento que eu quero
	// e depois voltar os elementos que eu tirei para fila novamente
	no* aux;
	int info;
	aux = primeiro;
	info = primeiro -> dado;
	primeiro = primeiro -> proximo;
	if(vazia()){
		ultimo = NULL;
	}
	delete aux;
	tamanho --;
	return info;
}

void fila::imprime(){
	no* aux = primeiro;
	
	while(aux != NULL){ // ou seja tem elemento 
		cout << aux -> dado << " " ;
		aux = aux -> proximo;
	}
	cout << endl;
}	


bool fila::vazia(){
	return (primeiro == NULL);
}

int fila::espia(){
	return primeiro -> dado;
}

void compara(fila& f1, fila& f2, fila& f3){
	int v1, v2;
    
    while(not f1.vazia() and not f2.vazia()) {
        v1 = f1.espia();
        v2 = f2.espia();

        if (v1 < v2) {
            f3.enfilera(v1);
            f1.desinfilera();
        } else {
            f3.enfilera(v2);
            f2.desinfilera();
        }
    }

    fila* resto = f1.pegaTamanho() == 0 ? &f2 : &f1;

    while(not resto->vazia()) {
        f3.enfilera(resto->desinfilera());
    }

    cout << f1.pegaTamanho() << endl;
    cout << f2.pegaTamanho() << endl;
    f3.imprime();
}


int main(){
	fila f,f2;
	fila f3;
	
	f.enfilera(1);
	f.enfilera(3);
	f.enfilera(3);
	f.enfilera(7);
	f2.enfilera(4);
	f2.enfilera(6);
	f2.enfilera(8);
	f2.enfilera(10);

	compara(f,f2,f3);

    return 0;
}
