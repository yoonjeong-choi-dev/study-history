#pragma once
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


static int spinAngle = 0;
static int ySpinAngle = 0;
const double lightPosZ = 1.5;
void MyLightInit() {
	// ���� Ư�� ����
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat light0_diffuse[] = { 0.8, 0.7, 0.6, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };


	glShadeModel(GL_SMOOTH);    // ���� ���̵� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);    // ���� ���� Ȱ��ȭ
	glEnable(GL_LIGHTING);      // ���� ��� Ȱ��ȭ => glColor ��� x

								// 0�� ���� Ȱ��ȭ �� ����
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
}



void MyDisplay() {
	// ��ġ�� ���� : ��ġ ����
	GLfloat lightPosition[] = { 0.0, 0.0, lightPosZ, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ���� ��� ����
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);

	// ���� �׸��� ����
	glPushMatrix();
	glRotatef(spinAngle, 1.0, 0.0, 0.0); // x�� ȸ��
	glRotatef(ySpinAngle, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glTranslatef(0.0, 0.0, lightPosZ);	// ���� ��ġ : ���� ��ǥ�迡�� z�� 1.5��ŭ ������ �� ��ġ

										// ���� �׸��� : �� �ڵ� glTranslatef(0.0, 0.0, 1.5); ��ġ�� �׷�����
	glDisable(GL_LIGHTING);			// ���� ��Ȱ��ȭ : ������ ��ġ�� �׸������ؼ�
	glColor3f(0.9, 0.9, 0.9);		// ������ �� ����
	glutWireSphere(0.06, 10, 10);	// ���� �� ����
	glEnable(GL_LIGHTING);			// ���� �׸� �� ���� Ȱ��ȭ

	glPopMatrix();	// ���� �׸��� ��


					// ��ü �� ����
	glutSolidSphere(1.0, 400, 400);
	glPopMatrix();
	glFlush();
}


// �������� �Լ��� ���α׷� ���۽� ���� 
// i.e ���÷��� �ݹ� ������ ȣ�� => �𵨺� ��� ��忡�� MyDisplay ����
void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void MyMouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			spinAngle = (spinAngle + 15) % 360;
			glutPostRedisplay();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			spinAngle = (360 + spinAngle - 15) % 360;
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		ySpinAngle = (360 + ySpinAngle - 15) % 360;
		glutPostRedisplay();
		break;
	case 'd':
		ySpinAngle = (ySpinAngle + 15) % 360;
		glutPostRedisplay();
		break;
	case 's':
		spinAngle = (spinAngle + 15) % 360;
		glutPostRedisplay();
		break;
	case 'w':
		spinAngle = (360 + spinAngle - 15) % 360;
		glutPostRedisplay();
		break;
	}
}

void MyExampleMain(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(700, 400);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Moving Light");

	MyLightInit();				// ���� ����
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(MyMouse);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
}