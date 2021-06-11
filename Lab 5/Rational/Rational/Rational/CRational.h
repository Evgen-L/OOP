#pragma once
#include <iostream>

using namespace std;

class CRational
{
public:
	CRational() = default;
	CRational(int num, int denom);
	CRational(int value);

	CRational& operator+=(const CRational& rhs);
	CRational& operator-=(const CRational& rhs);
	CRational& operator*=(const CRational& rhs);
	CRational& operator/=(const CRational& rhs);
	
	CRational operator-() const;
	CRational operator+() const;

	int GetNumerator()const;
	int GetDenominator()const;
	double ToDouble()const;

	friend CRational operator+(const CRational & lhs, const CRational & rhs);
	friend CRational operator-(const CRational & lhs, const CRational & rhs);
	friend CRational operator*(const CRational & lhs, const CRational & rhs);
	friend CRational operator/(const CRational & lhs, const CRational & rhs);
	friend bool operator==(const CRational& lhs, const CRational& rhs);
	friend bool operator!=(const CRational& lhs, const CRational& rhs);
	friend bool operator>=(const CRational& lhs, const CRational& rhs);
	friend bool operator<=(const CRational& lhs, const CRational& rhs);
	friend bool operator<(const CRational& lhs, const CRational& rhs);
	friend bool operator>(const CRational& lhs, const CRational& rhs);
	friend ostream& operator<<(ostream& output, const CRational& rhs);
	friend istream& operator>>(istream& output,  CRational& rhs);
	

private:
	void Normalize();
	int m_numerator = 0;
	int m_denominator = 1;
};

