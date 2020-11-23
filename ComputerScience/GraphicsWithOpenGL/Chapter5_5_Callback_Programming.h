#pragma once
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLint myWindowWidth = 300;
GLint myWindowHeight = 300;
GLint topLeftX, topLeftY, bottomRightX, bottomRightY;


/*
Example 1 : Reshape & Keyboard Event
*/
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);


	glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();

	glFlush();
}

void MyReshapeCallBack(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)myWindowWidth;
	GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)myWindowHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * widthFactor, 1.0 * widthFactor, -1.0 * heightFactor, 1.0 * heightFactor, -1.0, 1.0);
}

void MyKeyboardCallBack(unsigned char keyPressed, int x, int y) {
	switch (keyPressed) {
	case 'Q':
	case 'q':
	case 27:
		exit(0);
		break;

	}
}

void MyReshapeKeyboardCallBackExample(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(myWindowWidth, myWindowHeight);
	glutInitWindowPosition(700, 400);

	glutCreateWindow("Resahpe Example");

	glClearColor(0.0, 0.0, 1.0, 0.1);

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshapeCallBack);
	glutKeyboardFunc(MyKeyboardCallBack);

	glutMainLoop();
}


/*
Example 2 : Drawing a rectangle with the mouse
*/

void MyDrawingDisplay() {
	glViewport(0, 0, myWindowWidth, myWindowHeight);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_POLYGON);
	glVertex3f((GLfloat)topLeftX / (GLfloat)myWindowWidth,
		((GLfloat)myWindowHeight - (GLfloat)topLeftY) / (GLfloat)myWindowHeight,
		0.0);
	glVertex3f((GLfloat)topLeftX / (GLfloat)myWindowWidth,
		((GLfloat)myWindowHeight - (GLfloat)bottomRightY) / (GLfloat)myWindowHeight,
		0.0);
	glVertex3f((GLfloat)bottomRightX / (GLfloat)myWindowWidth,
		((GLfloat)myWindowHeight - (GLfloat)bottomRightY) / (GLfloat)myWindowHeight,
		0.0);
	glVertex3f((GLfloat)bottomRightX / (GLfloat)myWindowWidth,
		((GLfloat)myWindowHeight - (GLfloat)topLeftY) / (GLfloat)myWindowHeight,
		0.0);
	glEnd();

	glFlush();
}

void MyMouseClick(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		topLeftX = x;
		topLeftY = y;
	}
}

void MyMouseMove(GLint x, GLint y) {
	bottomRightX = x;
	bottomRightY = y;
	glutPostRedisplay();
}

void MyDrawingKeyboardCallBack(unsigned char keyPressed, int x, int y) {
	switch (keyPressed) {
	case 'q':
	case 'Q':
	case 27:
		exit(0);
		break;
	}
}

void MyDrawingReshapeCallBack(int newWidth, int newHeight) {
	myWindowWidth = newWidth;
	myWindowHeight = newHeight;

}

void MyMouseDrawExample(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(myWindowWidth, myWindowHeight);
	glutInitWindowPosition(700, 400);

	glutCreateWindow("Mouse Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDrawingDisplay);

	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);

	glutReshapeFunc(MyDrawingReshapeCallBack);
	glutKeyboardFunc(MyDrawingKeyboardCallBack);

	glutMainLoop();
}


/*
Example 3 : Make the menu
*/
GLboolean isSphere = true;
GLboolean isSmall = true;
void MyMenuDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.0, 0.5);

	if (isSphere) {
		if (isSmall)
			glutWireSphere(0.2, 15, 15);
		else
			glutWireSphere(0.4, 15, 15);
	}
	else {
		if (isSmall)
			glutWireTorus(0.1, 0.3, 40, 20);
		else
			glutWireTorus(0.2, 0.5, 40, 20);
	}
	glFlush();
}

void MyMainMenu(int entryId) {
	if (entryId == 1) {
		isSphere = true;
	}
	else if (entryId == 2) {
		isSphere = false;
	}
	else if (entryId == 3) {
		exit(0);
	}
	glutPostRedisplay();
}

void MySubMenu1(int entryId) {
	if (entryId == 1) {
		isSmall = true;
	}
	else if (entryId == 2) {
		isSmall = false;
	}
	glutPostRedisplay();
}

void MyMenuKeyboardCallBack(unsigned char keyPressed, int x, int y) {
	switch (keyPressed) {
	case 'q':
	case 'Q':
	case 27:
		exit(0);
		break;
	}
}

void MyMenuReshapeCallBack(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)myWindowWidth;
	GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)myWindowHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * widthFactor, 1.0 * widthFactor, -1.0 * heightFactor, 1.0 * heightFactor, -1.0, 1.0);
}

void MyMenuExample(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(myWindowWidth, myWindowHeight);
	glutInitWindowPosition(700, 400);

	glutCreateWindow("Menu Example");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);*/



	// Sub menu
	GLint MySubMenu1Id = glutCreateMenu(MySubMenu1);
	glutAddMenuEntry("Small size", 1);
	glutAddMenuEntry("Big size", 2);

	// Main menu 
	GLint MyMainMenuId = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Torus", 2);

	glutAddSubMenu("Change size", MySubMenu1Id);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(MyMenuDisplay);
	glutKeyboardFunc(MyMenuKeyboardCallBack);
	glutReshapeFunc(MyMenuReshapeCallBack);
	glutMainLoop();
}


/*
Example 4 : IDLE callback - animation
*/
GLfloat animation_delta = 0.0;

void MyIdleDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.5, 0.8);
	glVertex3f(-1.0 + animation_delta, -0.5, 0.0);
	glVertex3f(0.0 + animation_delta, -0.5, 0.0);
	glVertex3f(0.0 + animation_delta, 0.5, 0.0);
	glVertex3f(-1.0 + animation_delta, 0.5, 0.0);
	glEnd();

	glutSwapBuffers();
}

void MyIdleCallback() {

	if (animation_delta >= 1.0) {
		animation_delta = 0.0;
	}
	animation_delta = animation_delta + 0.001;
	glutPostRedisplay();
}

void MyIdleExample(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(myWindowWidth, myWindowHeight);
	glutInitWindowPosition(700, 400);

	glutCreateWindow("Idle Example");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);

	glutDisplayFunc(MyIdleDisplay);
	glutIdleFunc(MyIdleCallback);
	glutMainLoop();

}


/*
Example 5 : Timer callback - animation2
*/
GLfloat timer_delta = 0.0;
const GLint timer_interval = 40;
void MyTimerDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.5, 0.8);
	glVertex3f(-1.0 + timer_delta, -0.5, 0.0);
	glVertex3f(0.0 + timer_delta, -0.5, 0.0);
	glVertex3f(0.0 + timer_delta, 0.5, 0.0);
	glVertex3f(-1.0 + timer_delta, 0.5, 0.0);
	glEnd();

	glutSwapBuffers();
}

void MyTimer(int val) {
	if (timer_delta >= 1.0) {
		timer_delta = 0.0;
	}
	timer_delta = timer_delta + 0.001;
	glutPostRedisplay();
	glutTimerFunc(timer_interval, MyTimer, 1);
}

void MyTimerExample(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(myWindowWidth, myWindowHeight);
	glutInitWindowPosition(700, 400);

	glutCreateWindow("Timer Example");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);

	glutDisplayFunc(MyTimerDisplay);
	glutTimerFunc(timer_interval, MyTimer, 1);
	glutMainLoop();

}

/*
Example 6 : Timer callback2 - animation3
*/
unsigned char MY_PALLETE[16][3] = {
	{ 255,255,255 },		// WHITE
	{ 0,255,255 },		// CYAN
	{ 255,0,255 },		// PURPLE
	{ 0,0,255 },			// BLUE
	{ 192, 192, 192 },	// LIGHT GRAY
	{ 128, 128, 128 },	// DARK GRAY
	{ 0, 128, 128 },		// DARK CYAN
	{ 128,0,128 },		// DARK PURPLE
	{ 0, 0, 128 },		// DARK BLUE
	{ 255, 255, 0 },		// YELLOW
	{ 0, 255, 0 },		// GREEN
	{ 128, 128, 0 },		// DARK YELLOW
	{ 0, 128, 0 },		// DARK GREEN
	{ 255, 0, 0 },		// RED
	{ 128, 0, 0 },		// DARK RED
	{ 0,0,0 }				// BLACK
};

GLfloat timer_delta2 = 0.0;
GLint timer_idx = 0;
GLint timer_red = 0.0, timer_green = 0.0, timer_blue = 0.0;
const GLint timer_interval2 = 10;

void MyAnimationTimerDisplay() {
	timer_red = MY_PALLETE[timer_idx][0] / 255.0f;
	timer_green = MY_PALLETE[timer_idx][1] / 255.0f;
	timer_blue = MY_PALLETE[timer_idx][2] / 255.0f;

	glColor3f(timer_red, timer_green, timer_blue);

	glBegin(GL_LINES);
	glVertex3f(-1.0 + timer_delta2, 1.0, 0.0);
	glVertex3f(1.0 - timer_delta2, -1.0, 0.0);
	glVertex3f(-1.0, -1.0 + timer_delta2, 0.0);
	glVertex3f(1.0, 1.0 - timer_delta2, 0.0);
	glEnd();

	glutSwapBuffers();
}

void MyAnimationTimer(int val) {
	if (timer_delta2 < 2.0f) {
		timer_delta2 = timer_delta2 + 0.01;
	}
	else {
		timer_delta2 = 0.0;

		if (++timer_idx >= 15) {
			timer_idx = 0;
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
	glutPostRedisplay();
	glutTimerFunc(timer_interval2, MyAnimationTimer, 1);
}

void MyAnimationTimerExample(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(700, 400);

	glutCreateWindow("Animation Timer Example");
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyAnimationTimerDisplay);
	glutTimerFunc(timer_interval2, MyAnimationTimer, 1);
	glutMainLoop();
}

