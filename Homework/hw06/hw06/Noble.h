#ifndef NOBLE_H
#define _NOBLE_H
#pragma once
//#include "stdafx.h"
#include <string>
#include <vector>
#include "Warrior.h"

namespace WarriorCraft {

	class Warrior;

	class Noble {
		friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
	public:
		Noble(const std::string& newName) : name(newName), armyStrength(0) {}

		std::string getName() const;
		bool hire(Warrior& warrior);
		Warrior* warriorLookup(const std::string& name);
		bool fire(Warrior& warrior);
		bool desert(Warrior& warrior);
		//void display() const;
		void battle(Noble& otherNoble);
	private:
		std::vector<Warrior*> army;
		std::string name;
		double armyStrength;
		int armyNum;
		bool alive = true;
	};
}
#endif