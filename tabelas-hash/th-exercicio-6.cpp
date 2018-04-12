#include <iostream>

using namespace std;

int hash(int letra) {
	return letra % 13;
	
}

int main() {

	int qtd;
	cin >> qtd;
	for(int i = 0; i < qtd; i++) {
		int val;
		cin >> val;
		cout << val << ": " << hash(val) << endl;
	}
	 
	return 0;
}

