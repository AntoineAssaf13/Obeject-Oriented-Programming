#ifndef REAL_H
#define _REAL_H
#pragma once
//#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

namespace CS2124{

	class Rational {
		friend std::istream& operator>>(std::istream& input, Rational& rationalNum);
		friend std::ostream& operator<<(std::ostream& output, const Rational& rationalNum);
		friend bool operator==(const Rational& lhs, const Rational& rhs);
	public:
		Rational() {}
		Rational(int prime) : numerator(prime), denominator(1) {
			if (prime < 0) {
				denominator = prime*-1;
			}
		}
		Rational& operator+=(const Rational& rhs);
		Rational& operator++();
		Rational operator++(int);
		explicit operator bool() const;
		void normalize();

	private:
		int numerator;
		int denominator;
	};
	int greatestCommonDivisor(int x, int y);
	Rational operator+(const Rational& lhs, const Rational& rhs);
	bool operator!=(const Rational& lhs, const Rational& rhs);
	Rational operator--(Rational& rational, int);
	Rational& operator--(Rational& rational);
}
#endif