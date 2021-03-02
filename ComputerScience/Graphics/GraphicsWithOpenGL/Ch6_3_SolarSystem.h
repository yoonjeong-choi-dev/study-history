#pragma once
#include <GL/glut.h>
#include <stdlib.h>


static int Day = 0, Time = 0;
const double distance_earth = 0.7;	// ����~�¾� �Ÿ�
const double distance_moon = 0.2;	// ����~ �� �Ÿ�
const double r_sun = 0.2, r_earth = 0.1, r_moon = 0.04;

double rotate_z_factor = 1.0;

void MySolarSystemDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.0, 0.3, 0.3);

	// �¾� �׸���
	// �¾� : ���� ��ǥ���� ������ �߽�
	glutWireSphere(r_sun, 20, 16);

	// ���� �׸���
	glPushMatrix();

	// ���� model ���� : ���� -> �̵� -> ����
	// axix ���� : ���� -> �̵� -> ���� (model ���� ����)
	glRotatef((GLfloat)Day, 0.0, 1.0 - rotate_z_factor, rotate_z_factor);		// Day ���� : ���� ����
	glTranslatef(distance_earth, 0.0, 0.0);		// �¾� ~ ���� �Ÿ���ŭ �̵�
	glRotatef((GLfloat)Time, 0.0, 1.0 - rotate_z_factor, rotate_z_factor);	// Time ���� : ���� ����

	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 10, 8);

	// �� �׸���
	glPushMatrix();
	// �� model ���� : �̵� -> ����
	glRotatef((GLfloat)Time, 0.0, 1.0 - rotate_z_factor, rotate_z_factor);	// Time ���� : �� ����
	glTranslatef(distance_moon, 0.0, 0.0);		// �� ~ ���� �Ÿ���ŭ �̵�

	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(r_moon, 10, 8);

	glPopMatrix();	// �� �׸��� end
	glPopMatrix();	// ���� �׸��� end

	glutSwapBuffers();
}

void MySolarSystemKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		// ���� ��ȯ
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