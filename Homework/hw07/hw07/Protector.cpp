//#include "stdafx.h"
#include <vector>
#include <string>
#include "Protector.h"
#include "Noble.h"
#include <iostream>
using namespace std;


namespace WarriorCraft {
	//Check to see if hired
	bool Protector::isHired() const {
		return hired;
	}

	//Gets Protector name
	string Protector::getName() const {
		return name;
	}

	//Gets Protector strength
	int Protector::getStrength() const {
		return strength;
	}

	//Point the protector to its employer
	bool Protector::employ(Lord* newEmployer) {
		if (!hired) {
			hired = true;
			employer = newEmployer;
			return true;
		}
		return false;
	}
	//Set the employer pointer to nullptr
	bool Protector::unemploy() {
		if (hired) {
			hired = false;
			employer = nullptr;
			return true;
		}
		return false;
	}
	//If protector decides to desert his/her lord
	bool Protector::runaway() {
		if (hired) {
			hired = false;
			cout << name << " flees in terror, abandoning his lord, " << employer->getName() << endl;
			employer->desert(*this);
			employer = nullptr;
			return true;
		}
		return false;
	}


	//If int is 0 the warrior will be dead, if not the warrior's strength will be subtracted by the variable int
	void Protector::subtractStrength(double subCount) {
		if (subCount == 0) {
			strength = 0;
			return;
		}
		strength -= (strength * subCount);
	}

	//All subclasses for protector
	void Wizard::display() const {
		cout << "POOF" << endl;
	}

	void Warrior::display() const {
		cout << name << " says: Take that in the name of my lord, " << employer->getName() << endl;
	}

	void Archer::display() const {
		cout << "TWANG! ";
		Warrior::display();
	}

	void Swordsman::display() const {
		cout << "CLANG! ";
		Warrior::display();
	}
}