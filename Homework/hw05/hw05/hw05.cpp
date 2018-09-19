// hw05.cpp : Defines the entry point for the console application.
//Antoine Assaf, aca432: homework 4, creating a noble and warrior class where nobles hire and fire the warriors and battle other nobles with armies of warriors.
//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Warrior {
public:
	Warrior(const string& newName, int newStrength) : name(newName), strength(newStrength) {}

	//Checks if warrior is hired
	bool isHired() const {
		return hired;
	}

	//Gets warrior name
	string getName() const {
		return name;
	}

	//Gets warrior strength
	int getStrength() const {
		return strength;
	}

	//Changes warrior from hired to not hired or vice versa depending on current status
	void toggleStatus() {
		if (hired) {
			hired = false;
			return;
		}
		hired = true;
	}

	//If int is 0 the warrior will be dead, if not the warrior's strength will be subtracted by the variable int
	void subtractStrength(double subCount) {
		if (subCount == 0) {
			strength = 0;
			return;
		}
		strength -= (strength * subCount);
	}

private:
	string name;
	int strength;
	bool hired = false;

};

class Noble {
public:
	Noble(const string& newName) : name(newName), armyStrength(0) {}

	string getName() {
		return name;
	}
	//Hires a warrior but first checks if the warrior is alive and not already employed
	bool hire(Warrior& warrior) {
		if (!alive) {
			cout << name << " cannot hire since they are already dead." << endl;
			return false;
		}
		if (warrior.isHired() == true) {
			cout << warrior.getName() << " is already employed." << endl;
			return false;
		}
		else {
			Warrior* newPointer = &warrior;
			army.push_back(newPointer);
			warrior.toggleStatus();
			armyNum += 1;
			armyStrength += warrior.getStrength();
			return true;
		}
	}
	//Lookup specific warrior
	Warrior* warriorLookup(const string& name) {
		for (size_t index = 0; index < army.size(); index++) {
			if (army[index]->getName() == name) {
				return army[index];
			}
		}
		return nullptr;
	}
	//Fires the warrior if they are a part of this noble's army
	bool fire(Warrior& warrior) {
		if (!alive) {
			cout << "You cannot fire if you are dead!" << endl;
			return false;
		}
		//Goes through the vectore and increments everything backwards to get rid of the fired warrior in the army list.
		for (size_t index = 0; index < army.size(); index++) {
			if (warrior.getName() == army[index]->getName()) {
				cout << warrior.getName() << ", you're fired! -- " << name << endl;
				for (size_t changer = index; changer < army.size(); changer++) {
					if (changer == army.size() - 1) {
						continue;
					}
					else {
						int next_ind = changer + 1;
						Warrior* next_member = army[next_ind];
						army[changer] = next_member;
					}
				}
				army.pop_back();
				armyNum -= 1;
				armyStrength -= warrior.getStrength();
				return true;
			}

		}
		cout << "Warrior does not exist in this army." << endl;
		return false;
	}
	//Simple display of a Noble's army
	void display() const {
		cout << name << " has an army of " << armyNum << endl;
		for (size_t index = 0; index < army.size(); index++) {
			cout << "\t" << army[index]->getName() << ": " << army[index]->getStrength() << endl;
		}
	}

	//Battle conditions depending on whether or not both warriors are alive, dead (or a single one).  If both warriors are alive, appropriate calculations are done.
	void battle(Noble& otherNoble) {

		cout << name << " battles " << otherNoble.name << endl;
		if (!alive && otherNoble.alive) {
			cout << "He's dead, " << otherNoble.name << endl;
			return;
		}
		else if (alive && !otherNoble.alive) {
			cout << "He's dead, " << name << endl;
			return;
		}
		if (!alive && !otherNoble.alive) {
			cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
			return;
		}

		if (armyStrength == otherNoble.armyStrength) {
			cout << "Mutual Annihilation: " << name << " and " << otherNoble.name << " die at each other's hands." << endl;
			otherNoble.armyStrength = 0;
			armyStrength = 0;
			for (size_t index = 0; index < army.size(); index++) {
				army[index]->subtractStrength(0);
			}
			for (size_t index = 0; index < otherNoble.army.size(); index++) {
				otherNoble.army[index]->subtractStrength(0);
			}
			otherNoble.alive = false;
			alive = false;
			return;
		}

		if (armyStrength > otherNoble.armyStrength) {
			cout << name << " defeats " << otherNoble.name << endl;
			double damage = otherNoble.armyStrength/armyStrength;
			otherNoble.armyStrength = 0;
			armyStrength -= otherNoble.armyStrength;
			for (size_t index = 0; index < army.size(); index++) {
				army[index]->subtractStrength(damage); 
			}
			for (size_t index = 0; index < otherNoble.army.size(); index++) {
				otherNoble.army[index]->subtractStrength(0);
			}
			otherNoble.alive = false;
			return;
		}
		else if (armyStrength < otherNoble.armyStrength) {
			cout << otherNoble.name << " defeats " << name << endl;
			double damage = armyStrength / otherNoble.armyStrength;
			armyStrength = 0;
			otherNoble.armyStrength -= armyStrength;
			for (size_t index = 0; index < army.size(); index++) {
				army[index]->subtractStrength(0);
			}
			for (size_t index = 0; index < otherNoble.army.size(); index++) {
				otherNoble.army[index]->subtractStrength(damage);
			}
			alive = false;
			return;

		}

	}

private:
	vector<Warrior*> army;
	string name;
	double armyStrength;
	int armyNum;
	bool alive = true;
};

//Prototype all functions that are not within a class

bool createNoble(vector<Noble*>& nobles, const string& newName);

bool createWarrior(vector<Warrior*>& forHireWarriors, const string& newName, int strength);

void printStatus(const vector<Noble*>& nobles, const vector<Warrior*>& forHireWarriors);

bool newFire(const string& firstName, const string& secondName, vector<Noble*>& nobles, vector<Warrior*>& forHireWarriors);

bool newHire(const string& firstName, const string& secondName, vector<Noble*>& nobles, vector<Warrior*>& forHireWarriors);

void newBattle(const string& firstName, const string& secondName, vector<Noble*> nobles);


int main()
{
	vector<Noble*> nobles;
	vector<Warrior*> forHireWarriors;
	ifstream charList("nobleWarriors.txt");
	if (!charList) {
		cerr << "Failed to Open File";
		exit(1);
	}
	string command;
	string firstName;
	string secondName;
	int strength;
	//Check each command
	while (charList >> command) {
		if (command == "Noble") {
			charList >> firstName;
			createNoble(nobles, firstName);
		}

		else if (command == "Warrior") {
			charList >> firstName >> strength;
			createWarrior(forHireWarriors, firstName, strength);
		}
		else if (command == "Hire") {
			charList >> firstName >> secondName;
			newHire(firstName, secondName, nobles, forHireWarriors);
		}
		else if (command == "Status") {
			printStatus(nobles, forHireWarriors);
		}
		else if (command == "Fire") {
			charList >> firstName >> secondName;
			newFire(firstName, secondName, nobles, forHireWarriors);
		}
		else if (command == "Battle") {
			charList >> firstName >> secondName;
			newBattle(firstName, secondName, nobles);
		}
		//clear everything and remove from heap
		else if (command == "Clear") {
			for (size_t index = 0; index < forHireWarriors.size(); index++) {
				delete forHireWarriors[index];
			}
			int initSize = forHireWarriors.size();
			for (size_t index = 0; index < initSize; index++) {
				forHireWarriors.pop_back();
			}
			for (size_t index = 0; index < nobles.size(); index++) {
				delete nobles[index];
			}
			initSize = nobles.size();
			for (size_t index = 0; index < initSize; index++) {
				nobles.pop_back();
			}
		}
	}
}


bool createNoble(vector<Noble*>& nobles, const string& newName) {
	//error checking
	for (size_t index = 0; index < nobles.size(); index++) {
		if (nobles[index]->getName() == newName) {
			cout << "Name already exists!" << endl;
			return false;
		}
	}
	//create noble on heap
	Noble* newNoble = new Noble(newName);
	nobles.push_back(newNoble);
	return true;
}

bool createWarrior(vector<Warrior*>& forHireWarriors, const string& newName, int strength) {
	//error checking
	for (size_t index = 0; index < forHireWarriors.size(); index++) {
		if (forHireWarriors[index]->getName() == newName) {
			cout << "Name already exists!" << endl;
			return false;
		}
	}
	//create warrior on heap
	Warrior* newWarrior = new Warrior(newName, strength);
	forHireWarriors.push_back(newWarrior);
	return true;
}
//Text based user interface display
void printStatus(const vector<Noble*>& nobles, const vector<Warrior*>& forHireWarriors){
	cout << "Status" << endl << "======" << endl << "Nobles: " << endl;
	if (nobles.size() == 0) {
		cout << "None" << endl;
	}
	else {
		for (size_t index = 0; index < nobles.size(); index++) {
			nobles[index]->display();
		}
	}
	cout << "Unemployed Warriors: " << endl;
	if (forHireWarriors.size() == 0) {
		cout << "NONE" << endl;
	}
	else {
		for (size_t index = 0; index < forHireWarriors.size(); index++) {
			if (forHireWarriors[index] != nullptr) {
				cout << forHireWarriors[index]->getName() << ": " << forHireWarriors[index]->getStrength() << endl;
			}
		}
	}
}
bool newFire(const string& firstName, const string& secondName, vector<Noble*>& nobles, vector<Warrior*>& forHireWarriors) {
	int nobleNum = -1;
	for (size_t nIndex = 0; nIndex < nobles.size(); nIndex++) {
		if (nobles[nIndex]->getName() == firstName) {
			nobleNum = nIndex;
			break;
		}
	}
	//error checking
	Warrior* firedWarrior = nobles[nobleNum]->warriorLookup(secondName);
	if (nobleNum == -1 || firedWarrior == nullptr) {
		cout << "Either the noble or warrior does not exist" << endl;
		return false;
	}
	//call to class to fire
	nobles[nobleNum]->fire(*firedWarrior);
	forHireWarriors.push_back(firedWarrior);
	return true;
}

bool newHire(const string& firstName, const string& secondName, vector<Noble*>& nobles, vector<Warrior*>& forHireWarriors) {
	int nobleNum = -1;
	int warriorNum = -1;
	for (size_t nIndex = 0; nIndex < nobles.size(); nIndex++) {
		if (nobles[nIndex]->getName() == firstName) {
			nobleNum = nIndex;
			break;
		}
	}
	for (size_t wIndex = 0; wIndex < forHireWarriors.size(); wIndex++) {
		if (forHireWarriors[wIndex]->getName() == secondName) {
			warriorNum = wIndex;
			break;
		}
	}
	//error checking
	if (warriorNum == -1 || nobleNum == -1) {
		cout << "This warrior or Noble does not exist!" << endl;
		return false;
	}
	//remove hired warrior from non hired warrior vector
	else {
		nobles[nobleNum]->hire(*forHireWarriors[warriorNum]);
		for (size_t index = warriorNum; index < forHireWarriors.size(); index++) {
			if (index == forHireWarriors.size() - 1) {
				continue;
			}
			else {
				int next = index + 1;
				forHireWarriors[index] = forHireWarriors[next];
			}
		}
		forHireWarriors.pop_back();
		return true;
	}
}

void newBattle(const string& firstName, const string& secondName, vector<Noble*> nobles) {
	int nobleOne = -1;
	int nobleTwo = -1;
	for (size_t index = 0; index < nobles.size(); index++) {
		if (nobles[index]->getName() == firstName) {
			nobleOne = index;
			break;
		}
	}
	for (size_t index = 0; index < nobles.size(); index++) {
		if (nobles[index]->getName() == secondName) {
			nobleTwo = index;
			break;
		}
	}
	//error checking
	if (nobleOne == -1 || nobleTwo == -1) {
		cout << "One of these nobles does not exist!" << endl;
		return;
	}
	//call to class to start battle
	else {
		nobles[nobleOne]->battle(*nobles[nobleTwo]);
	}
}



	



