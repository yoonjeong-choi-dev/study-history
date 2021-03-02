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

// ��-�� �� ��ȯ ��Ŀ� ���ؼ� Ư�� ���� �׸���
void DrawScene() {

	glColor3f(0.7, 0.7, 0.7);

	// Fig 1 : 4*4 ȸ�� �簢��(������ �ٴ�)
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

	// Fig 2 : ������
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.5);
	glutWireTeapot(1.0);
	glPopMatrix();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	// ���ϴ� ���� ȭ��
	glViewport(0, 0, viewWidth / 2, viewHeight / 2);
	glPushMatrix();
	gluLookAt(
		0.0, 0.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	DrawScene();
	glPopMatrix();

	// ���ϴ� ���� ȭ��
	glViewport(viewWidth / 2, 0, viewWidth / 2, viewHeight / 2);
	glPushMatrix();
	gluLookAt(
		1.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	DrawScene();
	glPopMatrix();

	// �»�� ���� ȭ��
	glViewport(0, viewHeight / 2, viewWidth / 2, viewHeight / 2);
	glPushMatrix();
	gluLookAt(
		0.0, 1.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 1.0);   ////
	DrawScene();
	glPopMatrix();

	// ���� ���� ȭ��
	glViewport(viewWidth / 2, viewHeight / 2, viewWidth / 2, viewHeight / 2);
	// Init �Լ��� �������� ��� ���� ������ ����ϱ� ���� ��� ����
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();	// �� ���� ��� �ʱ�ȭ
						//gluPerspective(30, 1.0, 5.0, 50.0);	// ���� ���� ���� : ���� ��ǥ�� ����
	gluPerspective(30, (GLdouble)viewWidth / (GLdouble)viewHeight, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(
		5.0, 5.0, 5.0,
		0.0, 0.0, -0.5,
		0.0, 1.0, 0.0);	// ���� ���� : ���� ��ǥ�� ����
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