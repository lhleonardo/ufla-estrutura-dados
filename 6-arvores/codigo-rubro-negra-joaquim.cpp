#include <iostream>
#include <cstdlib>


using namespace std;

//constantes 
const unsigned PRETO = 0;
const unsigned VERMELHO = 1;

//usando bit field, para economizar memória

class noh{
	friend class arvoreRN;
	private:
	unsigned chave : 31;
	unsigned cor : 1;
	noh* esq;
	noh* dir;
	noh* pai;
};

class arvoreRN{
	private:
	noh* raiz;
	bool arrumaInsercao(noh* umNoh);
	bool arrumaRemocao(noh* umNoh, noh* paiUmNoh);
	void girarDireita(noh* umNoh);
	void girarEsquerda(noh* umNoh);
	//menor e maior valor de uma subarvore com pai em 
	//raizSub
	noh* minimoAux(noh* raizSub);
	noh* maximoAux(noh* raizSub);
	//transplanta o nó novo para o local onde estava o antigo
	void transplanta(noh* antigo,noh* novo);
	void percorreEmOrdemAux(noh* umNoh, int nivel);
	noh* buscaAux(unsigned chave);
	
	public:
	arvoreRN();
	bool insere(unsigned umaChave);
	bool remove(unsigned umaChave);
	unsigned minimo();
	unsigned maximo();
	void percorreEmOrdem();
	bool busca(unsigned chave);
};

arvoreRN ::arvoreRN(){
	raiz = NULL;
}

//insere uma chave na arvore 
//chama arruma insercao para corrigir eventuais problemas
bool arvoreRN :: insere(unsigned umaChave){
	//primeiro criamos um nó para inserção
	noh* umNoh = new noh;
	umNoh->chave = umaChave;
	umNoh->esq = NULL;
	umNoh->dir = NULL;
	
	//checa primeiro se não é o primeiro nó
	//se for, insere ele, como preto
	if(raiz == NULL){
		umNoh->cor = PRETO;
		umNoh->pai = NULL;
		raiz = umNoh;
		return true;
	}
	
	//não é o primeiro nó, busca posicao na arvore
	noh* atual = raiz;
	noh* anterior;
	while(atual != NULL){
		anterior = atual;
		if(umaChave > atual->chave){
			atual = atual->dir;
		}
		else{
			atual = atual->esq;
		}
	}
	
	//achou posição, insere o nó, como vermelho
	umNoh->pai = anterior;
	//cout << "VERMELHO" << endl;
	umNoh->cor = VERMELHO;
	while((umNoh != raiz) and (umNoh->pai->cor == VERMELHO)){
		//encontrando o tio
		if(umNoh->pai != raiz){
			if(umNoh->pai == umNoh->pai->pai->esq){
				tio = umNoh->pai->pai->dir;
			}
			else{
				tio = umNoh->pai->pai>esq;
			}
		}
		else{//se pai é raiz, entao tio é nulo
			tio = NULL;
		}
		//se tio é vermelho, faça o seguinte:
		//i)altere cor do pai e tio como preto
		//ii)altere cor do avô como vermelho
		//iii)mova umNoh para o avô, para continuar verificaçao
		if((tio != NULL) and (tio->cor == VERMELHO)){
			tio->cor = PRETO;
			umNoh->pai->cor = PRETO;
			umNoh->pai->pai->cor = VERLMELHO;
			umNoh = umNoh->pai->pai;
			//daqui volta ao while
		}
		else{//tio é preto(NULL também é preto)
			//tio é preto e pai é vermelho, precisa
			//fazer rotação, tem 4 situações
			//EE, ED, DE e DD
			
			//Caso EE(esquerda-esquerda)
			//i)troque cores de pai e avô
			//ii)rotacione à direita o avô
			
			if((umNoh->pai == umNoh->pai->pai->esq)and(umNoh==umNoh->pai-esq)){
				umNoh->pai->cor = PRETO;
				umNoh->pai->pai->cor = VERMELHO;
				girarDireita(umNoh->pai->pai);
				continue; // volta ao while para continuar checagem
			}
			//Caso ED(esquerda-direita);
			//i)troque nó atual com o pai
			//ii)rotacione à esquerda o novo nó atual pai
			//iii)troque cores do pai e do avô (após rotação)
			//iv)rotacione à direita o avô
			if((umNoh->pai == umNoh->pai->pai->esq)and(umNoh == umNoh->pai->dir)){
				umNoh = umNoh->pai;
				girarEsquerda(umNoh);
				umNoh->pai->cor = PRETO;
				umNoh->pai->pai->cor = VERMELHO;
				girarDireita(umNoh->pai->pai);
				continue;//volta ao while para continuar checagem
			}
			
			//caso DD(direita-direita)
			//i)troque cores de pai e avô
			//ii)rotacione à esquerda o avô
			if((umNoh->pai == umNoh->pai->pai->dir) and (umNoh == umNoh->pai->dir)){
				umNoh->pai->cor = PRETO;
				umNoh->pai->pai->cor = VERMELHO;
				girarEsquerda(umNoh->pai->pai);
				continue;//volta ao while para continuar checagem
			}
			//caso DE (direita-esquerda)
			//i)troque nó atual com o pai
			//ii)rotacione à direita o novo nó atual
			//iii)troque cores do pai e do avô(após rotação)
			//iv)rotaciona à esquerda o avô
			if((umNoh->pai == umNoh->pai->pai->dir) and((umNoh == umNoh->pai->esq)){
				umNoh = umNoh->pai;
				girarEsquerda(umNoh);
				umNoh->pai->cor = PRETO;
				umNoh->pai->pai->cor = VERMELHO;
				girarEsquerda(umNoh->pai->pai);
				continue;
			}
		}//fim do else
	}//fim do while
	
	//caso tenhamos alterado a cor da raiz em alguma momento
	// arrumamos aqui
	raiz->cor = PRETO;
	return true;
}
	


