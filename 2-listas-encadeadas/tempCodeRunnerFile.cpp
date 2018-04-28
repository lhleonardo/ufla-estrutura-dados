if (posAtual > this->qtdElementos) {
                cout << "A posicao maluca é: " << posAtual << endl;
                cout << "Seu valor é: ";
                if (atual != NULL) {
                    cout << atual->dado << endl;
                } else {
                    cout << "NULL" << endl;
                }
            }