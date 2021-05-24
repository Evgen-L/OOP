#include "CSphere.h"


const double PI = 3.141592653589793;

CSphere::CSphere(double density, double radius)
	: CBody("Sphere", density)
	, m_radius(radius) 
{

}

double CSphere::GetRadius()const
{
	return m_radius;
}

double CSphere::GetVolume()const
{
	return (pow(m_radius, 3) * PI) * 4 / 3;
}

void CSphere::AppendProperties(ostream& strm) const
{
	strm << "\tradius = " << m_radius << endl;
}