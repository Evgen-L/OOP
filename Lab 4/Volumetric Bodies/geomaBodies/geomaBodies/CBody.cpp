#include "CBody.h"
#include <sstream>
#include <iomanip>   

CBody::CBody(const string& type, double density)
	:m_density(density)
	, m_type(type)
{
}

CBody::~CBody()
{
}

double CBody::GetDensity() const 
{
	return m_density;
}

double CBody::GetMass() const
{
	return GetVolume() * GetDensity();
}

string CBody::ToString()const 
{
	ostringstream strm;
	strm << m_type << ":" << endl << setprecision(10)
		<< "\tdensity = " << GetDensity() << endl
		<< "\tvolume =" << GetVolume() << endl
		<< "\tmass =" << GetMass() << endl;
	AppendProperties(strm);
	return strm.str();
}