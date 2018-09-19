//#include "stdafx.h"
#include "polynomial.h"
#include <iostream>
#include <vector>
using namespace std;

namespace polynomialCraft {
	void listClear(Node*& hp) {
		if (hp == nullptr) return;
		while (hp->next != nullptr) {
			listRemoveAfter(hp);
		}
		delete hp;
		hp = nullptr;
	}
	void listRemoveAfter(Node*& prior) {
		Node* target = prior->next;
		//make prior node point to the one after the target
		prior->next = prior->next->next;
		//get rid of the target
		delete target;

	}

	int Polynomial::evaluate(int val) {
		if (degrees == 0) {
			return orderList->data;
		}
		int answer = 0;
		Node* selectedPos = orderList;
		vector<int> listOfNums;
		for (int index = 0; index < degrees+1; ++index) {
			listOfNums.push_back(selectedPos->data);
			selectedPos = selectedPos->next;
		}
		for (int index = degrees; index > 0; --index) {
			if (index != 1) {
				if (listOfNums[index] != 0) {
					int powVal = 1;
					for (int indexTwo = 0; indexTwo < index; ++indexTwo) {
						powVal *= val;
					}
					answer += listOfNums[index] * powVal;
				}
			}
			else if (index == 1) {
				if (listOfNums[index] != 0) {
					answer += listOfNums[index] * val;
				}
			}
		}
		answer += listOfNums[0];
		return answer;
	}

	Polynomial& Polynomial :: operator=(const Polynomial& rhs) {
		if (*this != rhs) {
			listClear(orderList);
			degrees = rhs.degrees;
			orderList = new Node(rhs.orderList->data);
			Node* selectedPosTwo = rhs.orderList->next;
			Node* selectedPosOne = orderList;
			while (selectedPosTwo != nullptr) {
				selectedPosOne->next = new Node(selectedPosTwo->data);
				selectedPosOne = selectedPosOne->next;
				selectedPosTwo = selectedPosTwo->next;
			}
		}
		return *this;
	}

	Polynomial& Polynomial :: operator+=(const Polynomial& rhs) {
		Node* selectedPosOne = orderList;
		Node* selectedPosTwo = rhs.orderList;
		if (this != &rhs) {
				for (int index = 0; index < degrees+1; ++index) {
					selectedPosOne->data += selectedPosTwo->data;
					if (selectedPosOne->next == nullptr || selectedPosTwo->next == nullptr) {
						break;
					}
					selectedPosOne = selectedPosOne->next;
					selectedPosTwo = selectedPosTwo->next;
				}
				if (rhs.degrees > degrees) {
					selectedPosTwo = selectedPosTwo->next;
					for (int index = degrees+1; index < rhs.degrees+1; ++index) {
						selectedPosOne->next = new Node(selectedPosTwo->data);
						selectedPosOne = selectedPosOne->next;
						selectedPosTwo = selectedPosTwo->next;
						degrees += 1;
					}
					degrees -= 1;
				}

			return *this;
		}
	}

	Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
		Polynomial newPoly = lhs;
		newPoly += rhs;
		return newPoly;
	}

	bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
		if (lhs.degrees != rhs.degrees) {
			return false;
		}
		Node* selectedPosOne = lhs.orderList;
		Node* selectedPosTwo = rhs.orderList;
		for (int index = 0; index < lhs.degrees+1; ++index) {
			if (selectedPosOne->data != selectedPosTwo->data) {
				return false;
			}
			selectedPosOne = selectedPosOne->next;
			selectedPosTwo = selectedPosTwo->next;
		}
		return true;
	}

	bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
		if (lhs == rhs) {
			return false;
		}
		return true;
	}
	ostream& operator<<(std::ostream& os, Polynomial& lhs) {
		int degrees = lhs.degrees;
		Node* selectedPos = lhs.orderList;
		vector<int> listOfNums;
		for (int index = 0; index < lhs.degrees + 1; ++index) {
			listOfNums.push_back(selectedPos->data);
			selectedPos = selectedPos->next;
		}
		for (int index = degrees; index > 0; --index) {
			if (index != 1) {
				os << listOfNums[index] << "x^" << degrees << " + ";
				degrees -= 1;
			}
			else if (index == 1) {
				os << listOfNums[index] << "x" << " + ";
			}
		}
		os << listOfNums[0] << endl;
		return os;
	}
}