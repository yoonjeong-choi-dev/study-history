#pragma once
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


#define height 4
#define width 4

GLubyte myTexture[width][height][3];

GLboolean linearInterpolationMode = true;
GLboolean repeatWrappingMode = true;

// �ؽ�ó �迭 ä���
void FillTexture() {
	int s, t;
	for (s = 0; s < width; s++) {
		for (t = 0; t < height; t++) {
			GLubyte intensity = ((s + t) % 2) * 255;
			myTexture[s][t][0] = intensity;
			myTexture[s][t][1] = intensity;
			myTexture[s][t][2] = intensity;
		}
	}
}


void MyInit() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	FillTexture();

	// ä���� �ؽ�ó �迭�� �ؽ�ó �������� ���
	// target = GL_TEXTURE_2D : 2���� �ؽ�ó ���
	// level = 0 : �Ҹ� ��� x
	// internalformat = GL_RGB : �ؼ��� ����ϴµ� ���� ���
	// border = 0 : ������ ��� x
	// format = GL_RGB : �ؽ�ó ���� ������ ������ RGB
	// type = GL_UNSIGNED_BYTE : �ؽ�ó �迭 ����� �ڷ���
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, &myTexture[0][0][0]);

	// �ؽ�ó ���� ��� �Ҵ�
	if (repeatWrappingMode) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}


	if (linearInterpolationMode) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
}


void MyDisplay() {

	MyInit();

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(0.0, 3.0); glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(3.0, 3.0); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(3.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
	glEnd();

	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'l':
		linearInterpolationMode = !linearInterpolationMode;
		glutPostRedisplay();
		break;
	case 'r':
		repeatWrappingMode = !repeatWrappingMode;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
	}
}


void TextureWrappingExample(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(700, 400);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Texture Wrapping Example");


	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
}
