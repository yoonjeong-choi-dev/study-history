#pragma once
#include <GL/glut.h>



int MyListId;

// 디스플레이 리스트를 사용하기 위한 명령어 모임
void MyCreateList() {

	// 디스플레이 리스트 선언
	MyListId = glGenLists(1);

	// glNewList ~ glEndList : 리스트를 구성하는 함수 나열
	// MyListId를 가진 디스플레이 리스트를 컴파일 완료(GL_COMPILE)된 버전으로 생성
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

	// 컴파일이 완료된 디스플레이 리스트를 디스플레이할 콜백함수에서 호출
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

