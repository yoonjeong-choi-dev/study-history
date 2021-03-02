#pragma once
/*
Camera.h
- ī�޶� Ŭ���� ���� : �������� ����
- ���� �ùķ��̼ǿ����� �������� ������ ������
- �������� ������ ���� �� ��� ����
*/

#include <windows.h>
#include <strstream>
#include <GL/glut.h>
#include "PointVector.h"

#define CAMERA_PI 3.14159265

class Camera {
public:
	Point3 eye;			// ������ǥ�� ����(�������� ��ġ)
	Vector3 u, v, n;	// ���� ��ǥ���� onb(orthonormal basis)
	float aspect, nearDist, farDist, viewAngle;	// gluPerspective�� �Ķ���͵� : ���� ��ȯ �� �̿�

	Camera();
	void setDefaultCamera();	// ī�޶� �ʱ�ȭ �Լ�
	void setModelViewMatrix();	// ���� ��ȯ�� ���� �� �� ��� ����
	
	// Roll,Pitch,Yaw�� ���� ȸ�� ��ȯ �Լ���
	void roll(float angle);
	void pitch(float angle);
	void yaw(float angle);

	// ����� �̵��� ���� �̵� ��ȯ �Լ�
	void slide(double du, double dv, double dn);

	// ���� ��ǥ�� ���� : ī�޶� ��ġ, ����, �����͸� �̿��Ͽ� �ʱ�ȭ
	void set(const Point3& eye, const Point3& look, Vector3& up);
	void set(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ);

	// gluPerspective�� �Ķ���� ���� : projection�� ���� ����Ʈ ����
	void setShape(float viewAngle, float aspect, float nearDist, float farDist);
	void setAspect(float aspect);
	void getShape(float& viewAngle, float& aspect, float& nearDist, float& farDist);
	
	// ���� ��ǥ�� ��ȸ�� : roll/pitch/yaw�� �����ϱ� ���� ��ƿ�Լ�
	// v1,v2 ���ͷ� �̷���� �����  angle ��ŭ ȸ��
	void rotateAxes(Vector3& v1, Vector3& v2, float angle);
};