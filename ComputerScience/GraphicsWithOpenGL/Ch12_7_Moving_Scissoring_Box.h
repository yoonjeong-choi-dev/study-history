#pragma once
#include <Windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
#pragma comment(linker, "/ENTRY:mainCRTStartup")

// 광원 위치
GLfloat light_position[] = { 5.0, 10.0, 50.0,0.0 };

// 윈도우 크기
int width = 800, height = 400;

// 시저 박스 영역 : GLUT 좌표계 기준
GLint startX = 100, startY = 120;
GLint endX = 250, endY = 270;


void Init() {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.1f, 0.1f, 0.2f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void MyReshape(GLint w, GLint h) {
	width = w;
	height = h;
	glutPostRedisplay();
}

void MySpecialKeyboard(GLint key, GLint x, GLint y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		if (endX <= 400) {
			startX += 1;
			endX += 1;
		}
		break;
	case GLUT_KEY_LEFT:
		if (startX >= 0) {
			startX -= 1;
			endX -= 1;
		}
		break;
		// GLUT과 GL의 y축은 서로 반대 방향으로 움직인다
	case GLUT_KEY_DOWN:
		if (endY <= 800) {
			startY += 1;
			endY += 1;
		}
		break;
	case GLUT_KEY_UP:
		if (startY >= 0) {
			startY -= 1;
			endY -= 1;
		}
		break;
	}
	glutPostRedisplay();
}

// 마우스 클릭후 움직인 영역으로 시저 박스 재정의
void MyMouseClick(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		startX = x;
		startY = y;
	}
}

void MyMouseMove(GLint x, GLint y) {
	endX = x;
	endY = y;
	glutPostRedisplay();
}


// 시저 박스를 화면에 나타내기 위한 함수
void DrawScissorBox() {
	// 시저 박스 : [startX, endX] * [startY, end Y] 
	// 윈도우 크기 : width/2 * height
	// 목표 크기 : [0, 1] * [0, 1]
	// Y축 : GLUT과 GL의 y축은 서로 반대 방향으로 움직인다

	glBegin(GL_POLYGON);
	glVertex3f(
		(GLfloat)startX / (GLfloat)(width / 2),
		(GLfloat)(height - startY) / (GLfloat)height,
		1.0
	);
	glVertex3f(
		(GLfloat)startX / (GLfloat)(width / 2),
		(GLfloat)(height - endY) / (GLfloat)height,
		1.0
	);
	glVertex3f(
		(GLfloat)endX / (GLfloat)(width / 2),
		(GLfloat)(height - endY) / (GLfloat)height,
		1.0
	);
	glVertex3f(
		(GLfloat)endX / (GLfloat)(width / 2),
		(GLfloat)(height - startY) / (GLfloat)height,
		1.0
	);
	glEnd();
}

// 물체들(원구, 육면체, 차 주전자) 그리는 함수
void DrawScene() {

	// 원구
	glPushMatrix();
	glColor3f(0.5, 0.5, 1.0);
	glutSolidSphere(0.7, 100.0, 100.0);
	glPopMatrix();

	// 육면체
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.5);
	glTranslatef(2.0, 2.0, 0.0);
	glutSolidCube(1.8);
	glPopMatrix();

	// 주전자
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.0, 2.0, 0.0);
	glutSolidTeapot(0.5);
	glPopMatrix();
}


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);


	// 첫번째 뷰 포트에 대한 설정
	// 1. 시저 테스트 이전 장면 그리기
	// 2. 시저 박스 자체 그리기
	glLoadIdentity();
	glViewport(0, 0, width / 2, height);
	glPushMatrix();

	// 시저 테스트 이전 장면 그리기
	glPushMatrix();
	glScalef(0.15, 0.15, 0.15);
	glTranslatef(2.0, 2.0, 0.0);
	DrawScene();
	glPopMatrix();

	// 시저 박스 자체 그리기
	glEnable(GL_BLEND);
	glColor4f(0.8, 0.8, 0.8, 0.5);
	DrawScissorBox();
	glDisable(GL_BLEND);
	glPopMatrix();

	// 두번째 뷰 포트에 대한 설정
	// 1. 시저 테스트 이후 장면 그리기
	glLoadIdentity();
	glViewport(width / 2, 0, width / 2, height);
	glPushMatrix();

	// 시저테스트 활성화 및 시저 박스 설정
	glEnable(GL_SCISSOR_TEST);
	if (endY > startY) {
		glScissor(startX + 400, abs(height - endY),
			abs(endX - startX), abs(endY - startY));
	}
	else {
		glScissor(startX + 400, abs(height - startY),
			abs(endX - startX), abs(endY - startY));
	}

	// 시저 테스트 이후 장면 그리기
	glPushMatrix();
	glScalef(0.15, 0.15, 0.15);
	glTranslatef(2.0, 2.0, 0.0);
	DrawScene();
	glPopMatrix();

	glDisable(GL_SCISSOR_TEST);
	glPopMatrix();
	glutSwapBuffers();
}


void ScissorBoxTestExample() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(700, 400);
	glutCreateWindow("Scisso Box Test");

	Init();
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(MySpecialKeyboard);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
}