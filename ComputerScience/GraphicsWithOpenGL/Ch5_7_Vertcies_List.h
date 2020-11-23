#pragma once
#include <GL/glut.h>


/*
Example 1 : Drawing a hexahedron
*/

// ����ü�� 8�� ������ (x,y,z) ��ǥ
GLfloat MyHexadronVertices[8][3] = {
	{ -0.25, -0.25, 0.25 },
	{ -0.25, 0.25, 0.25 },
	{ 0.25, 0.25, 0.25 },
	{ 0.25, -0.25, 0.25 },
	{ -0.25, -0.25, -0.25 },
	{ -0.25, 0.25, -0.25 },
	{ 0.25, 0.25, -0.25 },
	{ 0.25, -0.25, -0.25 }
};

// ����ü 8���� ������ (R,G,B) ����
GLfloat MyHexadronColors[8][3] = {
	{ 0.2, 0.2, 0.2 },
	{ 1.0, 0.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ 1.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 0.0, 1.0, 1.0 }
};

// ����ü �� ��(face)�� outer-face�� counter-clockwise ���� ����
GLubyte MyHexadronVertexList[24] = {
	0, 3, 2, 1,
	2, 3, 7, 6,
	0, 4, 7, 3,
	1, 2, 6, 5,
	4, 5, 6, 7,
	0, 1, 5, 4
};


void MyHexadronDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	// �� ǥ�鿡 ���� vertex ������ �ð� �ݴ� ����
	glFrontFace(GL_CCW);

	// ������ ������� �� ����
	glEnable(GL_CULL_FACE);

	// ���� �迭 ��� Ȱ��ȭ
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// ���� �迭 ��� Ȱ��ȭ �� �ش� �迭�� ����
	glColorPointer(3, GL_FLOAT, 0, MyHexadronColors);
	glVertexPointer(3, GL_FLOAT, 0, MyHexadronVertices);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// (1,1,1)�� ȸ�������� 30�� �ݽð�������� ȸ��
	glRotatef(100.0, 1.0, 1.0, 1.0);

	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyHexadronVertexList[4 * i]);
	}
	glFlush();
}

void MyHexadronExample(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowSize(300, 300);
	glutInitWindowPosition(700, 400);
	glutCreateWindow("Draw a hexadron");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyHexadronDisplay);
	glutMainLoop();

}