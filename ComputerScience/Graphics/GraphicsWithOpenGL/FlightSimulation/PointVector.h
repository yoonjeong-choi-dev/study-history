#pragma once
/*
PointVector.h
- 3차원의 점과 벡터에 대한 클래스 정의
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
	void flip();	// 반대 방향 벡터
	void setDiff(const Point3 &p1, const Point3& p2);	// p1-p2에 대한 벡터
	void normalize();
	Vector3 cross(const Vector3& v);	// 외적
	float dot(const Vector3& v);
};