#include <iostream>
#include <fstream>

using namespace std;

struct Pessoa {
    int idade;
    int anoNascimento;
};

int main() {
    int escolha;
    
    do {
        cout << "1 para inserir" << endl;
        cout << "2 para editar" << endl;
        cout << "3 para listar" << endl;
        cin >> escolha;

        switch(escolha) {
            case 1: {
                Pessoa nova;
                cout << "Idade: ";
                cin >> nova.idade;
                cout << "Ano de nascimento: ";
                cin >> nova.anoNascimento;

                ofstream gravador("testando.dat", ios::binary | ios::app);
                gravador.write((const char *) &nova, sizeof(Pessoa));
                
                cout << "Foi salvo com sucesso! " << endl;
            }
            case 2: {

            }
            case 3: {
                ifstream leitor("testando.dat", ios::binary);
                leitor.seekg(0, ios::end);
                int tamBytes = leitor.tellg();
                leitor.seekg(0, ios::beg);

                Pessoa valores[tamBytes/sizeof(Pessoa)];

                leitor.read((char *) (valores), tamBytes * sizeof(Pessoa));

                for(int i = 0; i < tamBytes/sizeof(Pessoa); i++) {
                    cout << "Idade: " << valores[i].idade << endl;
                    cout << "Ano de nascimento: " << valores[i].anoNascimento << endl;
                    cout << endl;
                }
            }
        }
    } while(escolha != 0);

    
}