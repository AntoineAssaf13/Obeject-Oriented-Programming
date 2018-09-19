// rec05.cpp : Defines the entry point for the console application.
// Antoine Assaf, aca432: Recitation 5: creating a grade/instructor recording program

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Section {
public:
	Section(const string& newName, const string& newDay, int newTime) : labName(newName), labTime(newDay, newTime) {}
	Section(const Section& rhs) : labTime(rhs.labTime), labName(rhs.labName){
		for (size_t index = 0; index < rhs.records.size(); index++) {
			Studentrecord* copyVal = new Studentrecord(*rhs.records[index]);
			records.push_back(copyVal);
		}
	}
	~Section() {
		cout << "Section " << labName << " is being deleted." << endl;
		for (size_t index = 0; index < records.size(); index++) {
			cout << "Deleting " << records[index]->getName() << endl;
			delete records[index];
		}
	}
	void addStudent(const string& studentName) {
		Studentrecord* newStudent = new Studentrecord (studentName);
		records.push_back(newStudent);
	}
	void display() const {
		cout << "Section: " << labName << ", " << "Time slot: ";
		labTime.display();
		if (records.size() == 0) {
			cout << "None" << endl;
			return;
		}
		for (size_t index = 0; index < records.size(); index++) {
			records[index]->display();
		}

	}
	void searchToGrade(const string& studentName, int grade, int week){
		for (int index = 0; index < records.size(); index++) {
			if (records[index]->getName() == studentName) {
				records[index]->modifyGrade(grade, week);
				return;
			}
		}
		cout << "Student does not exist" << endl;
	}

private:

	class Timeslot {
	public:
		Timeslot(const string& newDay, int newTime) : day(newDay), time(newTime) {}
		void display() const{
			if (time > 12) {
				cout << "[" << day << ", " << "Start time: " << time - 12 << "pm], Students:" << endl;
			}
			else {
				cout << "[" << day << ", " << "Start time: " << time << "am], Students:" << endl;
			}
		}
	private:
		string day;
		int time;
	};

	class Studentrecord {
	public:
		Studentrecord(const string& newStudentName) : studentName(newStudentName), studentRecord(14,-1){}
		void display() const {
			cout << "Name: " << studentName << ", Grades: ";
			for (size_t index = 0; index < studentRecord.size(); index++) {
				cout << studentRecord[index] << " ";
			}
			cout << endl;
		}
		string getName(){
			return studentName;
		}
		void modifyGrade(int grade, int week){
			studentRecord[week - 1] = grade;
		}
	private:
		string studentName;
		vector <int> studentRecord;
	};

	string labName;
	Timeslot labTime;
	vector <Studentrecord*> records;

};

class LabWorker {
public:
	LabWorker(const string& newName) : workerName(newName), workerSection(nullptr) {}
	void addSection(Section& newSection) {
		if (workerSection != nullptr) {
			cout << workerName << " already has a section!";
		}
		else {
			workerSection = &newSection;
		}
	}
	void addGrade(const string& studentName, int grade, int week) {
		workerSection->searchToGrade(studentName, grade, week);
	}
	void display() const {
		if (workerSection == nullptr) {
			cout << workerName << " does not have a section" << endl;
		}
		else {
			cout << workerName << " has ";
			workerSection->display();
		}
	}
private:
	string workerName;
	Section* workerSection;
};

// Test code
void doNothing(Section sec) { sec.display(); }

int main()
{
	cout << "Test 1: Defining a section\n";
	Section secA2("A2", "Tuesday", 16);
	secA2.display();
	
	cout << "\nTest 2: Adding students to a section\n";
	secA2.addStudent("John");
	secA2.addStudent("George");
	secA2.addStudent("Paul");
	secA2.addStudent("Ringo");
	secA2.display();
	
	cout << "\nTest 3: Defining a lab worker.\n";
	LabWorker moe("Moe");
	moe.display();

	cout << "\nTest 4: Adding a section to a lab worker.\n";
	moe.addSection(secA2);
	moe.display();

	cout << "\nTest 5: Adding a second section and lab worker.\n";
	LabWorker jane("Jane");
	Section secB3("B3", "Thursday", 11);
	secB3.addStudent("Thorin");
	secB3.addStudent("Dwalin");
	secB3.addStudent("Balin");
	secB3.addStudent("Kili");
	secB3.addStudent("Fili");
	secB3.addStudent("Dori");
	secB3.addStudent("Nori");
	secB3.addStudent("Ori");
	secB3.addStudent("Oin");
	secB3.addStudent("Gloin");
	secB3.addStudent("Bifur");
	secB3.addStudent("Bofur");
	secB3.addStudent("Bombur");
	jane.addSection(secB3);
	jane.display();

	cout << "\nTest 6: Adding some grades for week one\n";
	moe.addGrade("John", 17, 1);
	moe.addGrade("Paul", 19, 1);
	moe.addGrade("George", 16, 1);
	moe.addGrade("Ringo", 7, 1);
	moe.display();

	cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
	moe.addGrade("John", 15, 3);
	moe.addGrade("Paul", 20, 3);
	moe.addGrade("Ringo", 0, 3);
	moe.addGrade("George", 16, 3);
	moe.display();

	cout << "\nTest 8: We're done (almost)! \nWhat should happen to all those students (or rather their records?)\n";
	
	cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, then make sure the following call works\n";
	doNothing(secA2);
	cout << "Back from doNothing\n\n";
	
}

