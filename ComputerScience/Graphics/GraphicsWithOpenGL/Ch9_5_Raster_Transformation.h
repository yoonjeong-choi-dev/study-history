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

	// 현재 시스템이 지원하는 점들의 크기 범위 구하기
	glGetFloatv(GL_POINT_SIZE_RANGE, size);

	// 점의 크기는 가장 작은 점의 10배로 설정
	glPointSize(size[0] * 10);

	// 점 찍기
	glBegin(GL_POINTS);
	for (angle = 0.0; angle <= 2.0*Pi; angle += 2.0*Pi / (((GLfloat)numPoints))) {
		glVertex3f(0.5*cos(angle), 0.5*sin(angle), 0.0);
	}
	glEnd();
	glFlush();
}


void MyDrawingLinesDisplay() {
	GLint scaleFactor = 1;		// 패턴 길이결정 변수
	GLushort pattern = 0x00FF;	// 선분의 점표 패턴에 대한 변수
	GLfloat height;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3);

	// 선 패턴 기능 활성화
	glEnable(GL_LINE_STIPPLE);

	// scaleFactor를 키우면서 다양한 패턴을 그리는 작업
	for (height = -0.9; height <= 0.9; height += 0.4) {
		// 패턴 함수를 호출하여 다음에 그릴 선분의 패턴 등록
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

	glShadeModel(GL_SMOOTH);	// 선형 보간 사용
								//glShadeModel(GL_FLAT);

	glBegin(GL_TRIANGLES);

	// 정점 1 : 녹색
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	// 정점 2 : 흑색
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, 0.0);

	// 정점 3 : 적색
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