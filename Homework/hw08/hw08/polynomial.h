#ifndef POLYNOMIAL_H
#define _POLYNOMIAL_H
#pragma once
//#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#pragma once

namespace polynomialCraft {
	struct Node {
		Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
		int data;
		Node* next;
	};

	void listRemoveAfter(Node*& prior);
	void listClear(Node*& hp);

	class Polynomial {
		friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
		friend std::ostream& operator<<(std::ostream& os, Polynomial& lhs);
	public:
		Polynomial(const std::vector<int>& newVec = { 0 }) {
			Node* selectedPos = orderList;
			for (size_t index = newVec.size(); index > 0; --index) {
				selectedPos->data = newVec[index-1];
				if (index != 1) {
					selectedPos->next = new Node();
					selectedPos = selectedPos->next;
				}
				else if (index == 1) {
					selectedPos->next == nullptr;
				}
				degrees += 1;
			}
			degrees -= 1;
		}
		Polynomial(const Polynomial& rhs) : degrees(rhs.degrees) {
			if (rhs.orderList == nullptr) {
				orderList = nullptr;
			}
			else {
				orderList = new Node(rhs.orderList->data);
				Node* selectedPosOne = orderList;
				Node* selectedPosTwo = rhs.orderList->next;
				while (selectedPosTwo != nullptr) {
					selectedPosOne->next = new Node(selectedPosTwo->data);
					selectedPosOne = selectedPosOne->next;
					selectedPosTwo = selectedPosTwo->next;
				}
			}
		}
		~Polynomial() { listClear(orderList); }
		Polynomial& operator+=(const Polynomial& rhs);
		Polynomial& operator=(const Polynomial& rhs);
		int evaluate(int val);

	private:
		Node* orderList = new Node();
		int degrees = 0;
	};

	bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
	Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

}



#endif

