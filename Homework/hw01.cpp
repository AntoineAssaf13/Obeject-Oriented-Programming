// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


int main()
{
	cout << "Hello";
	ifstream coded_file("encrypt.txt");
	if (!coded_file) {
		cerr << "Failed to open encrypted text";
		exit(1);
	}
	string rotation;
	getline(coded_file, rotation);
	cout << rotation <<endl;
}

