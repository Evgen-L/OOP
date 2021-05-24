#pragma once
#include <iostream>
#include "../geomaBodies/CBody.h"

class CParallelepiped final : public CBody
{
public:
	CParallelepiped(double density, double width, double depth, double height);
	double GetVolume() const override;
	double GetWidth();
	double GetHeight();
	double GetDepth();

private:
	void AppendProperties(ostream& strm) const override;
	double m_width;
	double m_height;
	double m_depth;
};