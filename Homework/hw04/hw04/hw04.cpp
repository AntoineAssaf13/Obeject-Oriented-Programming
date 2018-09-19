// hw04.cpp : Defines the entry point for the console application.
//Antoine Assaf, aca432: homework 4, creating a noble and warrior class where nobles hire and fire the warriors and battle other nobles with armies of warriors.

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
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

private:
	vector<Warrior*> army;
	string name;
	double armyStrength;
	int armyNum;
	bool alive = true;
};


int main()
{
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);
	
	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

}

