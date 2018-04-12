#include <iostream>

using namespace std;

int hash(char letra) {
	return (letra-65) % 17;
	
}

int main() {
	char letra[13];
	for(int i = 0; i < 13; i++) {
		cin >> letra[i];
	}
	
	for(int i = 0; i < 13; i++) {
		cout << letra[i] << ": " << hash(letra[i]) << endl;
	}
	
	return 0;
}
