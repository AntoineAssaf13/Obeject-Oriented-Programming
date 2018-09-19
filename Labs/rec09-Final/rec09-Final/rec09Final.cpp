// rec09Final.cpp : Defines the entry point for the console application.
//Antoine Assaf aca432 rec09: Intro to inheritance

//#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial(unsigned numPages)
		: numOfPages(numPages)
	{}
	virtual void displayNumPages() const = 0;
protected:
private:
	unsigned numOfPages;
};
void PrintedMaterial::displayNumPages() const{
	cout << numOfPages;
}
class Magazine : public PrintedMaterial {
public:
	Magazine(unsigned numPages)
		: PrintedMaterial(numPages)
	{}
	void displayNumPages() const {
		cout << "Magazine Pages: ";
		PrintedMaterial::displayNumPages();
		cout << endl;
	}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book(unsigned numPages)
		: PrintedMaterial(numPages)
	{}
	void displayNumPages() const {
		cout << "Book Pages: ";
		PrintedMaterial::displayNumPages();
		cout << endl;
	}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook(unsigned numPages, unsigned numIndxPgs)
		: Book(numPages),
		numOfIndexPages(numIndxPgs)
	{}
	void displayNumPages() const
	{
		cout << "TextBook: " << endl;
		cout << "Pages: ";
		PrintedMaterial::displayNumPages(); //This will give you num of pages through public
		cout << endl;
		cout << "Index pages: ";
		cout << numOfIndexPages << endl;
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel(unsigned numPages)
		: Book(numPages)
	{}
	void displayNumPages() const {
		cout << "Novel ";
		PrintedMaterial::displayNumPages();
		cout << endl;
	}
protected:
private:
};
/*
void displayNumberOfPages(const PrintedMaterial& anyPM) {
	anyPM.displayNumPages();
}
*/
// tester/modeler code
int main()
{
	TextBook t(5430, 234);
	Novel n(213);
	Magazine m(6);

	t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();

	//PrintedMaterial pm = t; // THIS WILL MAKE A COPY AND HENCE pm WILL BE TREATED AS A PrintedMaterial and not a textbook
	//pm.displayNumPages(); ABSTRACT CLASS

	PrintedMaterial* pmPtr;
	pmPtr = &t; //This still will not work because by dereferncing a PrintedMaterial, you will get a PrintedMaterial object: UNLESS YOU MAKE DISPLAY VIRTUAL
	pmPtr->displayNumPages();

	vector <PrintedMaterial*> allStuff;
	allStuff.push_back(&t);
	allStuff.push_back(&n);
	allStuff.push_back(&m);
	for (size_t index = 0; index < allStuff.size(); ++index) {
		allStuff[index]->displayNumPages();
	}
}

