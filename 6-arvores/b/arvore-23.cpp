#include <iostream>
#define MAXIMO_CHAVES 2
#define MAXIMO_FILHOS 3
using namespace std;

typedef int Tipo;

class Bucket {
    // clang-format off
  friend class Arvore234;
    // clang-format on
  private:
    Tipo valores[MAXIMO_CHAVES + 1];
    Bucket* filhos[MAXIMO_FILHOS + 1];

    bool isFolha;
    unsigned qtdElementos;
    unsigned qtdFilhos;

  public:
    Bucket() : qtdElementos(0), qtdFilhos(0), isFolha(true) {
        for (unsigned i = 0; i < MAXIMO_FILHOS + 1; ++i) {
            filhos[i] = NULL;
        }
    }

    ~Bucket() {
        for (unsigned i = 0; i < MAXIMO_FILHOS + 1; i++) {
            delete this->filhos[i];
        }
    }
};

class Arvore234 {
  private:
    Bucket* raiz;
    unsigned qtdElementos;
};