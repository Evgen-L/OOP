#include "CCone.h"

const double PI = 3.141592653589793;

CCone::CCone(double density, double radius, double height)
	:CBody("Cone", density),
	m_radius(radius),
	m_height(height)
{
};

double CCone::GetBaseRadius()
{
	return m_radius;
}

double CCone::GetHeight()
{
	return m_height;
}

double CCone::GetVolume() const 
{
	return 1 / 3 * PI * pow(m_radius, 2) * m_height;
}

void CCone::AppendProperties(ostream& strm) const 
{
	strm << "\tradius = " << m_radius << endl;
	strm << "\theight = " << m_height << endl;
}