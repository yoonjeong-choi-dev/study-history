#pragma once
/*
PointVector.h
- 3������ ���� ���Ϳ� ���� Ŭ���� ����
*/

#include <math.h>

#define MIN_FLOAT 0.0000001

class Point3 {
public:
	float x, y, z;

	Point3(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f);
	void set(float dx, float dy, float dz);
	void set(const Point3& p);
};

class Vector3 {
public:
	float x, y, z;
	Vector3(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f);
	Vector3(const Vector3& v);
	void set(float dx, float dy, float dz);
	void set(const Vector3& v);
	void flip();	// �ݴ� ���� ����
	void setDiff(const Point3 &p1, const Point3& p2);	// p1-p2�� ���� ����
	void normalize();
	Vector3 cross(const Vector3& v);	// ����
	float dot(const Vector3& v);
};