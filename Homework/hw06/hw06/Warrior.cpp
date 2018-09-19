//#include "stdafx.h"
#include <vector>
#include <string>
#include "Warrior.h"
#include "Noble.h"
#include <iostream>
using namespace std;


namespace WarriorCraft {
	//Checks if warrior is hired
	bool Warrior::isHired() const {
		return hired;
	}

	//Gets warrior name
	string Warrior::getName() const {
		return name;
	}

	//Gets warrior strength
	int Warrior::getStrength() const {
		return strength;
	}


	bool Warrior::employ(Noble* newEmployer) {
		if (!hired) {
			hired = true;
			employer = newEmployer;
			return true;
		}
		return false;
	}

	bool Warrior::unemploy() {
		if (hired) {
			hired = false;
			employer = nullptr;
			return true;
		}
		return false;
	}

	bool Warrior::runaway() {
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
	void Warrior::subtractStrength(double subCount) {
		if (subCount == 0) {
			strength = 0;
			return;
		}
		strength -= (strength * subCount);
	}

}