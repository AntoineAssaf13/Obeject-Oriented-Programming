// rec12.cpp : Defines the entry point for the console application.
// Antoine Assaf: aca432 recitation 12
//#include "stdafx.h"
#include <cstdlib>
#include <iostream>
using namespace std;

class List {
	friend ostream& operator<<(ostream& os, const List& myList);
	struct Node {
		Node(int data = 0, Node* next = nullptr, Node* prior = nullptr) : data(data), next(next), prior(prior) {}
		int data;
		Node* next;
		Node* prior;
	};
public:
	List(){
		head->next = tail;
		tail->prior = head;
	}
	List(const List& rhs) {
		head->next = tail;
		tail->prior = head;
		mySize = rhs.mySize;
		Node* pointerOne = head;
		Node* pointerTwo = rhs.head;
		while (pointerTwo->next != rhs.tail) {
			Node* newNode = new Node(pointerTwo->next->data, tail, pointerOne);
			pointerOne->next->prior = newNode;
			pointerOne->next = newNode;
			pointerTwo = pointerTwo->next;
			pointerOne = pointerOne->next;
		}
	}
	~List() {
		this->clear();
		delete head;
		head = nullptr;
		delete tail;
		tail = nullptr;
	}

	List& operator=(const List& rhs) {
		this->clear();
		mySize = rhs.mySize;
		Node* pointerOne = head;
		Node* pointerTwo = rhs.head;
		while (pointerTwo->next != rhs.tail) {
			Node* newNode = new Node(pointerTwo->next->data, tail, pointerOne);
			pointerOne->next->prior = newNode;
			pointerOne->next = newNode;
			pointerTwo = pointerTwo->next;
			pointerOne = pointerOne->next;
		}
		return *this;
	}
	class iterator {
		friend class List;
		friend bool operator==(const iterator& lhs, const iterator& rhs) {
			return lhs.pointer == rhs.pointer;
		}
	public:
		iterator(Node* pointer = nullptr) : pointer(pointer) {}
		iterator(const iterator& rhs) : pointer(rhs.pointer) {}
		iterator& operator++() {
			pointer = pointer->next;
			return *this;
		}
		iterator& operator--() {
			pointer = pointer->prior;
			return *this;
		}
		int operator*() const { return pointer->data; }
	private:
		Node* pointer;
	};

	void push_back(int data) {
		if (mySize == 0) {
			Node* newNode = new Node(data, tail, head);
			head->next = newNode;
			tail->prior = newNode;
			mySize += 1;
		}
		else {
			Node* newNode = new Node(data, tail, tail->prior);
			tail->prior->next = newNode;
			tail->prior = newNode;
			mySize += 1;
		}
	}

	int size() const{
		return mySize;
	}

	int front() const {
		return head->next->data;
	}

	int back() const {
		return tail->prior->data;
	}

	void pop_back() {
		if (mySize == 0) {
			return;
		}
		Node* selectNode = tail->prior;
		Node* connection = selectNode->prior;
		connection->next = tail;
		tail->prior = connection;
		delete selectNode;
		selectNode = nullptr;
		mySize -= 1;
	}

	void push_front(int data) {
		if (mySize == 0) {
			Node* newNode = new Node(data, tail, head);
			head->next = newNode;
			tail->prior = newNode;
			mySize += 1;
		}
		else {
			Node* newNode = new Node(data, head->next, head);
			head->next = newNode;
			head->next->next->prior = newNode;
			mySize += 1;
		}
	}

	void pop_front() {
		if (mySize == 0) {
			return;
		}
		Node* selectNode = head->next;
		Node* connection = selectNode->next;
		connection->prior = head;
		head->next = connection;
		delete selectNode;
		selectNode = nullptr;
		mySize -= 1;

	}
	void clear() {
		if (mySize == 0) {
			return;
		}
		Node* pointer = head;
		while (mySize) {
			this->pop_back();
		}
	}

	iterator& insert(const iterator& iter, int data){
		Node* pointer = iter.pointer;
		Node* newNode = new Node(data, pointer, pointer->prior);
		pointer->prior->next = newNode;
		pointer->prior = newNode;
		iterator newIter(newNode);
		mySize += 1;
		return newIter;
	}

	iterator& erase(iterator& iter) {
		Node* selectPointer = iter.pointer;
		Node* connection = selectPointer->next;
		selectPointer->prior->next = selectPointer->next;
		selectPointer->next->prior = selectPointer->prior;
		delete selectPointer;
		selectPointer = nullptr;
		mySize -= 1;
		iterator newIter(connection);
		return newIter;
	}

	int& operator[](const int& i) {
		if (mySize == 0 || i > mySize - 1) {
			cerr << "Index out of range";
		}
		Node* pointer = head->next;
		for (int index = 0; index < i; ++index) {
			pointer = pointer->next;
		}
		return pointer->data;
	}
	iterator begin() { return iterator(head->next); }
	iterator end() { return iterator(tail); }
	iterator begin() const { return iterator(head->next); }
	iterator end() const { return iterator(tail); }
private:
	int mySize = 0;
	Node* head = new Node();
	Node* tail = new Node();
};

bool operator!=(const List::iterator& lhs, const List::iterator& rhs) {
	if (lhs == rhs) {
		return false;
	}
	else {
		return true;
	}
}

void printListInfo(List& myList) {
	cout << "size: " << myList.size()
		<< ", front: " << myList.front()
		<< ", back(): " << myList.back()
		<< ", list: " << myList << endl;
}

ostream& operator<<(ostream& os, const List& myList) {
	List::Node* pointer = myList.head;
	os << "[ ";
	while (pointer->next != myList.tail){
		os << pointer->next->data << " ";
		pointer = pointer->next;
	}
	os << "]";
	return os;
}


// Task 8
void doNothing(List aList) {
	cout << "In doNothing\n";
	printListInfo(aList);
	cout << endl;
	cout << "Leaving doNothing\n";
}

int main() {

	// Task 1
	cout << "\n------Task One------\n";
	List myList;
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	
	for (int i = 0; i < 10; ++i) {
		cout << "myList.push_back(" << i*i << ");\n";
		myList.push_back(i*i);
		
		printListInfo(myList);
	}

	cout << "===================\n";
	cout << "Remove the items with pop_back\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_back();
	}
	cout << "===================\n";
	
	// Task2
	cout << "\n------Task Two------\n";
	cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList2.push_front(" << i*i << ");\n";
		myList.push_front(i*i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_front\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_front();
	}
	cout << "===================\n";
	
	// Task3
	cout << "\n------Task Three------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		myList.push_back(i*i);
	}
	printListInfo(myList);
	cout << "Now clear\n";
	myList.clear();
	cout << "Size: " << myList.size() << ", list: " << myList << endl;
	cout << "===================\n";
	
	// Task4
	cout << "\n------Task Four------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
	cout << "Display elements with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Add one to each element with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
	cout << "And print it out again with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	
	// Task 5
	cout << "\n------Task Five------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
	printListInfo(myList);
	cout << "Now display the elements in a ranged for\n";
	for (int x : myList) cout << x << ' ';
	cout << endl;
	cout << "And again using the iterator type directly:\n";
	for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << endl;
	cout << "WOW!!! (I thought it was cool.)\n";
	
	// Task 6
	cout << "\n------Task Six------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
	printListInfo(myList);
	cout << "Filling an empty list with insert at begin(): "
		<< "i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
	printListInfo(myList);
	// ***Need test for insert other than begin/end***
	cout << "===================\n";
	
	// Task 7
	cout << "\n------Task Seven------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
	cout << "Erasing the elements in the list, starting from the beginning\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.erase(myList.begin());
	}
	// ***Need test for erase other than begin/end***
	cout << "===================\n";

	// Task 8
	cout << "\n------Task Eight------\n";
	cout << "Copy control\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
	printListInfo(myList);
	
	cout << "Calling doNothing(myList)\n";
	doNothing(myList);
	cout << "Back from doNothing(myList)\n";
	printListInfo(myList);
	cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
	List listTwo;
	for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
	printListInfo(listTwo);
	cout << "listTwo = myList\n";
	listTwo = myList;
	cout << "myList: ";
	printListInfo(myList);
	cout << "listTwo: ";
	printListInfo(listTwo);
	cout << "===================\n";
	
}


