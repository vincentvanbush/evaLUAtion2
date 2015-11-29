#include "evaLUAtion2.h"
#include "Misc.h"
#include <cmath>
/** returns vector length
*/
double Vector4d::length() {
	return sqrt(lengthSquared());
}
/** returns vector length squared
*/
double Vector4d::lengthSquared() {
	double value = val[0] * val[0] + val[1] * val[1] + val[2] * val[2] + val[3] * val[3];
	return value == 0.0 ? 0.00001 : value;	//TODO PS L porz¹dnie zabezpieczyc przed dzieleniem przez zero!
}

void Vector4d::rotateZ(double arc, bool radian) {
	if (!radian) {
		arc *= PI_CONST / 180.0;
	}
	double x = val[0] * cos(arc) - val[1] * sin(arc);
	double y = val[0] * sin(arc) + val[1] * cos(arc);
	val[0] = x;
	val[1] = y;
}