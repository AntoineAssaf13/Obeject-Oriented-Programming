//#include "stdafx.h"
#include <vector>
#include <string>
#include "Warrior.h"
#include "Noble.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {

	string Noble::getName() const {
		return name;
	}
	//Hires a warrior but first checks if the warrior is alive and not already employed
	bool Noble::hire(Warrior& warrior) {
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
			warrior.employ(this);
			armyNum += 1;
			armyStrength += warrior.getStrength();
			return true;
		}
	}
	//Lookup specific warrior
	Warrior* Noble::warriorLookup(const string& name) {
		for (size_t index = 0; index < army.size(); index++) {
			if (army[index]->getName() == name) {
				return army[index];
			}
		}
		return nullptr;
	}
	//Fires the warrior if they are a part of this noble's army
	bool Noble::fire(Warrior& warrior) {
		if (!alive) {
			cout << "You cannot fire if you are dead!" << endl;
			return false;
		}
		//Goes through the vectore and increments everything backwards to get rid of the fired warrior in the army list.
		for (size_t index = 0; index < army.size(); index++) {
			if (warrior.getName() == army[index]->getName()) {
				warrior.unemploy();
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

	bool Noble::desert(Warrior& warrior) {
		for (size_t index = 0; index < army.size(); index++) {
			if (warrior.getName() == army[index]->getName()) {
				warrior.unemploy();
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
	/*
	void Noble::display() const {
		cout << name << " has an army of " << armyNum << endl;
		for (size_t index = 0; index < army.size(); index++) {
			cout << "\t" << army[index]->getName() << ": " << army[index]->getStrength() << endl;
		}
	}
	*/
	//Battle conditions depending on whether or not both warriors are alive, dead (or a single one).  If both warriors are alive, appropriate calculations are done.
	void Noble::battle(Noble& otherNoble) {

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
			double damage = otherNoble.armyStrength / armyStrength;
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
	ostream& operator<<(ostream& os, const Noble& rhs) {
		os << rhs.name << " has an army of " << rhs.armyNum << endl;
		for (size_t index = 0; index < rhs.army.size(); index++) {
			cout << "\t" << rhs.army[index]->getName() << ": " << rhs.army[index]->getStrength() << endl;
		}
		return os;
	}
}