#pragma once
#include <GL/glut.h>
#include <stdlib.h>

GLint viewWidth, viewHeight;

void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// 모델-뷰 현 변환 행렬에 대해서 특정 씬을 그린다
void DrawScene() {

	glColor3f(0.7, 0.7, 0.7);

	// Fig 1 : 4*4 회색 사각형(주전자 바닥)
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);

	glBegin(GL_QUADS);
	glVertex3f(2.0, 0.0, 2.0);
	glVertex3f(2.0, 0.0, -2.0);
	glVertex3f(-2.0, 0.0, -2.0);
	glVertex3f(-2.0, 0.0, 2.0);
	glEnd();

	glPopMatrix();

	glColor3f(0.3, 0.3, 0.7);

	// Fig 2 : 주전자
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.5);
	glutWireTeapot(1.0);
	glPopMatrix();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	// 좌하단 분할 화면
	glViewport(0, 0, viewWidth / 2, viewHeight / 2);
	glPushMatrix();
	gluLookAt(
		0.0, 0.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	DrawScene();
	glPopMatrix();

	// 우하단 분할 화면
	glViewport(viewWidth / 2, 0, viewWidth / 2, viewHeight / 2);
	glPushMatrix();
	gluLookAt(
		1.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	DrawScene();
	glPopMatrix();

	// 좌상단 분할 화면
	glViewport(0, viewHeight / 2, viewWidth / 2, viewHeight / 2);
	glPushMatrix();
	gluLookAt(
		0.0, 1.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 1.0);   ////
	DrawScene();
	glPopMatrix();

	// 우상단 분할 화면
	glViewport(viewWidth / 2, viewHeight / 2, viewWidth / 2, viewHeight / 2);
	// Init 함수의 평행투상 대신 원근 투상을 사용하기 위해 모드 변경
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();	// 현 투상 행렬 초기화
						//gluPerspective(30, 1.0, 5.0, 50.0);	// 가시 부피 설정 : 시점 좌표계 기준
	gluPerspective(30, (GLdouble)viewWidth / (GLdouble)viewHeight, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(
		5.0, 5.0, 5.0,
		0.0, 0.0, -0.5,
		0.0, 1.0, 0.0);	// 시점 설정 : 전역 좌표계 기준
	DrawScene();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
}


void MyReshape(int w, int h) {
	viewWidth = w;
	viewHeight = h;
}

void MyReshapeForView(int w, int h) {
	viewWidth = w;
	viewHeight = h;

	glutPostRedisplay();
}

void example() {
	viewWidth = 500, viewHeight = 500;

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(viewWidth, viewHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Projection-View");

	Init();
	glutDisplayFunc(MyDisplay);
	//glutReshapeFunc(MyReshape);
	glutReshapeFunc(MyReshapeForView);
	glutMainLoop();
}