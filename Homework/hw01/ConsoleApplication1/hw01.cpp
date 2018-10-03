// ConsoleApplication1.cpp : Defines the entry point for the console application.
//Homework 1 , OOP, Antoine Assaf: Creating a simple caesar cypher decoder algorithm on C++

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//This serves to decrypt a specific character and will be used by the decryptString function.
char decryptChar(const char& letter, int rotation);

//This will decrypt an entire string and is the function being called by main.
void decryptString(string& line, int rotation);

//Main function that will handle reading the file and printing the decoded outputs.
int main()
{
	ifstream encryptedText("decrypt.txt");
	if (!encryptedText) {
		cerr << "Failed to open file";
		exit(1);
	}
	string line;
	int rotation;
	encryptedText >> rotation;
	getline(encryptedText, line);

	vector<string> encryptedVector;
	vector<string> finalVector;
	//Read the text and push each line into a vector
	while (getline(encryptedText, line)) {
		encryptedVector.push_back(line);
	}
	//Decrypt each line of the encryptedVector and pushes it into final vector in the correct order.
	for (size_t index = encryptedVector.size()-1; index+1 > 0; --index) {
		decryptString(encryptedVector[index], rotation);
		finalVector.push_back(encryptedVector[index]);
	}
	//output each line of the the now decrypted text.
	for (string item : finalVector) {
		cout << item << endl;
	}

}


void decryptString(string& line, int rotation) {
	//Checking every character in a string and decrypting it if necessary.
	for (size_t index = 0; index < line.size(); ++index) {
		line[index] = decryptChar(line[index], rotation);
	}
}



char decryptChar(const char& letter, int rotation) {
	if (letter >= 97 && letter - rotation < 97) {
		return (letter - rotation) + 26;
	}
	else if (letter >= 97 && letter <= 122) {
		return letter - rotation;
	}
	else {
		return letter;
	}
}

