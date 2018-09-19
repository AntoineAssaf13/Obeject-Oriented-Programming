// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main() {
	vector <string> grid1;
	vector <string> grid2;
	ifstream gol("life.txt");
	if (!gol) {
		cerr << "Failed to Open Life";
		exit(1);
	}
	string line;
	grid1.push_back("----------------------");
	while (getline(gol, line)) {
		grid1.push_back("-" + line + "-");
	}
	grid1.push_back("----------------------");
	for (string item : grid1) {
		cout << item << endl;
	}
	cout << " " << " " << endl;

	grid2 = grid1;
	int counter = 0;
	for (size_t index = 0; index <= 10; ++index) {
		for (size_t i = 1; i <  grid1.size()-1; ++i) {
			for (size_t j = 1; j < grid1[index].size()-1; ++j) {
		//cout << i << " " << j << endl;
				if (grid1[i][j + 1] == '*'){
					counter += 1;
				}
				
				if (grid1[i][j - 1] == '*') {
					counter += 1;
				}
				if (grid1[i+1][j] == '*') {
					counter += 1;
				}
				if (grid1[i-1][j] == '*') {
					counter += 1;
				}
				
				if (grid1[i-1][j + 1] == '*') {
					counter += 1;
				}
				if (grid1[i-1][j - 1] == '*') {
					counter += 1;
				}
				if (grid1[i+1][j + 1] == '*') {
					counter += 1;
				}
				if (grid1[i+1][j - 1] == '*') {
					counter += 1;
				}
				
				if (counter == 3 || counter == 2 && grid1[i][j] == '*') {
					grid2[i][j] = '*';
				}
				else {
					grid2[i][j] = '-';
				
				}
				if (counter == 3 && grid1[i][j] == '-') {
					grid2[i][j] = '*';
				}
				
				
				counter = 0;
			}
		}
		
		for (string item : grid2) {
			cout << item << endl;
		}
		cout << " " << " " << endl;
		grid1 = grid2;
	}
}




