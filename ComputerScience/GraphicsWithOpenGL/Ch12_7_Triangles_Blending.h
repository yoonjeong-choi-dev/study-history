#pragma once
#include <GL/glut.h>
#include <GL/GLAUX.H>
#include <stdio.h>



GLfloat triangle_alpha = 0.2;
GLboolean oneTriangleMode = true;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLES);
	if (oneTriangleMode) {
		glColor4f(1.0, 1.0, 0.0, triangle_alpha);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.0, 0.5, 0.0);
	}
	else {
		glColor4f(1.0, 1.0, 0.0, 1.0);
		glVertex3f(-0.75, -0.5, 0.0);
		glVertex3f(0.25, -0.5, 0.0);
		glVertex3f(-0.25, 0.5, 0.0);

		glColor4f(1.0, 0.0, 0.0, triangle_alpha);
		glVertex3f(-0.25, -0.5, 1.0);
		glVertex3f(0.75, -0.5, 1.0);
		glVertex3f(0.25, 0.5, 1.0);
	}

	glEnd();

	glDisable(GL_BLEND);
	glFlush();
}


void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		triangle_alpha += 0.1;
		if (triangle_alpha > 1.0) {
			triangle_alpha = 0.0;
		}
		glutPostRedisplay();
		break;
	case 's':
		triangle_alpha -= 0.1;
		if (triangle_alpha < 0.0) {
			triangle_alpha = 1.0;
		}
		glutPostRedisplay();
		break;
	case 'a':
	case 'd':
		oneTriangleMode = !oneTriangleMode;
		glutPostRedisplay();
		break;
	case 'q':
		exit(0);
		break;
	}
}

void TrianglesBlendingExample() {
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(700, 400);

	glutCreateWindow("Triangles Blending");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);

	glutMainLoop();
}