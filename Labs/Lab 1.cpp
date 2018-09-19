#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main(){
	ifstream gol("life.txt");
	if (!gol) {
		cerr << "Failed to Open Life"
		exit(1)
	}
	gol.open("life.txt");
	string line;
	while (getline(gol >> line)) {
		cout << line << endl
	}
}