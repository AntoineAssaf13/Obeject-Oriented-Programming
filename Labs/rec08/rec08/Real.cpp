//#include "stdafx.h"
#include <string>
#include <iostream>
#include "Real.h"
using namespace std;

namespace CS2124 {

	int greatestCommonDivisor(int x, int y);
	Rational& Rational :: operator+=(const Rational& rhs) {
		int oldDenom = denominator;
		numerator *= rhs.denominator;
		denominator *= rhs.denominator;

		numerator += (rhs.numerator*oldDenom);
		normalize();
		return *this;
	}
	Rational& Rational :: operator++() {
		numerator += denominator;
		return *this;
	}
	Rational Rational :: operator++(int) {
		Rational oldRational = *this;
		numerator += denominator;
		return oldRational;
	}

	Rational :: operator bool() const {
		if (numerator == 0) {
			return false;
		}
		return true;
	}

	void Rational::normalize() {
		int divisor = greatestCommonDivisor(numerator, denominator);
		numerator = numerator / divisor;
		denominator = denominator / divisor;

	}

	int greatestCommonDivisor(int x, int y) {
		while (y != 0) {
			int temp = x % y;
			x = y;
			y = temp;
		}
		return x;
	}
	istream& operator>>(istream& input, Rational& rationalNum) {
		int num;
		char slash;
		int denom;
		input >> num >> slash >> denom;
		rationalNum.numerator = num;
		rationalNum.denominator = denom;
		rationalNum.normalize();
		return input;

	}

	ostream& operator<<(ostream& output, const Rational& rationalNum) {
		output << rationalNum.numerator << '/' << rationalNum.denominator << endl;
		return output;
	}

	Rational operator+(const Rational& lhs, const Rational& rhs) {
		Rational newRational = lhs;
		newRational += rhs;
		newRational.normalize();
		return newRational;

	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		if (lhs.numerator == rhs.numerator) {
			if (lhs.denominator == rhs.denominator) {
				return true;
			}
		}
		return false;
	}

	bool operator!=(const Rational& lhs, const Rational& rhs) {
		if (lhs == rhs) {
			return false;
		}
		return true;
	}

	Rational operator--(Rational& rational, int) {
		Rational rationalCopy = rational;
		rational += -1;
		return rationalCopy;
	}

	Rational& operator--(Rational& rational) {
		rational += -1;
		return rational;
	}
}
