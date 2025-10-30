#include "BorjaLib.h"

namespace vec {

	Vector4::Vector4(bool cartesian)
	{
		isCartesianBool = cartesian;
		isSphericalBool = !isCartesianBool;

		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	Vector4::Vector4(float x, float y, float z, float w, bool cartesian)
	{
		isCartesianBool = cartesian;
		isSphericalBool = !isCartesianBool;

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
}