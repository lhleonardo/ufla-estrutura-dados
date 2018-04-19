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
 
 typedef string Chave;
 typedef string Valor;
 
 class No {
     public:
        No(Chave chave = "", Valor valor = "", No* proximo = NULL);
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
        
        void adiciona(Chave chave, Valor valor);
        bool existe(Chave chave);
     private:
        No** elementos;
        int qtdInseridos;
        int capacidade;
        
        int hashCode(string chave);
 };
 
 TabelaHash::TabelaHash(unsigned int cap) : capacidade(cap) {
     this->elementos = new No*[this->capacidade];
 }
