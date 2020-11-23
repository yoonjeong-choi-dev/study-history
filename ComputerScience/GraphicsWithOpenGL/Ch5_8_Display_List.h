#pragma once
#include <GL/glut.h>



int MyListId;

// ���÷��� ����Ʈ�� ����ϱ� ���� ��ɾ� ����
void MyCreateList() {

	// ���÷��� ����Ʈ ����
	MyListId = glGenLists(1);

	// glNewList ~ glEndList : ����Ʈ�� �����ϴ� �Լ� ����
	// MyListId�� ���� ���÷��� ����Ʈ�� ������ �Ϸ�(GL_COMPILE)�� �������� ����
	glNewList(MyListId, GL_COMPILE);

	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();

	glEndList();
}

void MyListDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 300, 300);

	// �������� �Ϸ�� ���÷��� ����Ʈ�� ���÷����� �ݹ��Լ����� ȣ��
	glCallList(MyListId);
	glFlush();
}

void MyDisplayListExample(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowSize(300, 300);
	glutInitWindowPosition(700, 400);
	glutCreateWindow("Display List Example");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyListDisplay);

	MyCreateList();

	glutMainLoop();
}

