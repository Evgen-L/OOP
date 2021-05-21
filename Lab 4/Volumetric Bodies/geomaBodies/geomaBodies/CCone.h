#pragma once
#include <iostream>
#include "../geomaBodies/CBody.h"

class CCone final : CBody
{
public:
	CCone(double density, double radius, double height);

	double GetBaseRadius();
	double GetHeight();
	double GetVolume() const override;

private:
	void AppendProperties(ostream& strm) const override;
	double m_radius;
	double m_height;
};

