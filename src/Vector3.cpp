#include "BorjaLib.h"

namespace vec {

	Vector3::Vector3(bool cartesian)
	{
		isCartesianBool = cartesian;
		isSphericalBool = !isCartesianBool;

		x = 0;
		y = 0;
		z = 0;
	}

	Vector3::Vector3(float x, float y, float z, bool cartesian)
	{
		isCartesianBool = cartesian;
		isSphericalBool = !isCartesianBool;

		this->x = x;
		this->y = y;
		this->z = z;
	}
}