#include "CRational.h"
#include <cmath>

const string DENOMINATOR_MUST_NATURAL = "denominator must be natural";
const string CANNOT_DEVIDE_BY_0 = "can\'t devide by 0";
const string INCORRECT_INPUT = "incorrect input.";

int CRational::GetNumerator() const 
{
	return m_numerator;
}

int CRational::GetDenominator() const 
{
	return m_denominator;
}

double CRational::ToDouble() const 
{
	return (double)m_numerator / (double)m_denominator;
}


int GetGreatestCommonDivisor(int numerator, int determinator) 
{
	while (numerator > 0 && determinator > 0)
	{
		if (numerator > determinator)
		{
			numerator %= determinator;
		}
		else 
		{
			determinator %= numerator;
		}
	}
	return abs(numerator + determinator);
}

void CRational::Normalize() 
{	
	int greatest—ommonDivisor = GetGreatestCommonDivisor(m_numerator, m_denominator);
	m_denominator /= greatest—ommonDivisor;
	m_numerator /= greatest—ommonDivisor;
}

CRational::CRational(int value)
	:m_numerator(value),
	m_denominator(1)
{

}

CRational::CRational(int numerator, int denominator)
{
	if (denominator <= 0)
	{
		throw invalid_argument(DENOMINATOR_MUST_NATURAL);
	}
	m_denominator = denominator;
	m_numerator = numerator;
	Normalize();
}


CRational CRational::operator+() const
{
	return *this;
}

CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}


CRational operator+(const CRational& lhs, const CRational& rhs)
{
	return CRational(lhs.m_numerator * rhs.m_denominator + rhs.m_numerator * lhs.m_denominator, lhs.m_denominator * rhs.m_denominator);
}

CRational operator-(const CRational& lhs, const CRational& rhs)
{
	return CRational(lhs.m_numerator * rhs.m_denominator - rhs.m_numerator * lhs.m_denominator, lhs.m_denominator * rhs.m_denominator);
}

CRational operator*(const CRational& lhs, const CRational& rhs)
{
	return CRational(lhs.m_numerator * rhs.m_numerator, lhs.m_denominator * rhs.m_denominator);
}

CRational operator/(const CRational& lhs, const CRational& rhs)
{
	if(rhs.m_numerator == 0)
		throw underflow_error(CANNOT_DEVIDE_BY_0);
	return CRational(lhs.m_numerator * rhs.m_denominator, lhs.m_denominator * rhs.m_numerator);
}

bool operator==(const CRational& lhs, const CRational& rhs)
{
	return (lhs.m_numerator == rhs.m_numerator && lhs.m_denominator == rhs.m_denominator);
}

bool operator!=(const CRational& lhs, const CRational& rhs)
{
	return !(lhs == rhs);
}

bool operator>(const CRational& lhs, const CRational& rhs)
{
	return (lhs.m_numerator * rhs.m_denominator > rhs.m_numerator * lhs.m_denominator);
}

bool operator<(const CRational& lhs, const CRational& rhs)
{
	return (lhs.m_numerator * rhs.m_denominator < rhs.m_numerator * lhs.m_denominator);
}

bool operator>=(const CRational& lhs, const CRational& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const CRational& lhs, const CRational& rhs)
{
	return !(lhs > rhs);
}

ostream& operator<<(ostream& output, const CRational& rhs)
{
	output << rhs.m_numerator << "/" << rhs.m_denominator;
	return output;
}

istream& operator>>(istream& input,  CRational& rhs)
{
	int numerator = -1;
	int denominator = -1;
	char symbol = '0';
	const char slash = '/';
	if (!input >> numerator)
	{
		cout << INCORRECT_INPUT;
		throw - 1;
	}
	if (!input >> symbol || symbol != slash)
	{
		cout << INCORRECT_INPUT;
		throw - 1;
	}
	if (!input >> denominator)
	{
		cout << INCORRECT_INPUT;
		throw - 1;
	}
	rhs = CRational(numerator, denominator);
	return input;
}

CRational&  CRational::operator+=(const CRational& rhs)
{
	*this = *this + rhs;
	return *this;
}

CRational& CRational::operator-=(const CRational& rhs)
{
	*this = *this - rhs;
	return *this;
}

CRational& CRational::operator*=(const CRational& rhs)
{
	*this = *this * rhs;
	return *this;
}

CRational& CRational::operator/=(const CRational& rhs)
{
	if (rhs.m_numerator == 0)
		throw underflow_error(CANNOT_DEVIDE_BY_0);
	*this = *this / rhs;
	return *this;
}