#pragma once
#include <GL/glut.h>
#include <stdlib.h>

/*
Example 1 : Rotation animation
*/

GLfloat timer_theta = 0.0;
const GLfloat full_theta = 360.0;
const GLfloat delta_theta = 10.0;
const GLint timer_interval = 40;

void MyGeometricTranslationDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 300, 300);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(0.6, 0.6, 0.0);
	glRotatef(40.0 + timer_theta, 0.0, 0.0, 1.0);
	glTranslatef(0.6, 0.0, 0.0);

	glutSolidCube(0.3);

	glFlush();
}

void MyGeometricTranslationTimer(int val) {
	if (timer_theta >= full_theta) {
		timer_theta -= full_theta;
	}
	timer_theta += delta_theta;
	glutPostRedisplay();
	glutTimerFunc(timer_interval, MyGeometricTranslationTimer, 1);

}

void MyGeometricTranslationExample() {
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(700, 300);

	glutCreateWindow("Geometric Translation");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyGeometricTranslationDisplay);
	glutTimerFunc(timer_interval, MyGeometricTranslationTimer, 1);
	glutMainLoop();

}