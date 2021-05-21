#pragma once
#include <iostream>
#include "../geomaBodies/CBody.h"

using namespace std;

class CSphere final : public CBody
{
public:
	CSphere(double density, double radius);

	double GetRadius() const;
	double GetVolume() const override;

private:
	void AppendProperties(ostream& strm) const override;
	double m_radius;
};

