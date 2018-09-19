#ifndef NOBLE_H
#define _NOBLE_H
#pragma once
//#include "stdafx.h"
#include "Protector.h"
#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {

	class Protector;
	class Warrior;
	class Wizard;
	class Archer;
	class Swordsman;

	class Noble {
	public:
		Noble(const std::string& newName) : name(newName), alive(true) {}
		void battle(Noble& otherNoble);
		std::string getName() const;
		virtual int getStrength() const = 0;
		virtual void setStrength(double damage) = 0;
	protected:
		std::string name;
		bool alive;
	};

	class PersonWithStrengthToFight : public Noble {
	public:
		PersonWithStrengthToFight(const std::string& newName, double strength) : Noble(newName), ownStrength(strength) {}
		int getStrength() const;
		void setStrength(double damage);
	private:
		double ownStrength;
	};

	class Lord : public Noble {
	public:
		Lord(const std::string& newName) : Noble(newName), armyStrength(0) {}
		int getStrength() const;
		void setStrength(double damage);
		Protector* protectorLookup(const std::string& name) const;
		bool fire(Protector& protector);
		bool hires(Protector& protector);
		bool desert(Protector& protector);
	private:
		std::vector<Protector*> army;
		double armyStrength;
		int armyNum;
	};

}



#endif

