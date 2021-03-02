#pragma once
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define Pi 3.141592

void MyCirclingDotDisplay() {
	GLfloat size[2];
	GLfloat angle;
	int numPoints = 20;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	// ���� �ý����� �����ϴ� ������ ũ�� ���� ���ϱ�
	glGetFloatv(GL_POINT_SIZE_RANGE, size);

	// ���� ũ��� ���� ���� ���� 10��� ����
	glPointSize(size[0] * 10);

	// �� ���
	glBegin(GL_POINTS);
	for (angle = 0.0; angle <= 2.0*Pi; angle += 2.0*Pi / (((GLfloat)numPoints))) {
		glVertex3f(0.5*cos(angle), 0.5*sin(angle), 0.0);
	}
	glEnd();
	glFlush();
}


void MyDrawingLinesDisplay() {
	GLint scaleFactor = 1;		// ���� ���̰��� ����
	GLushort pattern = 0x00FF;	// ������ ��ǥ ���Ͽ� ���� ����
	GLfloat height;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3);

	// �� ���� ��� Ȱ��ȭ
	glEnable(GL_LINE_STIPPLE);

	// scaleFactor�� Ű��鼭 �پ��� ������ �׸��� �۾�
	for (height = -0.9; height <= 0.9; height += 0.4) {
		// ���� �Լ��� ȣ���Ͽ� ������ �׸� ������ ���� ���
		glLineStipple(scaleFactor, pattern);

		glBegin(GL_LINES);
		glVertex3f(-1.0, height, 0.0);
		glVertex3f(1.0, height, 0.0);
		glEnd();

		scaleFactor *= 2;
	}

	glDisable(GL_LINE_STIPPLE);
	glFlush();
}


void MyTriagnleInterpolationDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);	// ���� ���� ���
								//glShadeModel(GL_FLAT);

	glBegin(GL_TRIANGLES);

	// ���� 1 : ���
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	// ���� 2 : ���
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, 0.0);

	// ���� 3 : ����
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);

	glEnd();
	glFlush();
}

void RasterTransformationExample(int argc, char** argv, void(*func)()) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(700, 400);
	glutCreateWindow("RasterTransformation");

	glClearColor(1.0, 1.0, 1.0, 0.1);

	glutDisplayFunc(func);
	glutMainLoop();
}