// hw03.cpp : Defines the entry point for the console application.
//Antoine Assaf, aca432 Homework 3:  Creating a a nested class using data hiding to give the warriors weapons

//#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Warrior Class that holds the name and weapon of the warrior.
class Warrior {
	//Weapon class that holds the strength and weapon name of the warrior.  Only accessible by the warrior class itself.
	class Weapon {
	public:
		Weapon(const string& newWeaponName, int newWeaponStrength) : weaponName(newWeaponName), strength(newWeaponStrength) {}
		int getStrength() const {
			return strength;
		}
		string getWeaponName() const {
			return weaponName;
		}
		//Subtract the strengths and set to 0 if number is negative for either of them
		void subtract(Weapon& weaponTwo) {
			int oldStrength = strength;
			strength -= weaponTwo.strength;
			weaponTwo.strength -= oldStrength;
			if (strength < 0) {
				strength = 0;
			}
			if (weaponTwo.strength < 0) {
				weaponTwo.strength = 0;
			}
		}
	private:
		string weaponName;
		int strength;
	};
public:
	Warrior(const string& newWarriorName, const string& newWeaponName, int newWeaponStrength) : warriorName(newWarriorName), warriorWeapon(newWeaponName, newWeaponStrength ){}
	void displayStatus() const {
		int strength = warriorWeapon.getStrength();
		string weaponName = warriorWeapon.getWeaponName();
		cout << "Warrior: " << warriorName << ", Weapon: " << weaponName << ", " << strength << endl;
	}
	string getWarriorName() const {
		return warriorName;
	}
	void fight(Warrior& warriorTwo){
		cout << warriorName << " battles " << warriorTwo.warriorName << endl;
		Weapon& weaponTwo = warriorTwo.warriorWeapon;

		if (warriorWeapon.getStrength() == 0 && weaponTwo.getStrength() == 0) {
			cout << "Oh, NO! They're both dead! Yuck" << endl;
		}
		//If one of the warrios are dead
		else if (warriorWeapon.getStrength() != 0 && weaponTwo.getStrength() == 0) {
			cout << "He's dead, " << warriorName << endl;
		}
		else if (warriorWeapon.getStrength() == 0 && weaponTwo.getStrength() != 0) {
			cout << "He's dead, " << warriorTwo.warriorName << endl;
		}
		//If both warrios are alive and calculations must be made
		else{
			warriorWeapon.subtract(weaponTwo);
			if (warriorWeapon.getStrength() > weaponTwo.getStrength()) {
				cout << warriorName << " defeats " << warriorTwo.warriorName << endl;
			}
			else if (warriorWeapon.getStrength() < weaponTwo.getStrength()) {
				cout << warriorName << " defeats " << warriorTwo.warriorName << endl;
			}
			else if (warriorWeapon.getStrength() == weaponTwo.getStrength()) {
				cout << "Mutual Annihalation: " << warriorName << " and " << warriorTwo.warriorName << " die at each other's hands" << endl;
			}
		}
	}
	
private:
	string warriorName;
	Weapon warriorWeapon;
};

//Function used to generate a new warrior and add it to the vector of existing warriors
void createWarrior(vector<Warrior>& warriors, const string& warriorOne, const string& weaponOrWarrior, const int& strength);
//Function used to display the number of warriors, each of their names weapon names and weapon strength.
void display(const vector<Warrior>& warriors);

//Function used when two warriors battle, will check if the warrior names are valid and then commence the fight.
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
	string weaponOrWarrior;
	int strength;
	//Loop that reads the first token of each line to see what command is being given
	while (warriorList >> command) {
		//Create new warrior
		if (command == "Warrior") {
			warriorList >> warriorOne >> weaponOrWarrior >> strength;
			createWarrior(warriors, warriorOne, weaponOrWarrior, strength);
		}
		//Display Status
		else if (command == "Status") {
			display(warriors);
		}
		//Two warriors battle
		else if (command == "Battle") {
			warriorList >> warriorOne >> weaponOrWarrior;
			battle(warriors, warriorOne, weaponOrWarrior); 
		} 
	}
}

void createWarrior(vector<Warrior>& warriors, const string& warriorOne, const string& weaponOrWarrior, const int& strength) {
	Warrior newWarrior(warriorOne, weaponOrWarrior, strength);
	warriors.push_back(newWarrior);
}

void display(const vector<Warrior>& warriors) {
	cout << "There are " << warriors.size() << " warriors" << endl;
	//Goes through the vector of warriors and displays their name and strength through the warrior class.
	for (Warrior warrior : warriors) {
		warrior.displayStatus();
	}
}


void battle(vector<Warrior>& warriors, const string& warriorOne, const string& warriorTwo) {
	//default values for the indices in order to check whether or not the given warrior name exists in the warrios vector
	int indexOne = -1;
	int indexTwo = -1;
	//Checks the warriors vector and saves the index of the desired warriors
	for (size_t i = 0; i < warriors.size(); ++i) {
		string checkName = warriors[i].getWarriorName();
		if (checkName == warriorOne) {
			indexOne = i;
		}
		else if (checkName == warriorTwo) {
			indexTwo = i;
		}
	}
	//If one of the warriors does not exist, then the function will stop after this first if statement
	if (indexOne == -1 || indexTwo == -1) {
		cout << "At least one of these warriors does not exist!" << endl;
	}
	else {
		Warrior& warriorOne = warriors[indexOne];
		Warrior& warriorTwo = warriors[indexTwo];
		warriorOne.fight(warriorTwo);
	}
}
