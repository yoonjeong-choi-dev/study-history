#pragma once
#include <GL/glut.h>
#include <stdlib.h>

// ���� ���� 
void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 2, 3.0, 0.0 };

	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// ���� ���� ��ƾ �Լ�
void InitVisibility() {
	//�ĸ� ���� ��� Ȱ��ȭ
	glEnable(GL_CULL_FACE);

	//������ �ð�������� ������ ���� ǥ������ ���� : GL_CCW <-> GL_CW �׽�Ʈ �غ���
	glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);

	// �ĸ�(GL_BACK) ���� 
	glCullFace(GL_BACK);

	// ���� ���� ��� Ȱ��ȭ : �� ���� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);
}

void InitVisibilty_revised() {
	//�ĸ� ���� ��� Ȱ��ȭ
	glEnable(GL_CULL_FACE);

	//������ �ð�������� ������ ���� ǥ������ ���� : GL_CCW <-> GL_CW �׽�Ʈ �غ���
	glFrontFace(GL_CW);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glCullFace(GL_FRONT);

	// ���� ���� ��� Ȱ��ȭ : �� ���� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);
}

void MyDisplay() {
	// ������ ���ۿ� ���� ���� �ʱ�ȭ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0, 0.4, 0.5,
		0.0, -0.5, -1.0,
		0.0, 1.0, 0.0);
	glutSolidTeapot(0.58);
	glFlush();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 2.0);
}

void MyTeapotExample(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Visibility Example");
	glClearColor(0.5, 0.5, 0.5, 0.0);

	InitLight();
	InitVisibility();
	//InitVisibilty_revised();

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
}
