// Lab02.cpp : Defines the entry point for the console application.
//aca432 lab 2

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Hydrocarbon {
	vector<string> name;
	int carbonAtoms;
	int hydroAtoms;
};

void createHydrocarbon(vector<Hydrocarbon>& hydrocarbons, const string& name, const int& carbonAtoms, const int& hydroAtoms) {
	for (Hydrocarbon& item : hydrocarbons) {
		if (item.carbonAtoms == carbonAtoms && item.hydroAtoms == hydroAtoms) {
			item.name.push_back(name);
			return;
		}
	}
	Hydrocarbon newHydrocarbon;
	newHydrocarbon.name.push_back(name);
	newHydrocarbon.carbonAtoms = carbonAtoms;
	newHydrocarbon.hydroAtoms = hydroAtoms;
	hydrocarbons.push_back(newHydrocarbon);
}

void display(const vector<Hydrocarbon>& hydrocarbons) {
	int biggestCarbon = 0;
	for (const Hydrocarbon& item : hydrocarbons) {
		if (item.carbonAtoms > biggestCarbon) {
			biggestCarbon = item.carbonAtoms;
		}
	}
		for (int index = 0; index <= biggestCarbon; ++index) {
			for (const Hydrocarbon& item : hydrocarbons) {
				if (item.carbonAtoms == index){
					cout << "C" << item.carbonAtoms << "H" << item.hydroAtoms << " ";
					for (string name : item.name) {
						cout << name << " ";
					}
					cout << endl;
				}
			}

	}
	

}

int main(){
	vector<Hydrocarbon> hydrocarbons;
	ifstream chemFile("formulae.txt");
	if (!chemFile) {
		cerr << "Failed to Open";
		exit(1);
	}
	string item;
	char carbon;
	int carbonNum;
	char hydro;
	int hydroNum;
	vector<string> nameAndFormula;

	while (chemFile >> item >> carbon >> carbonNum >> hydro >> hydroNum){
		createHydrocarbon(hydrocarbons, item, carbonNum, hydroNum);
	}
	display(hydrocarbons);
	
}

