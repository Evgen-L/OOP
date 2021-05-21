#pragma once
#include<string>

using namespace std;

class CBody
{
public:
	CBody(const string& type, double density);

	double GetDensity() const;
	virtual double GetVolume() const = 0;
	double GetMass() const;
	string ToString() const;

	virtual ~CBody();


private:
	virtual void AppendProperties(ostream& strm) const = 0;
	double m_density;
	string m_type;
};

