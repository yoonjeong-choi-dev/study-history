#pragma once
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


static int spinAngle = 0;
static int ySpinAngle = 0;
const double lightPosZ = 1.5;
void MyLightInit() {
	// 광원 특성 설정
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat light0_diffuse[] = { 0.8, 0.7, 0.6, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };


	glShadeModel(GL_SMOOTH);    // 구로 쉐이딩 활성화
	glEnable(GL_DEPTH_TEST);    // 깊이 버퍼 활성화
	glEnable(GL_LIGHTING);      // 조명 기능 활성화 => glColor 사용 x

								// 0번 광원 활성화 및 셋팅
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
}



void MyDisplay() {
	// 위치성 광원 : 위치 설정
	GLfloat lightPosition[] = { 0.0, 0.0, lightPosZ, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 이전 행렬 저장
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);

	// 광원 그리기 시작
	glPushMatrix();
	glRotatef(spinAngle, 1.0, 0.0, 0.0); // x축 회전
	glRotatef(ySpinAngle, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glTranslatef(0.0, 0.0, lightPosZ);	// 광원 위치 : 현재 좌표계에서 z축 1.5만큼 떨어진 곳 위치

										// 광원 그리기 : 위 코드 glTranslatef(0.0, 0.0, 1.5); 위치에 그려진다
	glDisable(GL_LIGHTING);			// 조명 비활성화 : 광원의 위치를 그리기위해서
	glColor3f(0.9, 0.9, 0.9);		// 광원의 색 설정
	glutWireSphere(0.06, 10, 10);	// 광원 모델 설정
	glEnable(GL_LIGHTING);			// 광원 그린 후 조명 활성화

	glPopMatrix();	// 광원 그리기 끝


					// 구체 모델 정의
	glutSolidSphere(1.0, 400, 400);
	glPopMatrix();
	glFlush();
}


// 리쉐이프 함수는 프로그램 시작시 실행 
// i.e 디스플레이 콜백 이전에 호출 => 모델뷰 행렬 모드에서 MyDisplay 실행
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

	MyLightInit();				// 조명 설정
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(MyMouse);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
}