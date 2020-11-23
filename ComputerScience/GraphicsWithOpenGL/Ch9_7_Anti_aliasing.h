#pragma once
#include <GL/glut.h>
#include <stdlib.h>

/*
점과 선분에 대한 간단한 안티 에일리어싱
*/
void SimpleAntiAliasingDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	// 혼합 기능 활성화 : 지엘의 안티 에일리어싱은 혼합 함수 이용
	glEnable(GL_BLEND);

	// 혼합 모드 설정
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 부드러운 점 기능 활성화
	glEnable(GL_POINT_SMOOTH);

	// 지엘에 일종의 힌트를 전달하기 위한 것
	// GL_POINT_SMOOTH_HINT : 점에 대한 안티 에일리어싱
	// GL_NICEST : 속도가 느리더라도 가장 질이 좋은 안티 에일리어싱을 가하라는 의미
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	// 크기 12인 점을 그림
	glPointSize(12);
	glBegin(GL_POINTS);
	glVertex3f(-0.9, -0.65, 0.0);
	glEnd();

	// 부드러운 점 기능 비활성화
	glDisable(GL_POINT_SMOOTH);

	// 부드러운 선 기능 활성화
	glEnable(GL_LINE_SMOOTH);

	// 지엘에 일종의 힌트를 전달하기 위한 것
	// GL_LINE_SMOOTH_HINT : 선에 대한 안티 에일리어싱
	// GL_NICEST : 속도가 느리더라도 가장 질이 좋은 안티 에일리어싱을 가하라는 의미
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// 선분 그리기
	glBegin(GL_LINES);
	glVertex3f(-1.0, -0.6, 0.0);
	glVertex3f(1.0, -0.2, 0.0);
	glVertex3f(-1.0, -0.6, 0.0);
	glVertex3f(0.75, 1.0, 0.0);
	glVertex3f(-1.0, -0.6, 0.0);
	glVertex3f(-0.75, 1.0, 0.0);
	glEnd();

	// 부드러운 선 기능 비활성화
	glDisable(GL_LINE_SMOOTH);

	glDisable(GL_BLEND);
	glFlush();
}


void SimpleAntiAliasingExample(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(700, 400);
	glutCreateWindow("RasterTransformation");

	glClearColor(1.0, 1.0, 1.0, 0.1);

	glutDisplayFunc(SimpleAntiAliasingDisplay);
	glutMainLoop();
}



/*
안티에일리어싱 비교 예시
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define GAP 16
void redisplay_all();
GLuint window, world, screen, command;


GLfloat fDelta = 0.0f;
GLboolean bBlend = true;   // 혼합 함수 사용 여부
GLboolean bSmooth = true;   // 부드러운 선분 기능 사용 여부

const GLfloat rgbFactor = 255.0f;
GLfloat red = 0.0, green = 0.0, blue = 0.0;
GLint index = 0;

// rgb 파레트 설정
unsigned char PALETTE[16][3] = {
	{ 255, 255, 255 },      // WHITE
	{ 0,   255, 255 },      // CYAN
	{ 255,   0, 255 },      // PURPLE
	{ 0,   0,   255 },      // BLUE
	{ 192, 192, 192 },      // LIGHT GRAY
	{ 128, 128, 128 },      // DARK GRAY
	{ 0  , 128, 128 },      // DARK TEAL
	{ 128,   0, 128 },      // DARK PURPLE
	{ 0  ,   0, 128 },      // DARK BLUE
	{ 255, 255,   0 },      // YELLOW
	{ 0  , 255,   0 },      // GREEN
	{ 128, 128,   0 },      // DARK YELLOW
	{ 0  , 128,   0 },      // DARK GREEN
	{ 255,   0,   0 },      // RED
	{ 128,   0,   0 },      // DARK RED
	{ 0  ,   0,   0 },      // BLACK
};

void world_display() {
	red = PALETTE[index][0] / rgbFactor;
	green = PALETTE[index][1] / rgbFactor;
	blue = PALETTE[index][2] / rgbFactor;
	glColor3f(red, green, blue);

	// 혼합 함수 기능 설정
	if (bBlend) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	// 부드러운 선 기능 설정
	if (bSmooth) {
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	}

	glBegin(GL_LINES);
	glVertex3f(-1.0 + fDelta, 1.0, 0.0);
	glVertex3f(1.0 - fDelta, -1.0, 0.0);
	glVertex3f(-1.0, -1.0 + fDelta, 0.0);
	glVertex3f(1.0, 1.0 - fDelta, 0.0);
	glEnd();

	if (bSmooth) {
		glDisable(GL_LINE_SMOOTH);
	}
	if (bBlend) {
		glDisable(GL_BLEND);
	}

	glutSwapBuffers();
}


void world_timer(int val) {
	if (fDelta < 2.0f) {
		fDelta = fDelta + 0.1;
	}
	else {
		fDelta = 0.0;
		// 16개의 파레트 색이 순차적으로 돌면서 칠해짐
		if (++index >= 15) {
			index = 0;
			glClear(GL_COLOR_BUFFER_BIT);	// 색이 바뀔때마다 화면 초기화
		}

	}
	redisplay_all();
	glutTimerFunc(100, world_timer, 1);
}


void screen_display() {
	static unsigned char buffer[128 * 128 * 4 * 2];

	// 현재 윈도우 : world
	glutSetWindow(world);

	// 현재 윈도우의 작은 창에 그려진 프레임 버퍼 내용을 메모리(buffer)에 복사하는 함수
	// 여기서는 [0,127]*[0,127]의 윈도우 창의 프레임 버퍼를 복사
	glReadPixels(0, 0, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	// 현재 윈도우 : screen
	glutSetWindow(screen);

	// 현재 윈도우를 확대
	glPixelZoom(4, 4);

	// 현재 윈도우에 이전에 복사한 메모리(buffer)로 프레임 버퍼 기록
	glDrawPixels(128, 128, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	glPixelZoom(0, 0);
	glutSwapBuffers();
}

void main_display() {
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void show_current_state() {
	printf("blend : %s, ", bBlend ? "true" : "false");
	printf("smooth : %s\n", bSmooth ? "true" : "false");

}

void main_keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'b':	// 혼합 함수 사용 여부 설정
		bBlend = !bBlend;
		show_current_state();
		break;
	case 's':	// 스무딩 함수 사용 여부 설정
		bSmooth = !bSmooth;
		show_current_state();
		break;
	case 't':	// 혼합 및 스무딩 함수 사용 여부 동시 설정
		if (!bBlend) {
			bBlend = bSmooth = true;
		}
		else {
			bBlend = bSmooth = false;
		}
		show_current_state();
		break;
	case 27:
		exit(0);
	}
}

void redisplay_all() {
	//glutSetWindow(command);
	//glutPostRedisplay();

	glutSetWindow(world);
	glutPostRedisplay();

	glutSetWindow(screen);
	glutPostRedisplay();
}


void mainFunction(int argc, char** argv) {
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(128 + 512 + GAP * 3, 512 * GAP * 2);
	glutInitWindowPosition(700, 400);
	glutInit(&argc, argv);

	window = glutCreateWindow("Line Antialiasing Demo");
	glutDisplayFunc(main_display);
	glutKeyboardFunc(main_keyboard);

	world = glutCreateSubWindow(window, GAP, GAP, 128, 128);
	glutDisplayFunc(world_display);
	glutKeyboardFunc(main_keyboard);

	screen = glutCreateSubWindow(window, GAP + 128 + GAP, GAP, 512, 512);
	glutDisplayFunc(screen_display);
	glutKeyboardFunc(main_keyboard);

	redisplay_all();

	glutTimerFunc(100, world_timer, 1);
	glutMainLoop();

}

