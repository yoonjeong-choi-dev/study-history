#include "Camera.h"


Camera::Camera() {
	setDefaultCamera();
}
// �⺻�� �ʱ�ȭ
void Camera::setDefaultCamera() {
	// ���� ��� ����
	setShape(45.0f, 640 / (float)480, 0.1f, 200.0f);

	// ī�޶� ��ġ
	Point3 eyePoint = Point3(10.0, 0.0, 0.0);

	// ���� ��ġ
	Point3 lookPoint = Point3(0.0, 0.0, 0.0);

	// ī�޶� ������
	Vector3 upVector = Vector3(0.0f, 1.0f, 0.0f);

	// ���� ��ǥ�� ����
	set(eyePoint, lookPoint, upVector);
}

// ���� ��ǥ�� ����
void Camera::set(const Point3& eye, const Point3& look, Vector3& up) {	
	// ī�޶� ��ġ ����
	this->eye.set(eye);

	// n�� : ī�޶� ��ġ - ����
	this->n.set(this->eye.x - look.x, this->eye.y - look.y, this->eye.z - look.z);

	// u�� : ī�޶� �� ���Ϳ� n���� ����
	this->u.set(up.cross(this->n));

	// v�� : n���Ϳ� u���� ����
	this->v.set(this->n.cross(this->u));
	
	// (n,u,v) ����ȭ
	this->n.normalize();
	this->u.normalize();
	this->v.normalize();

	// �𵨺� ��� ������Ʈ
	setModelViewMatrix();
}

void Camera::set(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ) {
	Point3 eyePoint = Point3(eyeX, eyeY, eyeZ);
	Point3 look = Point3(lookX, lookY, lookZ);
	Vector3 up = Vector3(upX, upY, upZ);

	set(eyePoint, look, up);
}


// ���� ����� ������ �𵨺���Ŀ� ����
void Camera::setModelViewMatrix() {
	float m[16];

	//ī�޶� ��ġ ���� : ȸ�� ��ȯ�� ���
	Vector3 eyeVec(eye.x, eye.y, eye.z);
									  
	// �𵨺������ ȸ����ȯ�� �̵���ȯ���� : M = T*R - p633 (11.29) ���� ���
	m[0] = u.x;	m[4] = u.y;	m[8] = u.z;	m[12] = -eyeVec.dot(u);
	m[1] = v.x;	m[5] = v.y;	m[9] = v.z;	m[13] = -eyeVec.dot(v);
	m[2] = n.x;	m[6] = n.y;	m[10] = n.z;m[14] = -eyeVec.dot(n);
	m[3] = 0;	m[7] = 0;	m[11] = 0;	m[15] = 1.0;

	// GL �𵨺� ���������ο��� �𵨺� ��� ����
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}

void Camera::setShape(float viewAngle, float aspect, float nearDist, float farDist) {
	this->viewAngle = viewAngle;	// �þ߰�
	this->aspect = aspect;			// ��Ⱦ��
	this->nearDist = nearDist;		// ���������
	this->farDist = farDist;		// �Ĺ������

	// GL Projection ���������� ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(this->viewAngle, this->aspect, this->nearDist, this->farDist);

	//glMatrixMode(GL_MODELVIEW);
}

void Camera::setAspect(float aspect) {
	this->aspect = aspect;			// ��Ⱦ��
}

void Camera::getShape(float& viewAngle, float& aspect, float& nearDist, float& farDist) {
	viewAngle = this->viewAngle;
	aspect = this->aspect;			
	nearDist = this->nearDist;		
	farDist = this->farDist;		
}

// ����Ⱑ (du, dv, dn)��ŭ �̵� �� �𵨺� ��� ������Ʈ
// i.e ������ǥ�谡 ���� ��ǥ�� ������ �̵�
void Camera::slide(double du, double dv, double dn) {
	// eye = eye + [u|v|n]*[du,dv,dn]^T
	eye.x += du*u.x + dv*v.x + dn*n.x;
	eye.y += du*u.y + dv*v.y + dn*n.y;
	eye.z += du*u.z + dv*v.z + dn*n.z;
	setModelViewMatrix();	// �𵨺� ��� ������Ʈ
}

// (v1,v2)�� ���ؼ� ȸ����ȯ 
// i.e v1 <- cos*v1 + sin*v2, v2 <- -sin*v1 + cos*v2
void Camera::rotateAxes(Vector3& v1, Vector3& v2, float angle) {
	float rad = CAMERA_PI / 180 * angle;
	float c = cos(rad);
	float s = sin(rad);

	// v1,v2�� ���ÿ� ������Ʈ�ϱ� ���� �ӽ� ����
	Vector3 temp(c*v1.x + s*v2.x, c*v1.y + s*v2.y, c*v1.z + s*v2.z);	
	v2.set(-s*v1.x + c*v2.x, -s*v1.y + c*v2.y, -s*v1.z + c*v2.z);
	v1.set(temp);
}

void Camera::roll(float angle) {
	// u,v �࿡ ���� ȸ��
	rotateAxes(u, v, angle);
	setModelViewMatrix();	// �𵨺� ��� ������Ʈ
}
void Camera::pitch(float angle) {
	// n,v �࿡ ���� ȸ��
	rotateAxes(n, v, angle);
	setModelViewMatrix();	// �𵨺� ��� ������Ʈ
}
void Camera::yaw(float angle) {
	// u,n �࿡ ���� ȸ��
	rotateAxes(u, n, angle);
	setModelViewMatrix();	// �𵨺� ��� ������Ʈ
}