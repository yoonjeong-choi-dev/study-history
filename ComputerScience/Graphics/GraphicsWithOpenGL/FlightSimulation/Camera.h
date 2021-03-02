#pragma once
/*
Camera.h
- 카메라 클래스 정의 : 조종사의 시점
- 비행 시뮬레이션에서는 조종사의 시점만 움직임
- 조종사의 시점에 대한 뷰 행렬 정의
*/

#include <windows.h>
#include <strstream>
#include <GL/glut.h>
#include "PointVector.h"

#define CAMERA_PI 3.14159265

class Camera {
public:
	Point3 eye;			// 시점좌표계 원점(조종사의 위치)
	Vector3 u, v, n;	// 시점 좌표계의 onb(orthonormal basis)
	float aspect, nearDist, farDist, viewAngle;	// gluPerspective의 파라미터들 : 시점 변환 후 이용

	Camera();
	void setDefaultCamera();	// 카메라 초기화 함수
	void setModelViewMatrix();	// 시점 변환에 따른 모델 뷰 행렬 세팅
	
	// Roll,Pitch,Yaw를 위한 회전 변환 함수들
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);

	// 비행기 이동을 위한 이동 변환 함수
	void slide(double du, double dv, double dn);

	// 시점 좌표계 설정 : 카메라 위치, 초점, 업벡터를 이용하여 초기화
	void set(const Point3& eye, const Point3& look, Vector3& up);
	void set(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ);

	// gluPerspective의 파라미터 세팅 : projection을 위한 뷰포트 설정
	void setShape(float viewAngle, float aspect, float nearDist, float farDist);
	void setAspect(float aspect);
	void getShape(float& viewAngle, float& aspect, float& nearDist, float& farDist);
	
	// 시점 좌표계 축회전 : roll/pitch/yaw를 구현하기 위한 유틸함수
	// v1,v2 벡터로 이루어진 평면을  angle 만큼 회전
	void rotateAxes(Vector3& v1, Vector3& v2, float angle);
};