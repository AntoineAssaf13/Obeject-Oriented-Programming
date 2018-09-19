#ifndef PROTECTOR_H
#define _PROTECTOR_H
#pragma once
//#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include "Noble.h"

namespace WarriorCraft {

	class Noble;
	class Lord;
	class PersonWithStrengthToFight;

	class Protector {
	public:
		Protector(const std::string& newName, double newStrength) : name(newName), strength(newStrength), hired(false), employer(nullptr) {}
		bool isHired() const;
		std::string getName() const;
		int getStrength() const;
		bool employ(Lord* newEmployer);
		bool unemploy();
		bool runaway();
		void subtractStrength(double subCount);
		virtual void display() const = 0;
	protected:
		std::string name;
		int strength;
		bool hired;
		Lord* employer;
	};

	class Wizard : public Protector {
	public:
		Wizard(const std::string& newName, double newStrength) : Protector(newName,newStrength) {}
		void display() const;
	};

	class Warrior : public Protector {
	public:
		Warrior(const std::string& newName, double newStrength) : Protector(newName, newStrength) {}
		virtual void display() const = 0;
	};

	class Archer : public Warrior {
	public:
		Archer(const std::string& newName, double newStrength) : Warrior(newName, newStrength) {}
		void display() const;
	};

	class Swordsman : public Warrior {
	public:
		Swordsman(const std::string& newName, double newStrength) : Warrior(newName, newStrength) {}
		void display() const;
	};
}







#endif
