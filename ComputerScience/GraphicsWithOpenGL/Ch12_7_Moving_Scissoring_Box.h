#pragma once
#include <Windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
#pragma comment(linker, "/ENTRY:mainCRTStartup")

// ���� ��ġ
GLfloat light_position[] = { 5.0, 10.0, 50.0,0.0 };

// ������ ũ��
int width = 800, height = 400;

// ���� �ڽ� ���� : GLUT ��ǥ�� ����
GLint startX = 100, startY = 120;
GLint endX = 250, endY = 270;


void Init() {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.1f, 0.1f, 0.2f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void MyReshape(GLint w, GLint h) {
	width = w;
	height = h;
	glutPostRedisplay();
}

void MySpecialKeyboard(GLint key, GLint x, GLint y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		if (endX <= 400) {
			startX += 1;
			endX += 1;
		}
		break;
	case GLUT_KEY_LEFT:
		if (startX >= 0) {
			startX -= 1;
			endX -= 1;
		}
		break;
		// GLUT�� GL�� y���� ���� �ݴ� �������� �����δ�
	case GLUT_KEY_DOWN:
		if (endY <= 800) {
			startY += 1;
			endY += 1;
		}
		break;
	case GLUT_KEY_UP:
		if (startY >= 0) {
			startY -= 1;
			endY -= 1;
		}
		break;
	}
	glutPostRedisplay();
}

// ���콺 Ŭ���� ������ �������� ���� �ڽ� ������
void MyMouseClick(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		startX = x;
		startY = y;
	}
}

void MyMouseMove(GLint x, GLint y) {
	endX = x;
	endY = y;
	glutPostRedisplay();
}


// ���� �ڽ��� ȭ�鿡 ��Ÿ���� ���� �Լ�
void DrawScissorBox() {
	// ���� �ڽ� : [startX, endX] * [startY, end Y] 
	// ������ ũ�� : width/2 * height
	// ��ǥ ũ�� : [0, 1] * [0, 1]
	// Y�� : GLUT�� GL�� y���� ���� �ݴ� �������� �����δ�

	glBegin(GL_POLYGON);
	glVertex3f(
		(GLfloat)startX / (GLfloat)(width / 2),
		(GLfloat)(height - startY) / (GLfloat)height,
		1.0
	);
	glVertex3f(
		(GLfloat)startX / (GLfloat)(width / 2),
		(GLfloat)(height - endY) / (GLfloat)height,
		1.0
	);
	glVertex3f(
		(GLfloat)endX / (GLfloat)(width / 2),
		(GLfloat)(height - endY) / (GLfloat)height,
		1.0
	);
	glVertex3f(
		(GLfloat)endX / (GLfloat)(width / 2),
		(GLfloat)(height - startY) / (GLfloat)height,
		1.0
	);
	glEnd();
}

// ��ü��(����, ����ü, �� ������) �׸��� �Լ�
void DrawScene() {

	// ����
	glPushMatrix();
	glColor3f(0.5, 0.5, 1.0);
	glutSolidSphere(0.7, 100.0, 100.0);
	glPopMatrix();

	// ����ü
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.5);
	glTranslatef(2.0, 2.0, 0.0);
	glutSolidCube(1.8);
	glPopMatrix();

	// ������
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.0, 2.0, 0.0);
	glutSolidTeapot(0.5);
	glPopMatrix();
}


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);


	// ù��° �� ��Ʈ�� ���� ����
	// 1. ���� �׽�Ʈ ���� ��� �׸���
	// 2. ���� �ڽ� ��ü �׸���
	glLoadIdentity();
	glViewport(0, 0, width / 2, height);
	glPushMatrix();

	// ���� �׽�Ʈ ���� ��� �׸���
	glPushMatrix();
	glScalef(0.15, 0.15, 0.15);
	glTranslatef(2.0, 2.0, 0.0);
	DrawScene();
	glPopMatrix();

	// ���� �ڽ� ��ü �׸���
	glEnable(GL_BLEND);
	glColor4f(0.8, 0.8, 0.8, 0.5);
	DrawScissorBox();
	glDisable(GL_BLEND);
	glPopMatrix();

	// �ι�° �� ��Ʈ�� ���� ����
	// 1. ���� �׽�Ʈ ���� ��� �׸���
	glLoadIdentity();
	glViewport(width / 2, 0, width / 2, height);
	glPushMatrix();

	// �����׽�Ʈ Ȱ��ȭ �� ���� �ڽ� ����
	glEnable(GL_SCISSOR_TEST);
	if (endY > startY) {
		glScissor(startX + 400, abs(height - endY),
			abs(endX - startX), abs(endY - startY));
	}
	else {
		glScissor(startX + 400, abs(height - startY),
			abs(endX - startX), abs(endY - startY));
	}

	// ���� �׽�Ʈ ���� ��� �׸���
	glPushMatrix();
	glScalef(0.15, 0.15, 0.15);
	glTranslatef(2.0, 2.0, 0.0);
	DrawScene();
	glPopMatrix();

	glDisable(GL_SCISSOR_TEST);
	glPopMatrix();
	glutSwapBuffers();
}


void ScissorBoxTestExample() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(700, 400);
	glutCreateWindow("Scisso Box Test");

	Init();
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(MySpecialKeyboard);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
}