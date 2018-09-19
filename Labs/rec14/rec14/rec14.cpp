// rec14.cpp : Defines the entry point for the console application.
//aca432: Rec14 Antoine Assaf

//#include "stdafx.h"
#include <iostream>
#include <climits>
using namespace std;


struct Node{
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};
//? turnary operator 1

//tas 1
bool evenOnes(int n){
	return n == 0 ? 1 : (n & 1) ^ evenOnes(n >> 1);
}

//task 2
Node* listSum(Node* hp1, Node* hp2, Node* nhp = new Node()) {
	if (hp1->next == nullptr, hp2->next == nullptr) {
		nhp->data = (hp1->data + hp2->data);
		return nhp;
	}
	nhp->data = (hp1->data + hp2->data);
	nhp->next = listSum(hp1->next, hp2->next);
	return nhp;

}

//task 3

struct TNode {
	TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
		: data(data), left(left), right(right) {}
	int data;
	TNode *left, *right;
};

int max(TNode* root) {
	if (root==nullptr) {
		return INT_MIN;
	}
	int result = root->data;
	int rresult = max(root->right);
	int lresult = max(root->left);

	if (result < lresult) {
		result = lresult;
	}
	if (result < rresult) {
		result = rresult;
	}
	return result;

}

//task 4

bool palindrome(char* s, int size) {
	if (size <= 1) {
		return true;
	}
	if (*(s + size-1) == *s) {
		return palindrome((s + 1), (size - 2));
	}
	else {
		return false;
	}
}

//task 5

int towers(int n, char start, char helper, char target) {
	if (n == 0) return 0;
	return 1 + towers(n - 1, start, target, helper) + towers(n - 1, helper, start, target);
}

//task 6
void faaa(int n) {
	if (n > 1) {
		cout << 'a';
		faaa(n / 2);
		cout << 'b';
		faaa(n / 2);
	}
	cout << 'c';
}

int main() {
	cout << evenOnes(7) << endl;


	TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
	cout << max(&f) << endl;

	char s[] = "racecar";
	cout << palindrome(s, 7) << endl;

	cout << towers(8, 'A', 'B', 'C') << endl;
	faaa(3);

}




