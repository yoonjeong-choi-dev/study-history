#pragma once
#include <GL/glut.h>
#include <stdlib.h>

/*
���� ���п� ���� ������ ��Ƽ ���ϸ����
*/
void SimpleAntiAliasingDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	// ȥ�� ��� Ȱ��ȭ : ������ ��Ƽ ���ϸ������ ȥ�� �Լ� �̿�
	glEnable(GL_BLEND);

	// ȥ�� ��� ����
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// �ε巯�� �� ��� Ȱ��ȭ
	glEnable(GL_POINT_SMOOTH);

	// ������ ������ ��Ʈ�� �����ϱ� ���� ��
	// GL_POINT_SMOOTH_HINT : ���� ���� ��Ƽ ���ϸ����
	// GL_NICEST : �ӵ��� �������� ���� ���� ���� ��Ƽ ���ϸ������ ���϶�� �ǹ�
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	// ũ�� 12�� ���� �׸�
	glPointSize(12);
	glBegin(GL_POINTS);
	glVertex3f(-0.9, -0.65, 0.0);
	glEnd();

	// �ε巯�� �� ��� ��Ȱ��ȭ
	glDisable(GL_POINT_SMOOTH);

	// �ε巯�� �� ��� Ȱ��ȭ
	glEnable(GL_LINE_SMOOTH);

	// ������ ������ ��Ʈ�� �����ϱ� ���� ��
	// GL_LINE_SMOOTH_HINT : ���� ���� ��Ƽ ���ϸ����
	// GL_NICEST : �ӵ��� �������� ���� ���� ���� ��Ƽ ���ϸ������ ���϶�� �ǹ�
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// ���� �׸���
	glBegin(GL_LINES);
	glVertex3f(-1.0, -0.6, 0.0);
	glVertex3f(1.0, -0.2, 0.0);
	glVertex3f(-1.0, -0.6, 0.0);
	glVertex3f(0.75, 1.0, 0.0);
	glVertex3f(-1.0, -0.6, 0.0);
	glVertex3f(-0.75, 1.0, 0.0);
	glEnd();

	// �ε巯�� �� ��� ��Ȱ��ȭ
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
��Ƽ���ϸ���� �� ����
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
GLboolean bBlend = true;   // ȥ�� �Լ� ��� ����
GLboolean bSmooth = true;   // �ε巯�� ���� ��� ��� ����

const GLfloat rgbFactor = 255.0f;
GLfloat red = 0.0, green = 0.0, blue = 0.0;
GLint index = 0;

// rgb �ķ�Ʈ ����
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

	// ȥ�� �Լ� ��� ����
	if (bBlend) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	// �ε巯�� �� ��� ����
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
		// 16���� �ķ�Ʈ ���� ���������� ���鼭 ĥ����
		if (++index >= 15) {
			index = 0;
			glClear(GL_COLOR_BUFFER_BIT);	// ���� �ٲ𶧸��� ȭ�� �ʱ�ȭ
		}

	}
	redisplay_all();
	glutTimerFunc(100, world_timer, 1);
}


void screen_display() {
	static unsigned char buffer[128 * 128 * 4 * 2];

	// ���� ������ : world
	glutSetWindow(world);

	// ���� �������� ���� â�� �׷��� ������ ���� ������ �޸�(buffer)�� �����ϴ� �Լ�
	// ���⼭�� [0,127]*[0,127]�� ������ â�� ������ ���۸� ����
	glReadPixels(0, 0, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	// ���� ������ : screen
	glutSetWindow(screen);

	// ���� �����츦 Ȯ��
	glPixelZoom(4, 4);

	// ���� �����쿡 ������ ������ �޸�(buffer)�� ������ ���� ���
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
	case 'b':	// ȥ�� �Լ� ��� ���� ����
		bBlend = !bBlend;
		show_current_state();
		break;
	case 's':	// ������ �Լ� ��� ���� ����
		bSmooth = !bSmooth;
		show_current_state();
		break;
	case 't':	// ȥ�� �� ������ �Լ� ��� ���� ���� ����
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

