#ifndef MISC_H
#define MISC_H
#include <cassert>

#define PI_CONST 3.14159265

/** class grouping most importatnt enumeration types - required by luabind
*/
class Enumerations {
public:
	enum ActionType {
		Moving,
		Shooting,
		ChangingWeapon,
		Dying,
		Reloading,
		Waiting
	};
	enum WeaponType {
		Chaingun,
		Railgun,
		RocketLuncher,
		Shotgun,
		WeaponSize
	};
};

/** 4 dimentional vector class
*/
struct Vector4d {
	double val[4];
	Vector4d(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0) {
		val[0] = x;
		val[1] = y;
		val[2] = z;
		val[3] = w;
	}
	Vector4d(const Vector4d &vect) {
		val[0] = vect.val[0];
		val[1] = vect.val[1];
		val[2] = vect.val[2];
		val[3] = vect.val[3];
	}

	double value(int i) {
		return val[i];
	}

	//liczy dot produkt wektrorów znolmalizowanych !!! zmieñ nazwê !!!
	double dot(Vector4d & b) {
		//		assert(this->lengthSquared() == 1.0 && b.lengthSquared() == 1.0); //TODO dodac tolerancje dla b³edów numerycznych
		return val[0] * b.val[0] + val[1] * b.val[1] + val[2] * b.val[2] + val[3] * b.val[3];
	};
	double length();
	double lengthSquared();
	void rotateZ(double arc, bool radian);
	Vector4d operator-(const Vector4d &q) {
		return Vector4d(val[0] - q.val[0], val[1] - q.val[1], val[2] - q.val[2], val[3] - q.val[3]);
	}
	Vector4d operator-=(const Vector4d &q) {
		val[0] -= q.val[0];
		val[1] -= q.val[1];
		val[2] -= q.val[2];
		val[3] -= q.val[3];
		return *this;
	}
	Vector4d operator+(const Vector4d &q) {
		return Vector4d(val[0] + q.val[0], val[1] + q.val[1], val[2] + q.val[2], val[3] + q.val[3]);
	}
	Vector4d operator+=(const Vector4d &q) {
		val[0] += q.val[0];
		val[1] += q.val[1];
		val[2] += q.val[2];
		val[3] += q.val[3];
		return *this;
	}
	Vector4d operator*(const double &q) {
		return Vector4d(val[0] * q, val[1] * q, val[2] * q, val[3] * q);
	}
	Vector4d operator*=(const double &q) {
		val[0] *= q;
		val[1] *= q;
		val[2] *= q;
		val[3] *= q;
		return *this;
	}
	Vector4d operator/(const double &q) {
		assert(q != 0.0);
		return Vector4d(val[0] / q, val[1] / q, val[2] / q, val[3] / q);
	}
	Vector4d operator/=(const double &q) {
		assert(q != 0.0);
		val[0] /= q;
		val[1] /= q;
		val[2] /= q;
		val[3] /= q;
		return *this;
	}
	Vector4d normal() {
		return (*this / this->length());
	}
	Vector4d normalize() {
		*this = (*this / this->length());
		return *this;
	}
	bool operator==(const Vector4d& q) const {
		return (val[0] == q.val[0]) && (val[1] == q.val[1]) && (val[2] == q.val[2]) && (val[3] == q.val[3]);
	}
	bool operator!=(const Vector4d& q) const {
		return (val[0] != q.val[0]) || (val[1] != q.val[1]) || (val[2] != q.val[2]) || (val[3] != q.val[3]);
	}
	bool operator<(const Vector4d& q) const {
		for (int i = 0; i < 4; i++) {
			if (val[i] < q.val[i]) {
				return true;
			}
			else if (val[i] > q.val[i]) {
				return false;
			}
		}
		return false;
	}
};

#endif //MISC_H