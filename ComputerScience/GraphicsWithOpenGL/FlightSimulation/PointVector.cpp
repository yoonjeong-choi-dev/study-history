#include "PointVector.h"

Point3::Point3(float xx, float yy, float zz) {
	x = xx; y = yy; z = zz;
}

void Point3::set(float dx, float dy, float dz) {
	x = dx; y = dy; z = dz;
}

void Point3::set(const Point3& p) {
	x = p.x; y = p.y; z = p.z;
}


Vector3::Vector3(float xx, float yy, float zz) {
	x = xx; y = yy; z = zz;
}

Vector3::Vector3(const Vector3& v) {
	x = v.x; y = v.y; z = v.z;
}

void Vector3::set(float dx, float dy, float dz) {
	x = dx; y = dy; z = dz;
}

void Vector3::set(const Vector3& v) {
	x = v.x; y = v.y; z = v.z;
}

void Vector3::flip() {
	x = -x; y = -y; z = -z;
}

void Vector3::setDiff(const Point3 &p1, const Point3& p2) {
	x = p1.x - p2.x;
	y = p1.y - p2.y;
	z = p1.z - p2.z;
}

void Vector3::normalize() {
	double l2Square = x*x + y*y + z*z;

	// MIN_FLOAT보다 작은 경우 정규화하지 않는다
	if (l2Square < MIN_FLOAT) {
		return;
	}

	// 정규화 : 나눗셈 연산을 최소화 하기위해 scaleFactor에 저장한다
	float scaleFactor = 1.0 / (float)sqrt(l2Square);
	x *= scaleFactor;
	y *= scaleFactor;
	z *= scaleFactor;
}

Vector3 Vector3::cross(const Vector3& v) {
	Vector3 ret(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	return ret;
}

float Vector3::dot(const Vector3& v) {
	return x*v.x + y*v.y + z*v.z;
}