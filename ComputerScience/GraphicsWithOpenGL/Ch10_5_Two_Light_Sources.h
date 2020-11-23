#pragma once
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


GLboolean positionLightOn = true;
GLboolean spotLightOn = true;

void MyLightInit() {
	//전역 주변반사
	GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	//0번 광원 특성 : 위치성 광원
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat light0_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	//1번 광원 특성 : 스포트라이트
	GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light1_diffuse[] = { 0.5, 0.2, 0.3, 1.0 };
	GLfloat light1_specular[] = { 0.0, 0.0, 0.0, 1.0 };

	//물체 특성
	GLfloat material_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat material_specular[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 25.0 };


	glShadeModel(GL_SMOOTH);	// 구로 쉐이딩 활성화
	glEnable(GL_DEPTH_TEST);	// 깊이 버퍼 활성화
	glEnable(GL_LIGHTING);		// 조명 기능 활성화 => glColor 사용 x

	// 0번 광원 활성화 및 셋팅
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	// 1번 광원 활성화 및 셋팅
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	// 물체 특성 셋팅
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	// 조명 모델 정의 : 전역 주변광 설정
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	// 조명 모델 정의 : 시점 위치 설정 -근접 i.e 시점 위치가 물체에 매우 가까움
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}



void MyDisplay() {
	// 위치성 광원 : 위치 설정
	GLfloat lightPosition[] = { 0.0, 0.0, 2.0, 1.0 };

	// 스포트라이트 광원 : 위치, 방향, 각도 설정
	GLfloat spotPosition[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat spotDirection[] = { -0.5, -1.0, -1.0 };
	GLfloat spotAngle[] = { 20.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 모델 뷰 행렬 설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.5, 0.5, 0.5,
		0.0, 0.0, -1.0,
		0.0, 1.0, 0.0
	);	// 시점 변환
	glTranslatef(0.3, 0.3, 0.0);	// 모델 변환

									// 위치성 광원 설정 : 모델 변환 이후 선언 => 광원의 위치는 모델 뷰 행렬에 의해 변경
	if (positionLightOn) {
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	}
	else {
		glDisable(GL_LIGHT0);
	}

	// 스포트 라이트 설정 : 모델 변환 이후 선언 => 광원의 위치 및 방향은 모델 뷰 행렬에 의해 변경
	if (spotLightOn) {
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_POSITION, spotPosition);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
		glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);	// 코사인 승수 설정
	}
	else {
		glDisable(GL_LIGHT1);
	}


	// 토러스 모델 정의
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

	MyLightInit();				// 조명 설정
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
}
