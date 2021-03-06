#include "CParallelepiped.h"

using namespace std;

CParallelepiped::CParallelepiped(double density, double width, double depth, double height)
	:  CBody("Parallelepiped", density)
	,  m_width(width)
	,  m_height(height)
	,  m_depth(depth)
{
}

double CParallelepiped::GetVolume() const
{
	return m_width * m_height * m_depth;
}

double CParallelepiped::GetWidth() 
{
	return m_width;
}

double CParallelepiped::GetHeight() 
{
	return m_height;
}

double CParallelepiped::GetDepth()
{
	return m_depth;
}

void CParallelepiped::AppendProperties(ostream& strm) const
{
	strm << "\twidth = " << m_width  << endl;
	strm << "\tdepth = " << m_depth << endl;
	strm << "\theight = " << m_height << endl;
}