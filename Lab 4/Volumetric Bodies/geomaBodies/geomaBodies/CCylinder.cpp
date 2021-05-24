#include "CCylinder.h"
#include <sstream>

const double PI = 3.141592653589793;

CCylinder::CCylinder(double density, double radius, double height)
	: CBody("Cylinder", density),
	m_radius(radius),
	m_height(height)
{}




double CCylinder::GetBaseRadius()
{
	return m_radius;
}

double CCylinder::GetHeight() 
{
	return m_height;
}

double CCylinder::GetVolume() const 
{
	return PI * pow(m_radius, 2) * m_height;
}

void CCylinder::AppendProperties(ostream& strm) const
{
	strm << "\tradius = " << m_radius << endl;
	strm << "\theight = " << m_height << endl;
}