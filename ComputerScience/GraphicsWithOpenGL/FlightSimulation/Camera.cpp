#include "Camera.h"


Camera::Camera() {
	setDefaultCamera();
}
// 기본값 초기화
void Camera::setDefaultCamera() {
	// 투상 행렬 설정
	setShape(45.0f, 640 / (float)480, 0.1f, 200.0f);

	// 카메라 위치
	Point3 eyePoint = Point3(10.0, 0.0, 0.0);

	// 초점 위치
	Point3 lookPoint = Point3(0.0, 0.0, 0.0);

	// 카메라 업벡터
	Vector3 upVector = Vector3(0.0f, 1.0f, 0.0f);

	// 시점 좌표계 설정
	set(eyePoint, lookPoint, upVector);
}

// 시점 좌표계 설정
void Camera::set(const Point3& eye, const Point3& look, Vector3& up) {	
	// 카메라 위치 정의
	this->eye.set(eye);

	// n축 : 카메라 위치 - 초점
	this->n.set(this->eye.x - look.x, this->eye.y - look.y, this->eye.z - look.z);

	// u축 : 카메라 업 벡터와 n벡터 외적
	this->u.set(up.cross(this->n));

	// v축 : n벡터와 u벡터 외적
	this->v.set(this->n.cross(this->u));
	
	// (n,u,v) 정규화
	this->n.normalize();
	this->u.normalize();
	this->v.normalize();

	// 모델뷰 행렬 업데이트
	setModelViewMatrix();
}

void Camera::set(float eyeX, float eyeY, float eyeZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ) {
	Point3 eyePoint = Point3(eyeX, eyeY, eyeZ);
	Point3 look = Point3(lookX, lookY, lookZ);
	Vector3 up = Vector3(upX, upY, upZ);

	set(eyePoint, look, up);
}


// 현재 비행기 정보를 모델뷰행렬에 적용
void Camera::setModelViewMatrix() {
	float m[16];

	//카메라 위치 벡터 : 회전 변환에 사용
	Vector3 eyeVec(eye.x, eye.y, eye.z);
									  
	// 모델뷰행렬의 회전변환과 이동변환적용 : M = T*R - p633 (11.29) 공식 사용
	m[0] = u.x;	m[4] = u.y;	m[8] = u.z;	m[12] = -eyeVec.dot(u);
	m[1] = v.x;	m[5] = v.y;	m[9] = v.z;	m[13] = -eyeVec.dot(v);
	m[2] = n.x;	m[6] = n.y;	m[10] = n.z;m[14] = -eyeVec.dot(n);
	m[3] = 0;	m[7] = 0;	m[11] = 0;	m[15] = 1.0;

	// GL 모델뷰 파이프라인에서 모델뷰 행렬 설정
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}

void Camera::setShape(float viewAngle, float aspect, float nearDist, float farDist) {
	this->viewAngle = viewAngle;	// 시야각
	this->aspect = aspect;			// 종횡비
	this->nearDist = nearDist;		// 전방투상면
	this->farDist = farDist;		// 후방투상면

	// GL Projection 파이프라인 설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(this->viewAngle, this->aspect, this->nearDist, this->farDist);

	//glMatrixMode(GL_MODELVIEW);
}

void Camera::setAspect(float aspect) {
	this->aspect = aspect;			// 종횡비
}

void Camera::getShape(float& viewAngle, float& aspect, float& nearDist, float& farDist) {
	viewAngle = this->viewAngle;
	aspect = this->aspect;			
	nearDist = this->nearDist;		
	farDist = this->farDist;		
}

// 비행기가 (du, dv, dn)만큼 이동 후 모델뷰 행렬 업데이트
// i.e 시점좌표계가 월드 좌표계 위에서 이동
void Camera::slide(double du, double dv, double dn) {
	// eye = eye + [u|v|n]*[du,dv,dn]^T
	eye.x += du*u.x + dv*v.x + dn*n.x;
	eye.y += du*u.y + dv*v.y + dn*n.y;
	eye.z += du*u.z + dv*v.z + dn*n.z;
	setModelViewMatrix();	// 모델뷰 행렬 업데이트
}

// (v1,v2)에 대해서 회전변환 
// i.e v1 <- cos*v1 + sin*v2, v2 <- -sin*v1 + cos*v2
void Camera::rotateAxes(Vector3& v1, Vector3& v2, float angle) {
	float rad = CAMERA_PI / 180 * angle;
	float c = cos(rad);
	float s = sin(rad);

	// v1,v2를 동시에 업데이트하기 위한 임시 변수
	Vector3 temp(c*v1.x + s*v2.x, c*v1.y + s*v2.y, c*v1.z + s*v2.z);	
	v2.set(-s*v1.x + c*v2.x, -s*v1.y + c*v2.y, -s*v1.z + c*v2.z);
	v1.set(temp);
}

void Camera::roll(float angle) {
	// u,v 축에 대한 회전
	rotateAxes(u, v, angle);
	setModelViewMatrix();	// 모델뷰 행렬 업데이트
}
void Camera::pitch(float angle) {
	// n,v 축에 대한 회전
	rotateAxes(n, v, angle);
	setModelViewMatrix();	// 모델뷰 행렬 업데이트
}
void Camera::yaw(float angle) {
	// u,n 축에 대한 회전
	rotateAxes(u, n, angle);
	setModelViewMatrix();	// 모델뷰 행렬 업데이트
}