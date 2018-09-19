//#include "stdafx.h"
#include <vector>
#include <string>
#include "Noble.h"
#include "Protector.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {

	//Get the noble's name
	string Noble::getName() const{
		return name;
	}

	//Lords hiring a protector function
	bool Lord::hires(Protector& protector){
		if (!alive) {
			//cout << name << " cannot hire since they are already dead." << endl;
			return false;
		}
		if (protector.isHired() == true) {
			//cout << protector.getName() << " is already employed." << endl;
			return false;
		}
		if (protector.getStrength() == 0) {
			return false;
		}
		else {
			Protector* newPointer = &protector;
			army.push_back(newPointer);
			protector.employ(this);
			armyNum += 1;
			armyStrength += protector.getStrength();
			return true;
		}
	}

	//Lord firing a protector function
	bool Lord::fire(Protector& protector) {
		if (!alive) {
			//cout << "You cannot fire if you are dead!" << endl;
			return false;
		}
		//Goes through the vectore and increments everything backwards to get rid of the fired warrior in the army list.
		for (size_t index = 0; index < army.size(); index++) {
			if (protector.getName() == army[index]->getName()) {
				protector.unemploy();
				cout << protector.getName() << ", you're fired! -- " << name << endl;
				for (size_t changer = index; changer < army.size(); changer++) {
					if (changer == army.size() - 1) {
						continue;
					}
					else {
						int next_ind = changer + 1;
						Protector* next_member = army[next_ind];
						army[changer] = next_member;
					}
				}
				army.pop_back();
				armyNum -= 1;
				armyStrength -= protector.getStrength();
				return true;
			}

		}
		//cout << "Protector does not exist in this army." << endl;
		return false;
	}

	//If a protector deserts his/her lord.  Yes we could use fire but I had this new function to not have outputs.
	bool Lord::desert(Protector& protector){
		for (size_t index = 0; index < army.size(); index++) {
			if (protector.getName() == army[index]->getName()) {
				protector.unemploy();
				for (size_t changer = index; changer < army.size(); changer++) {
					if (changer == army.size() - 1) {
						continue;
					}
					else {
						int next_ind = changer + 1;
						Protector* next_member = army[next_ind];
						army[changer] = next_member;
					}
				}
				army.pop_back();
				armyNum -= 1;
				armyStrength -= protector.getStrength();
				return true;
			}

		}
		//cout << "Protector does not exist in this army." << endl;
		return false;
	}

	//Looks through the lord's army to find a specific protector
	Protector* Lord :: protectorLookup(const std::string& name) const {
		for (size_t index = 0; index < army.size(); index++) {
			if (army[index]->getName() == name) {
				return army[index];
			}
		}
		return nullptr;
	}

	//Get Lord's strength
	int Lord::getStrength() const{
		return armyStrength;
	}

	//Get PWSTF's strength
	int PersonWithStrengthToFight::getStrength() const{
		return ownStrength;
	}

	//Function to modify lord's strength post battle
	void Lord::setStrength(double damage) {
		if (damage = 0) {
			armyStrength = 0;
			for (size_t index = 0; index < army.size(); index++) {
				army[index]->subtractStrength(0);
			}
			return;
		}
		armyStrength = armyStrength - (armyStrength*damage);
		for (size_t index = 0; index < army.size(); index++) {
			army[index]->subtractStrength(damage);
			army[index]->display();
		}
	}

	//Function to modify PWSTF's strength post battle
	void PersonWithStrengthToFight::setStrength(double damage) {
		if (damage = 0) {
			ownStrength = 0;
			return;
		}
		ownStrength = ownStrength = ownStrength - (ownStrength*damage);
	}

	//Noble battle function
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

		double nobleOneStr = this->getStrength();
		double nobleTwoStr = otherNoble.getStrength();

		if (nobleOneStr == nobleTwoStr) {
			this->setStrength(0);
			otherNoble.setStrength(0);
			otherNoble.alive = false;
			alive = false;
			cout << "Mutual Annihilation: " << name << " and " << otherNoble.name << " die at each other's hands." << endl;
			return;
		}
		

		if (nobleOneStr > nobleTwoStr) {
			double damage = nobleTwoStr / nobleOneStr;
			otherNoble.setStrength(0);
			this->setStrength(damage);
			otherNoble.alive = false;
			cout << name << " defeats " << otherNoble.name << endl;
			return;
		}
		else if (nobleOneStr < nobleTwoStr) {
			double damage = nobleTwoStr / nobleTwoStr;
			this->setStrength(0);
			otherNoble.setStrength(damage);
			alive = false;
			cout << otherNoble.name << " defeats " << name << endl;
			return;

		}
	}
}
