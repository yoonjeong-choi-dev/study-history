#pragma once
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


GLboolean positionLightOn = true;
GLboolean spotLightOn = true;

void MyLightInit() {
	//���� �ֺ��ݻ�
	GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	//0�� ���� Ư�� : ��ġ�� ����
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat light0_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	//1�� ���� Ư�� : ����Ʈ����Ʈ
	GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light1_diffuse[] = { 0.5, 0.2, 0.3, 1.0 };
	GLfloat light1_specular[] = { 0.0, 0.0, 0.0, 1.0 };

	//��ü Ư��
	GLfloat material_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat material_specular[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };


	glShadeModel(GL_SMOOTH);	// ���� ���̵� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);	// ���� ���� Ȱ��ȭ
	glEnable(GL_LIGHTING);		// ���� ��� Ȱ��ȭ => glColor ��� x

	// 0�� ���� Ȱ��ȭ �� ����
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	// 1�� ���� Ȱ��ȭ �� ����
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	// ��ü Ư�� ����
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	// ���� �� ���� : ���� �ֺ��� ����
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	// ���� �� ���� : ���� ��ġ ���� -���� i.e ���� ��ġ�� ��ü�� �ſ� �����
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}



void MyDisplay() {
	// ��ġ�� ���� : ��ġ ����
	GLfloat lightPosition[] = { 0.0, 0.0, 2.0, 1.0 };

	// ����Ʈ����Ʈ ���� : ��ġ, ����, ���� ����
	GLfloat spotPosition[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat spotDirection[] = { -0.5, -1.0, -1.0 };
	GLfloat spotAngle[] = { 20.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �� �� ��� ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.5, 0.5, 0.5,
		0.0, 0.0, -1.0,
		0.0, 1.0, 0.0
	);	// ���� ��ȯ
	glTranslatef(0.3, 0.3, 0.0);	// �� ��ȯ

									// ��ġ�� ���� ���� : �� ��ȯ ���� ���� => ������ ��ġ�� �� �� ��Ŀ� ���� ����
	if (positionLightOn) {
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	}
	else {
		glDisable(GL_LIGHT0);
	}

	// ����Ʈ ����Ʈ ���� : �� ��ȯ ���� ���� => ������ ��ġ �� ������ �� �� ��Ŀ� ���� ����
	if (spotLightOn) {
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_POSITION, spotPosition);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
		glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);	// �ڻ��� �¼� ����
	}
	else {
		glDisable(GL_LIGHT1);
	}


	// �䷯�� �� ����
	glutSolidTorus(0.3, 0.6, 800, 800);

	glFlush();
	//glutSwapBuffers();
}


void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-1.0, 1.0,
		-1.0, 1.0,
		-1.0, 1.0
	);
}


void show_current_state() {
	printf("positionLightOn : %s, ", positionLightOn ? "true" : "false");
	printf("spotLightOn : %s\n", spotLightOn ? "true" : "false");
}


void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'p':
		positionLightOn = !positionLightOn;
		show_current_state();
		glutPostRedisplay();
		break;
	case 's':
		spotLightOn = !spotLightOn;
		show_current_state();
		glutPostRedisplay();
		break;
	case 't':
		if (positionLightOn) {
			positionLightOn = spotLightOn = false;
		}
		else {
			positionLightOn = spotLightOn = true;
		}
		show_current_state();
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
	}
}



void MyExampleMain(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(700, 400);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Two Lights");

	MyLightInit();				// ���� ����
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
}
