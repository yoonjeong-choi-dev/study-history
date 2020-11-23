#pragma once
#include <GL/glut.h>
#include <stdlib.h>

// 조명 설정 
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

// 은면 제거 루틴 함수
void InitVisibility() {
	//후면 제거 모드 활성화
	glEnable(GL_CULL_FACE);

	//정점의 시계방향으로 구성된 면을 표면으로 설정 : GL_CCW <-> GL_CW 테스트 해보자
	glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);

	// 후면(GL_BACK) 제거 
	glCullFace(GL_BACK);

	// 은면 제거 모드 활성화 : 지 버퍼 활성화
	glEnable(GL_DEPTH_TEST);
}

void InitVisibilty_revised() {
	//후면 제거 모드 활성화
	glEnable(GL_CULL_FACE);

	//정점의 시계방향으로 구성된 면을 표면으로 설정 : GL_CCW <-> GL_CW 테스트 해보자
	glFrontFace(GL_CW);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glCullFace(GL_FRONT);

	// 은면 제거 모드 활성화 : 지 버퍼 활성화
	glEnable(GL_DEPTH_TEST);
}

void MyDisplay() {
	// 프레임 버퍼와 깊이 버퍼 초기화
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
