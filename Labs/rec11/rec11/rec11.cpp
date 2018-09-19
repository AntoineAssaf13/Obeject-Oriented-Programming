// rec11.cpp : Defines the entry point for the console application.
//Antoine Assaf: aca432.  Lab on linked lists

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

void listDisplay(Node* hp) {
	Node* p = hp;
	while (p != nullptr) {
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}

Node* listFindTail(Node* hp) {
	if (hp == nullptr) return nullptr;
	Node* p = hp;
	//while (p != nullptr && p->next != nullptr) {
	while (p->next != nullptr) {
		p = p->next;
	}
	return p;
}


void listAddTail(Node*& hp, int data) {
	//Node* nodeToAdd = new Node(data);
	Node* tail = listFindTail(hp);
	if (tail == nullptr) {
		hp = new Node(data);
	}
	else {
		tail->next = new Node(data);
	}
}

void listAddHead(Node*& hp, int data) {
	// // create a node for the data
	// Node* p = new Node(data);
	// // make our new node "point" to what was the first node
	// p->next = hp;

	// Node* p = new Node(data, hp);
	// // set our head pointer to the new node
	// hp = p;

	hp = new Node(data, hp);
}

void listInsertAfter(Node* prior, int data) {
	// create node
	// set new node to point to the node after prior
	// new Node(data, prior->next);
	// make prior node point to the new node
	prior->next = new Node(data, prior->next);
}

void listRemoveAfter(Node* prior) {
	Node* target = prior->next;
	// make prior node point to the one after the target
	prior->next = prior->next->next;
	// get rid of the target
	delete target;
}

Node* listCopy(Node* hp) {
	if (hp == nullptr) return nullptr;
	// Initialization code
	Node* result = new Node(hp->data);
	Node* lastAdded = result;
	Node* p = hp->next;

	while (p != nullptr) {
		lastAdded->next = new Node(p->data);
		lastAdded = lastAdded->next;
		p = p->next;
	}
	return result;
}

Node* listCopyV2(Node* hp) {
	if (hp == nullptr) return nullptr;
	return new Node(hp->data, listCopyV2(hp->next));
}

void listClear(Node*& hp) {
	if (hp == nullptr) return;
	while (hp->next != nullptr) {
		listRemoveAfter(hp);
	}
	delete hp;
	hp = nullptr;
}

void splice(Node* p, Node* hp) {
	Node* nextNode = p->next;
	Node* currentCopy = hp;
	while (currentCopy != nullptr) {
		p->next = currentCopy;
		p = p->next;
		currentCopy = currentCopy->next;
	}
	p->next = nextNode;
	
}
//1,2,3,4,5
//1,2
Node* subList(Node* hpOne, Node* hpTwo) {
	if (hpTwo == nullptr) {
		return hpOne;
	}
	while (hpOne != nullptr) {
		if (hpOne->data == hpTwo->data) {
			Node* pOne = hpOne->next;
			Node* pTwo = hpTwo->next;
			while ((pOne == nullptr && pTwo == nullptr) || pOne != nullptr) {
				if (pTwo == nullptr) {
					return hpOne;
				}
				else if (pOne->data != pTwo->data) {
					break;
				}
				pOne = pOne->next;
				pTwo = pTwo->next;
			}
		}
		hpOne = hpOne->next;
	}
	return nullptr;
}

int main()
{
	Node* myList = nullptr;
	myList = new Node(5);
	listAddTail(myList, 7);
	listAddTail(myList, 9);
	listAddTail(myList, 1);

	Node* myList2 = nullptr;
	myList2 = new Node(6);
	listAddTail(myList2, 3);
	listAddTail(myList2, 2);

	listDisplay(myList);
	listDisplay(myList2);
	
	splice(myList->next, myList2);

	listDisplay(myList);
	
	Node* myFinalList = nullptr;
	myFinalList = new Node(1);
	listAddTail(myFinalList, 2); listAddTail(myFinalList, 3); listAddTail(myFinalList, 2); listAddTail(myFinalList, 3); listAddTail(myFinalList, 2); listAddTail(myFinalList, 4); listAddTail(myFinalList, 5); listAddTail(myFinalList, 6);
	listDisplay(myFinalList);

	Node* testOne = nullptr;
	testOne = new Node(1);
	Node* testTwo = nullptr;
	testTwo = new Node(3);
	listAddTail(testTwo, 9);
	Node* testThree = new Node(2);
	listAddTail(testThree, 3);
	Node* testFour = new Node(5);
	listAddTail(testFour, 6); listAddTail(testFour, 7);


	cout << "TEST ONE" << endl;
	Node* sub = subList(myFinalList, testOne);
	listDisplay(sub);

	cout << "TEST TWO" << endl;
	sub = subList(myFinalList, testTwo);
	//listDisplay(sub);
	if (sub == nullptr) {
		cout << "IT IS NULLPTR" << endl;
	}

	cout << "TEST THREE" << endl;
	sub = subList(myFinalList, testThree);
	listDisplay(sub);

	cout << "TEST FOUR" << endl;
	sub = subList(myFinalList, testFour);
	if (sub == nullptr) {
		cout << "IT IS NULLPTR" << endl;
	}
}

