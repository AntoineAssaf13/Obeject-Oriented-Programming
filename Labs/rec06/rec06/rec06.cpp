// rec06.cpp : Defines the entry point for the console application.
//Antoine Assaf aca432, Recitation 6: Creating a directory of employees by making the use of dynamic arrays and copy control

//#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;


class Position {
public:
	Position(const string& aTitle, double aSalary)
		: title(aTitle), salary(aSalary) {}
	const string& getTitle() const { return title; }
	double getSalary() const { return salary; }
	void changeSalaryTo(double d) { salary = d; }
	void display(ostream& os = cout) const {
		os << '[' << title << ',' << salary << ']';
	}
private:
	string title;
	double salary;
}; // class Position

class Entry {
public:
	Entry(const string& aName, unsigned aRoom, unsigned aPhone,
		Position& aPosition)
		: name(aName), room(aRoom), phone(aPhone), pos(&aPosition) {
	}
	void display(ostream& os = cout) const {
		os << name << ' ' << room << ' ' << phone << ", ";
		pos->display(os);
	}
	const string& getName() const { return name; }
	const unsigned& getPhone() const { return phone; }
private:
	string name;
	unsigned room;
	unsigned phone;
	Position* pos;
}; // class Entry

class Directory {
public:
	Directory() {}
	Directory(const Directory& rhs) {
		size = rhs.size;
		capacity = rhs.capacity;
		entries = new Entry*[capacity];
		for (size_t index = 0; index < size; index++) {
			entries[index] = new Entry(*rhs.entries[index]); //default copy constructor
		}
	}

	~Directory() {
		for (size_t index = 0; index < size; ++index) {
			delete entries[index];
		}
		delete[] entries;
	}


	Directory& operator=(const Directory& rhs){
		if (this != &rhs) {
			for (size_t index = 0; index < size; ++index) {
				delete entries[index];
			}
			delete[] entries;
			entries = new Entry*[rhs.capacity];
			size = rhs.size;
			capacity = rhs.capacity;
			for (size_t index = 0; index < size; index++) {
				entries[index] = new Entry(*rhs.entries[index]);
			}
			for (size_t index = size; index < capacity; index++) {
				entries[index] = nullptr;
			}
		}
		return *this;
	}

	unsigned operator[](const string& name) {
		for (size_t index = 0; index < size; ++index) {
			if (name == entries[index]->getName()) {
				return entries[index]->getPhone();
			}
		}
		return 0;
	}

	void add(const string& name, unsigned room, unsigned ph, Position& pos) {
		if (size == capacity) {
			if (entries == nullptr) {
				entries = new Entry*[1];
				capacity = 1;
			}
			else {
				Entry** oldEntries = entries;
				entries = new Entry*[2 * capacity];
				for (size_t index = 0; index < size; ++index) {
					entries[index] = oldEntries[index];
				}
				for (size_t index = size; index < capacity; index++) {
					entries[index] = nullptr;
				}
				delete[] oldEntries;
				capacity *= 2;
			}

		} // if
		entries[size] = new Entry(name, room, ph, pos);
		++size;
	} // add

	void display(ostream& os = cout) const {
		for (size_t i = 0; i < size; ++i) {
			entries[i]->display(os);
			os << endl;
		}
	}

private:
	Entry** entries = nullptr;
	size_t size = 0;
	size_t capacity = 0;
}; // class Directory

void doNothing(Directory dir) { dir.display(); }

int main() {

	// Note that the Postion objects are NOT on the heap.
	Position boss("Boss", 3141.59);
	Position pointyHair("Pointy Hair", 271.83);
	Position techie("Techie", 14142.13);
	Position peon("Peonissimo", 34.79);

	// Create a Directory
	Directory d;
	d.add("Marilyn", 123, 4567, boss);
	d.display();

	Directory d2 = d;	// What function is being used??
	d2.add("Gallagher", 111, 2222, techie);
	d2.add("Carmack", 314, 1592, techie);
	d2.display();

	cout << "Calling doNothing\n";
	doNothing(d2);
	cout << "Back from doNothing\n";

	Directory d3;
	d3 = d2;

	// Should display 1592
	cout << d2["Carmack"] << endl;

} // main


