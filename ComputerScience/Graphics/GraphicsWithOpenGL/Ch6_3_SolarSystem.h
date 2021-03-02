#pragma once
#include <GL/glut.h>
#include <stdlib.h>


static int Day = 0, Time = 0;
const double distance_earth = 0.7;	// 지구~태양 거리
const double distance_moon = 0.2;	// 지구~ 달 거리
const double r_sun = 0.2, r_earth = 0.1, r_moon = 0.04;

double rotate_z_factor = 1.0;

void MySolarSystemDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.0, 0.3, 0.3);

	// 태양 그리기
	// 태양 : 전역 좌표계의 원점이 중심
	glutWireSphere(r_sun, 20, 16);

	// 지구 그리기
	glPushMatrix();

	// 지구 model 기준 : 자전 -> 이동 -> 공전
	// axix 기준 : 공전 -> 이동 -> 자전 (model 기준 역순)
	glRotatef((GLfloat)Day, 0.0, 1.0 - rotate_z_factor, rotate_z_factor);		// Day 각도 : 지구 공전
	glTranslatef(distance_earth, 0.0, 0.0);		// 태양 ~ 지구 거리만큼 이동
	glRotatef((GLfloat)Time, 0.0, 1.0 - rotate_z_factor, rotate_z_factor);	// Time 각도 : 지구 자전

	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 10, 8);

	// 달 그리기
	glPushMatrix();
	// 달 model 기준 : 이동 -> 공전
	glRotatef((GLfloat)Time, 0.0, 1.0 - rotate_z_factor, rotate_z_factor);	// Time 각도 : 달 공전
	glTranslatef(distance_moon, 0.0, 0.0);		// 달 ~ 지구 거리만큼 이동

	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(r_moon, 10, 8);

	glPopMatrix();	// 달 그리기 end
	glPopMatrix();	// 지구 그리기 end

	glutSwapBuffers();
}

void MySolarSystemKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		// 시점 변환
		if (rotate_z_factor == 1.0) {
			rotate_z_factor = 0.0;
		}
		else {
			rotate_z_factor = 1.0;
		}
	case 'w':
		Day = (Day + 10) % 360;
		glutPostRedisplay();
		break;
	case 's':
		Day = (Day - 10) % 360;
		glutPostRedisplay();
		break;
	case 'd':
		Time = (Time + 5) % 360;
		glutPostRedisplay();
		break;
	case 'a':
		Time = (Time - 5) % 360;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void MySolarSystemExample(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(700, 500);
	glutCreateWindow("Solar System");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MySolarSystemDisplay);
	glutKeyboardFunc(MySolarSystemKeyboard);
	glutMainLoop();
}