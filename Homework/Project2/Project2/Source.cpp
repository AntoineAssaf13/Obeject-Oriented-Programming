// hw02.cpp : Defines the entry point for the console application.
//Antoine Assaf (aca432) Homework 2: Creating a warrior game powered by commands in a text file.  Creating, and creating fights between warriors as well as checking their status.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Warrior Structure that holds the name and remaining strength of a specific warrior
struct Warrior {
	string name;
	int strength;
};

//Function used to generate a new warrior and add it to the vector of existing warriors
void createWarrior(vector<Warrior>& warriors, const string& warriorOne, const int& strength);

//Function used to display the number of warriors, each of their names and their status in strength
void display(const vector<Warrior>& warriors);

//Function used when two warriors battle, depending on their strength, a specific output will be displayed and strength will be deducted from the warriors if necessary
void battle(vector<Warrior>& warriors, const string& warriorOne, const string& warriorTwo);

//Main function containing the vector of warriors and that is in charge of reading each command from the warrior.txt file
int main() {
	vector<Warrior> warriors;
	ifstream warriorList("warriors.txt");
	if (!warriorList) {
		cerr << "Failed to Open File";
		exit(1);
	}
	string command;
	string warriorOne;
	string warriorTwo;
	int strength;
	//Loop that reads the first token of each line to see what command is being given
	while (warriorList >> command) {
		//Create new warrior
		if (command == "Warrior") {
			warriorList >> warriorOne >> strength;
			createWarrior(warriors, warriorOne, strength);
		}
		//Display Status
		else if (command == "Status") {
			display(warriors);
		}
		//Two warriors battle
		else if (command == "Battle") {
			warriorList >> warriorOne >> warriorTwo;
			battle(warriors, warriorOne, warriorTwo);
		}
	}
}

void createWarrior(vector<Warrior>& warriors, const string& warriorOne, const int& strength) {
	Warrior newWarrior;
	newWarrior.name = warriorOne;
	newWarrior.strength = strength;
	warriors.push_back(newWarrior);
}

void display(const vector<Warrior>& warriors) {
	cout << "There are " << warriors.size() << " warriors" << endl;
	//Goes through the vector of warriors and displays their name and strength
	for (Warrior warrior : warriors) {
		cout << "Warrior: " << warrior.name << ", Strength: " << warrior.strength << endl;
	}
}


void battle(vector<Warrior>& warriors, const string& warriorOne, const string& warriorTwo) {
	//default values for the indices in order to check whether or not the given warrior name exists in the warrios vector
	int indexOne = -1;
	int indexTwo = -1;
	//Checks the warrios vector and saves the index of the desired warriors
	for (size_t i = 0; i < warriors.size(); ++i) {
		if (warriors[i].name == warriorOne) {
			indexOne = i;
		}
		else if (warriors[i].name == warriorTwo) {
			indexTwo = i;
		}
	}
	//If one of the warriors does not exist, then the function will stop after this first if statement
	if (indexOne == -1 || indexTwo == -1) {
		cout << "At least one of these warriors does not exist!" << endl;
	}
	else {
		cout << warriors[indexOne].name << " battles " << warriors[indexTwo].name << endl;
		//If both warrios are dead
		if (warriors[indexOne].strength == 0 && warriors[indexTwo].strength == 0) {
			cout << "Oh, NO! They're both dead! Yuck" << endl;
		}
		//If one of the warrios are dead
		else if (warriors[indexOne].strength != 0 && warriors[indexTwo].strength == 0) {
			cout << "He's dead, " << warriors[indexOne].name << endl;
		}
		else if (warriors[indexOne].strength == 0 && warriors[indexTwo].strength != 0) {
			cout << "He's dead, " << warriors[indexTwo].name << endl;
		}
		//If both warriors are alive but have the same strength value
		else if (warriors[indexOne].strength == warriors[indexTwo].strength) {
			warriors[indexOne].strength = 0;
			warriors[indexTwo].strength = 0;
			cout << "Mutual Annihalation: " << warriors[indexOne].name << " and " << warriors[indexTwo].name << " die at each other's hands" << endl;
		}
		//If both warrios are alive and one has a higher strength level, the weaker one's strength will go to 0 while the stronger one will have its strength subtracted by the original value of the weaker
		else if (warriors[indexOne].strength > warriors[indexTwo].strength) {
			warriors[indexOne].strength -= warriors[indexTwo].strength;
			warriors[indexTwo].strength = 0;
			cout << warriors[indexOne].name << " defeats " << warriors[indexTwo].name << endl;
		}
		else if (warriors[indexOne].strength < warriors[indexTwo].strength) {
			warriors[indexTwo].strength -= warriors[indexOne].strength;
			warriors[indexOne].strength = 0;
			cout << warriors[indexTwo].name << " defeats " << warriors[indexOne].name << endl;
		}
	}
}




