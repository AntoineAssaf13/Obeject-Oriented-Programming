#ifndef WARRIOR_H
#define _WARRIOR_H
#pragma once
//#include "stdafx.h"
#include <string>
#include "Noble.h"

namespace WarriorCraft {

	class Noble;

	class Warrior {
	public:
		Warrior(const std::string& newName, int newStrength) : name(newName), strength(newStrength)/*, employer(nullptr)*/ {}
		bool isHired() const;
		std::string getName() const;
		int getStrength() const;
		bool employ(Noble* newEmployer);
		bool unemploy();
		bool runaway();
		void subtractStrength(double subCount);
	private:
		std::string name;
		int strength;
		bool hired = false;
		Noble* employer;
	};

}
#endif
