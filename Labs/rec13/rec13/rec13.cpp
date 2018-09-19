// rec13_test.cpp

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <set>         // task 20
#include <map>         // task 22
#include <string>
using namespace std;

class Random {
public:
	Random(int x) : rval(x) {}
	bool operator()(int n) { return (n%rval) == 0; }
private:
	int rval = 0;
};

bool isEven(int n) { return n % 2 == 0; }

void listPrint(const list<int>& listInts) {
	for (list<int>::const_iterator iter = listInts.begin(); iter != listInts.end(); ++iter) {
		cout << *iter << " ";
	}
}

void listPrint2(const list<int>& listInts) {
	for (int ele : listInts) {
		cout << ele << " ";
	}
}

auto searchItem(const list<int>& listInts, int val) {
	for (auto iter = listInts.begin(); iter != listInts.end(); ++iter) {
		if (*iter == val) {
			return iter;
		}
	}
	return --(listInts.end());
}
template <typename T, typename U>
T ourFind(T start, T stop, U val) {
	for (T iter = start; iter != stop; iter++) {
		if (*iter == val) {
			return iter;
		}
	}
	return stop;
}
int main() {
	// 1. Create a vector with some values and display using ranged for
	cout << "Task 1:\n";
	vector<int> vecInts({ 5,3,1,2,4,6 });
	for (int ele : vecInts) {
		cout << ele << " ";
	}

	cout << "\n=======\n";

	// 2. Initalize a list as a copy of values from the vector
	cout << "Task 2:\n";
	list<int> listInts(vecInts.begin(), vecInts.end());
	for (int ele : listInts) {
		cout << ele << " ";
	}

	cout << "\n=======\n";

	// 3. Sort the original vector.  Display both the vector and the list
	cout << "Task 3:\n";
	sort(vecInts.begin(), vecInts.end());
	for (int ele : vecInts) {
		cout << ele << " ";
	}
	cout << endl;
	for (int ele : listInts) {
		cout << ele << " ";
	}
	cout << "\n=======\n";

	// 4. print every other element of the vector.
	cout << "Task 4:\n";
	for (size_t index = 0; index < vecInts.size(); ++(++index)) {
		cout << vecInts[index] << " ";
	}

	cout << "\n=======\n";

	// 5. Attempt to print every other element of the list using the
	//    same technique.
	cout << "Task 5:\n";
	/*
	for (size_t index = 0; index < listInts.size(); ++(++index)) {
		cout << listInts[index] << " ";
	}
	*/
	cout << "Does Not Compile";
	cout << "\n=======\n";

	//
	// Iterators
	//

	// 6. Repeat task 4 using iterators.  Do not use auto;
	cout << "Task 6:\n";
	for (vector<int>::iterator iter = vecInts.begin(); iter != vecInts.end(); ++ ++iter) {
		cout << *iter << " ";
	}

	cout << "\n=======\n";

	// 7. Repeat the previous task using the list.  Again, do not use auto.
	//    Note that you cannot use the same simple mechanism to bump
	//    the iterator as in task 6.
	cout << "Task 7:\n";
	for (list<int>::iterator iter = listInts.begin(); iter != listInts.end(); ++ ++iter) {
		cout << *iter << " ";
	}

	cout << "\n=======\n";

	// 8. Sorting a list
	cout << "Task 8:\n";
	listInts.sort();
	for (int ele : listInts) {
		cout << ele << " ";
	}
	cout << "\n=======\n";

	// 9. Calling the function to print the list
	cout << "Task 9:\n";

	listPrint(listInts);
	cout << endl;

	cout << "=======\n";

	// 10. Calling the function that prints the list, using ranged-for
	cout << "Task 10:\n";
	listPrint2(listInts);
	cout << endl;
	cout << "=======\n";

	//
	// Auto
	//

	// 11. Calling the function that, using auto, prints alterate
	// items in the list
	cout << "Task 11:\n";
	for (auto iter = listInts.begin(); iter != listInts.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;
	cout << "=======\n";


	// 12.  Write a function find that takes a list and value to search for.
	//      What should we return if not found
	cout << "Task 12:\n";
	list<int>::const_iterator pointer = searchItem(listInts, 5);
	cout << *pointer << " ";
	list<int>::const_iterator pointer2 = searchItem(listInts, 9);
	cout << *pointer2;
	cout << "\n=======\n";

	// 13.  Write a function find that takes a list and value to search for.
	//      What should we return if not found
	cout << "Task 13:\n";
	auto pointer3 = searchItem(listInts, 5);
	cout << *pointer << " ";
	auto pointer4 = searchItem(listInts, 9);
	cout << *pointer2;
	cout << "\n=======\n";

	//
// Generic Algorithms
//

// 14. Generic algorithms: find
cout << "Task 14:\n";
auto val1 = find(listInts.begin(), listInts.end(), 5);
cout << *val1 << " ";
auto val2 = find(listInts.begin(), listInts.end(), 9);
cout << *(--val2) << " ";
cout << "\n=======\n";

// 15. Generic algorithms: find_if
cout << "Task 15:\n";
auto val3 = find_if(listInts.begin(), listInts.end(), isEven);
cout << *val3;
cout << "\n=======\n";

// 16a. Functor
cout << "Task 16a:\n";
auto val4 = find_if(listInts.begin(), listInts.end(), Random(2));
cout << *val4;
cout << "\n=======\n";

// 16b. Lambda
cout << "Task 16b:\n";
auto val5 = find_if(listInts.begin(), listInts.end(), [](int n) {return (n % 2) == 0; });
cout << *val5;
cout << "\n=======\n";

// 17. Generic algorithms: copy to an array
cout << "Task 17:\n";
int arr[6];
copy(listInts.begin(), listInts.end(), arr);
for (size_t index = 0; index < 6; ++index) {
	cout << arr[index] << " ";
}
cout << endl;
auto val6 = find(arr, arr + 6, 5);
cout << *val6 << " ";
cout << endl;
auto val7 = find_if(arr, arr + 6, isEven);
cout << *val3;
cout << endl;
auto val8 = find_if(arr, arr + 6, Random(2));
cout << *val8;
cout << endl;
auto val9 = find_if(arr, arr + 6, [](int n) {return (n % 2) == 0; });
cout << *val9;
cout << "\n=======\n";

//
// Templated Functions
//

// 18. Implement find as a function for lists
cout << "Task 18:\n";
auto val10 = ourFind(listInts.begin(), listInts.end(), 3);
cout << *val10;
cout << "\n=======\n";

// 19. Implement find as a templated function
cout << "Task 20:\n";
auto val11 = ourFind(listInts.begin(), listInts.end(), 3);
cout << *val11;
cout << "\n=======\n";

//
// Associative collections
//

// 20. Using a vector of strings, print a line showing 
cout << "Task 21:\n";

vector<string> pooh;
ifstream f("pooh.txt");
if (!f) {
	cerr << "Failed";
	exit(1);
}

string word;
while (f >> word) {
	if (ourFind(pooh.begin(), pooh.end(), word) == pooh.end()) {
		pooh.push_back(word);
	}

}
cout << pooh.size();

cout << "\n=======\n";
f.close();
// 21. Repeating previous step, but using the set
cout << "Task 22:\n";
ifstream f2("pooh.txt");
if (!f2) {
	cerr << "Failed";
	exit(1);
}

set<string> pooh2;
string word2;
while (f2 >> word2) {
	if (find(pooh2.begin(), pooh2.end(), word2) == pooh2.end()) {
		pooh2.insert(word2);
	}
}
for (auto p = pooh2.begin(); p != pooh2.end(); ++p){
	cout << *p << " ";
}

cout << "\n=======\n";
f2.close();
// 22. Word co-occurence using map
cout << "Task 23:\n";
map<string, vector<int>> wordMap;
ifstream f3("pooh.txt");
if (!f3) {
	cerr << "Failed";
	exit(1);
}
string word3;
int counter = 0;
while (f3 >> word3) {
	wordMap[word3].push_back(counter);
	++counter;
}
for (auto pair : wordMap) {
	cout << pair.first << " " << "Positions:";
	for (size_t index = 0; index < pair.second.size(); ++index) {
		cout << pair.second[index] << " ";
	}
}
cout << "\n=======\n";
}
