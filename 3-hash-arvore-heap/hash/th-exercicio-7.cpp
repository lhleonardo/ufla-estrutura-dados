#include <iostream>

using namespace std;
/**
 * Implemente uma tabela hash com um número genérico n de posições, 
 * informado durante a construção da tabela, com resolução de colisões 
 * por encadeamento.  
 * 
 * Utilize hash h(k) = k mod n, em que k é a chave do registro sendo 
 * armazenado e n é o número de posições da tabela.
 *  
 * */
 
 typedef int Chave;
 typedef int Valor;
 
 class No {
     friend class TabelaHash;
     public:
        No(Chave chave, Valor valor, No* proximo = NULL);
     private:
        Chave chave;
        Valor valor;
        No* proximo;
 };
 
 No::No(Chave key, Valor value, No* proximo) : chave(key), valor(value) {
     this->proximo = proximo;
 }
 
 class TabelaHash {
     public:
        TabelaHash(unsigned int capacidade = 20);
        ~TabelaHash();
        
        bool existe(Chave chave);
        void adiciona(Chave chave, Valor valor);
        void altera(Chave chave, Valor valor);
        Valor recupera(Chave chave);
        
     private:
        No** elementos;
        unsigned int qtdInseridos;
        unsigned int capacidade;
        
        int hashCode(Chave chave);
 };
 
 TabelaHash::TabelaHash(unsigned int cap) : capacidade(cap) {
     this->elementos = new No*[this->capacidade];
 }
 
 TabelaHash::~TabelaHash() {
     No* atual;
     for(unsigned int i = 0; i < this->capacidade; i++) {
         atual = elementos[i];
         delete atual;
     }
     
     delete [] elementos;
 }
 
 int TabelaHash::hashCode(Chave chave) {
     return chave % this->capacidade;     
 }
 
 bool TabelaHash::existe(Chave chave) {
     int posicao = this->hashCode(chave);
     
     if (elementos[posicao] != NULL) {
         if (elementos[posicao]->chave == chave) {
             return true;
         } else {
             if (elementos[posicao]->proximo != NULL) {
                 No* temp = elementos[posicao];
                 
                 while(temp->chave != chave and temp->proximo != NULL) {
                     temp = temp->proximo;
                 }
                 
                 if (temp != NULL) 
                    return true;
             }
         }
     }
     
     return false;
 }
 
 void TabelaHash::adiciona(Chave chave, Valor valor) {
     if (not existe(chave)) {
         int posicao = this->hashCode(chave);
         
         No* elemento = new No(chave, valor);
         
         if (elementos[posicao] != NULL) {
             No* aux = elementos[posicao];
             
             while(aux->proximo != NULL) {
                 aux = aux->proximo;
             }
             
             aux->proximo = elemento;
         } else {
             // VAI SER A CABEÇA DO ENCADEAMENTO
             elementos[posicao] = elemento;
         }
     } else {
         // CHAVE EXISTE NA TABELA, NAO DEVE ADICIONAR
         cerr << "A chave \"" << chave << "\" se encontra na tabela.";
     }
 }
 
 Valor TabelaHash::recupera(Chave chave) {
     jklhjhkjyhkuyhg
     
 }
 
 int main() {
     TabelaHash tabela(20);
     
     tabela.adiciona(1, 10);
     tabela.adiciona(2, 20);
     tabela.adiciona(3, 30);
     tabela.adiciona(4, 40);   
     tabela.adiciona(5, 50);    
     tabela.adiciona(22, 60);
     
     cout << tabela.existe(22);
     
     
     return 0;
 }
