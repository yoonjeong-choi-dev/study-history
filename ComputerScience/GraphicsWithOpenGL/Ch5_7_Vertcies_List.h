#pragma once
#include <GL/glut.h>


/*
Example 1 : Drawing a hexahedron
*/

// 육면체의 8개 정점의 (x,y,z) 좌표
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

// 육면체 8개의 정점의 (R,G,B) 색상
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

// 육면체 각 면(face)의 outer-face의 counter-clockwise 정점 정보
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

	// 각 표면에 대한 vertex 순서가 시계 반대 방향
	glFrontFace(GL_CCW);

	// 시점과 상관없는 면 제거
	glEnable(GL_CULL_FACE);

	// 정점 배열 기능 활성화
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// 정점 배열 기능 활성화 후 해당 배열들 저장
	glColorPointer(3, GL_FLOAT, 0, MyHexadronColors);
	glVertexPointer(3, GL_FLOAT, 0, MyHexadronVertices);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// (1,1,1)을 회전축으로 30도 반시계방향으로 회전
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