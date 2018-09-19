// rec10.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;


//------------------------------------//
class Instrument {
public:
	virtual void makeSound() const = 0;
	virtual void play() const = 0;
private:
};

void Instrument::makeSound() const {
	cout << "To make a sound...";
}
void Instrument::play() const {
	cout << "Default true sound... If you get this you done messed up" << endl;
}
//-------------------------------------//
class Brass : public Instrument {
public:
	Brass(unsigned newSize) : size(newSize) {}
	void makeSound() const {
		Instrument::makeSound();
		cout<< "Blow on a mouthpiece of size " << size << endl;
	}
private:
	unsigned size;
};

class Trombone : public Brass {
public:
	Trombone(unsigned size) : Brass(size) {}
	void play() const {
		cout << "Blat!" << endl;
	}
private:
};

class Trumpet : public Brass {
public:
	Trumpet(unsigned size) : Brass(size) {}
	void play() const {
		cout << "Toot!" << endl;
	}
private:
};
//------------------------------------//
class String : public Instrument {
public:
	String(unsigned newPitch) : pitch(newPitch) {}
	void makeSound() const {
		Instrument::makeSound();
		cout << "Bow a string of pitch " << pitch << endl;
	}
private:
	unsigned pitch;
};

class Violin : public String {
public:
	Violin(unsigned pitch) : String(pitch) {}
	void play() const {
		cout << "Screech!" << endl;
	}
private:
};

class Cello : public String {
public:
	Cello(unsigned pitch) : String(pitch) {}
	void play() const {
		cout << "Squawk!" << endl;
	}
private:
};
//------------------------------------//
class Percussion : public Instrument {
public:
	void makeSound() const {
		Instrument::makeSound();
		cout << "Hit me! "<<endl;
	}
private:
};

class Drum : public Percussion {
public:
	void play() const {
		cout << "Boom!" << endl;
	}
};

class Cymbal : public Percussion {
public:
	void play() const {
		cout << "Crash!" << endl;
	}
};
//------------------------------------//
class Musician {
public:
	Musician() : instr(nullptr) {}
	void acceptInstr(Instrument& i) { instr = &i; }
	Instrument* giveBackInstr() {
		Instrument* tmp(instr);
		instr = nullptr;
		return tmp;
	}
	void testPlay() const {
		if (instr)
			instr->makeSound();
		else
			cerr << "I have no Instruments!\n";
	}
	void realPlay() const {
		if (instr)
			instr->play();
		else
			cout << "silence..." << endl;
	}
private:
	Instrument* instr;
};
//------------------------------------//
class MILL {
public:
	void receiveInstr(Instrument& instr) {
		instr.makeSound();
		inventory.push_back(&instr);
	}
	void dailyTestPlay() const {
		cout << "DAILY TEST" << endl;
		for (size_t index = 0; index < inventory.size(); ++index) {
			inventory[index]->makeSound();
		}
	}
	Instrument* loanOut() {
		if (inventory.size() == 0) {
			cout << "No instrument available" << endl;
			return NULL;
		}
		Instrument* instrLoaned = inventory[0];
		for (int i = 0; i < inventory.size()-1; i++) {
			inventory[i] = inventory[i + 1];
		}
		inventory.pop_back();
		return instrLoaned;
	}
private:
	vector<Instrument*> inventory;
};

class Orch {
public:
	bool addPlayer(Musician& newMember) {
		if (musicians.size() == 25) {
			cout << "MAX AMOUNT EXCEEDED" << endl;
			return false;
		}
		musicians.push_back(&newMember);
		return true;
	}
	void play() const {
		for (size_t index = 0; index < musicians.size(); ++index) {
			musicians[index]->realPlay();
		}
	}
private:
	vector<Musician*> musicians;
};
//------------------------------------//
// PART ONE
int main() {

	// The initialization phase

	Drum drum;
	Cello cello(673);
	Cymbal cymbal;
	Trombone tbone(4);
	Trumpet trpt(12);
	Violin violin(567);

	MILL mill;
	mill.receiveInstr(trpt);
	mill.receiveInstr(violin);
	mill.receiveInstr(tbone);
	mill.receiveInstr(drum);
	mill.receiveInstr(cello);
	mill.receiveInstr(cymbal);

	Musician bob;
	Musician sue;
	Musician mary;
	Musician ralph;
	Musician jody;
	Musician morgan;
	
	Orch orch;



	// THE SCENARIO
	
	//Bob joins the orchestra without an instrument.
	orch.addPlayer(bob);
	
	//The orchestra performs
	cout << "orch performs\n";
	orch.play();
	
	//Sue gets an instrument from the MIL2 and joins the orchestra.
	sue.acceptInstr(*mill.loanOut());
	orch.addPlayer(sue);

	//Ralph gets an instrument from the MIL2.
	ralph.acceptInstr(*mill.loanOut());

	//Mary gets an instrument from the MIL2 and joins the orchestra.
	mary.acceptInstr(*mill.loanOut());
	orch.addPlayer(mary);

	//Ralph returns his instrument to the MIL2.
	mill.receiveInstr(*ralph.giveBackInstr());

	//Jody gets an instrument from the MIL2 and joins the orchestra.
	jody.acceptInstr(*mill.loanOut());
	orch.addPlayer(jody);

	// morgan gets an instrument from the MIL2
	morgan.acceptInstr(*mill.loanOut());

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Ralph joins the orchestra.
	orch.addPlayer(ralph);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	// bob gets an instrument from the MIL2
	bob.acceptInstr(*mill.loanOut());

	// ralph gets an instrument from the MIL2
	ralph.acceptInstr(*mill.loanOut());

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Morgan joins the orchestra.
	orch.addPlayer(morgan);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();
	
}

