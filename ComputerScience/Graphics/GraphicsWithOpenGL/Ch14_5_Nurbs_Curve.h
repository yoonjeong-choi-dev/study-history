#pragma once
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
//#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
//#pragma comment(linker, "/ENTRY:mainCRTStartup")

// �������� ���� ����ġ �迭
static GLfloat weightControlPoints[4][4] = {
	{ 4.0, 4.0, 4.0, 4.0 },
	{ 4.0, 4.0, 4.0, 4.0 },
	{ 4.0, 4.0, 4.0, 4.0 },
	{ 4.0, 4.0, 4.0, 4.0 }
};
// �������� ȭ��� ��ġ 
// controlPointsCoordi[i][j][x/y/z] = (i,j)��° �������� x/y/z ��ǥ
static GLfloat controlPointsCoordi[4][4][4];
// ������ �迭 
// controlPoints[i][j][x/y/z]
static GLfloat controlPoints[4][4][4];
// ��Ʈ ����
GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
// �ʺ꽺 ��ü
static GLUnurbsObj *theNurbs = nullptr;

// ȭ�� ũ�� ����
GLint width = 300, height = 300;

// ������ ��
GLfloat point_mat_diffuse[] = { 1.0, 0.5, 1.0, 1.0 };
GLfloat point_mat_specular[] = { 0.8, 0.0, 0.8, 0.0 };
GLfloat point_mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat point_mat_shininess[] = { 30.0 };

//����� ��
GLfloat surface_mat_diffuse[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat surface_mat_specular[] = { 0.8, 0.0, 0.8, 0.0 };
GLfloat surface_mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat surface_mat_shininess[] = { 30.0 };


// ȸ�� ����
GLfloat theta_x = 45.0f;

void InitSurfaceWithControlPoints() {
	int s, t;
	
	// ������ ��ġ �ʱ�ȭ
	for (s = 0; s < 4; s++) {
		for (t = 0; t < 4; t++) {
			controlPointsCoordi[s][t][0] = 2.0*((GLfloat)s - 1.5);
			controlPointsCoordi[s][t][2] = 2.0*((GLfloat)t - 1.5);

			if ((s == 1 || s == 2) && (t == 1 || t == 2)) {
				controlPointsCoordi[s][t][1] = 3.0;
			}
			else {
				controlPointsCoordi[s][t][1] = -3.0;
			}

			for (int k = 0; k < 3; k++) {
				// ������ ���� �ʱ�ȭ
				controlPoints[s][t][k] = weightControlPoints[s][t] * controlPointsCoordi[s][t][k];
			}

			controlPoints[s][t][3] = weightControlPoints[s][t];
		}
	}
}

void CreateSurface() {
	if (theNurbs != nullptr) {
		gluDeleteNurbsRenderer(theNurbs);
	}

	// �÷� �ʱ�ȭ
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// �־��� �������� ���� ��� ����
	glEnable(GL_AUTO_NORMAL);
	InitSurfaceWithControlPoints();
	theNurbs = gluNewNurbsRenderer();
	
	
}

void InitLight() {
	// ���� ��ġ ����
	GLfloat light0_pos[] = { 3.0, 1.0,1.0,1.0 };
	GLfloat light1_pos[] = { -3.0,1.0,1.0,1.0 };

	// ���� �� ����
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);

	// ���� ��ġ ����
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

	// ���� ��� �� ���� Ȱ��ȭ
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// ���� ���� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);

	// �÷� �ʱ�ȭ
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// �־��� �������� ���� ��� ����
	CreateSurface();
}


void MyReshape(GLint w, GLint h) {
	width = w;
	height = h;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(33.0, (GLfloat)w / (GLfloat)h, 3.0, 20.0);
}

void MyDisplay() {

	// �������� ���� ��� ����
	CreateSurface();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -15.0);

	// ��ü ��
	glPushMatrix();
	glRotatef(theta_x, 1.0, 0.0, 0.0);

	// ������ ��ġ ǥ���ϱ�
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// �� �������� ȭ�鿡 ��Ÿ���� ���ؼ�
			glPushMatrix();

			// ������ �� ����
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, point_mat_diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, point_mat_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, point_mat_emission);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, point_mat_shininess);

			glPointSize(5.0);
			glBegin(GL_POINT);
			glVertex3f(
				controlPointsCoordi[i][j][0],
				controlPointsCoordi[i][j][1],
				controlPointsCoordi[i][j][2]
			);
			glEnd();

			glPopMatrix();
		}
	}

	// �������� ���� ��� ���� ǥ���ϱ�
	glPushMatrix();

	// y�� ���� : x�� ����
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			glBegin(GL_LINES);
			glVertex3f(
				controlPointsCoordi[i][j][0],
				controlPointsCoordi[i][j][1],
				controlPointsCoordi[i][j][2]);
			glVertex3f(
				controlPointsCoordi[i][j + 1][0],
				controlPointsCoordi[i][j + 1][1],
				controlPointsCoordi[i][j + 1][2]);
			glEnd();
		}
	}
	// x�� ���� : y�� ����
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			glBegin(GL_LINES);
			glVertex3f(
				controlPointsCoordi[i][j][0],
				controlPointsCoordi[i][j][1],
				controlPointsCoordi[i][j][2]);
			glVertex3f(
				controlPointsCoordi[i + 1][j][0],
				controlPointsCoordi[i + 1][j][1],
				controlPointsCoordi[i + 1][j][2]);
			glEnd();
		}
	}
	glPopMatrix();

	// ��� �׸���
	glPushMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, surface_mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, surface_mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, surface_mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, surface_mat_shininess);

	gluBeginSurface(theNurbs);
	gluNurbsSurface(theNurbs, 8, knots, 8, knots, 4 * 4, 4,
		&controlPoints[0][0][0], 4, 4, GL_MAP2_VERTEX_4);
	gluEndSurface(theNurbs);

	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}


void PrintWeightOfControlPoints() {
	printf("[ Current Control Point Weight ] \n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%f ", weightControlPoints[i][j]);
		}
		printf("\n");
	}
}


void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				weightControlPoints[i][j] += 1.0f;
			}
		}
		PrintWeightOfControlPoints();
		glutPostRedisplay();
		break;
	case 'a':
		if (weightControlPoints[0][0] <= 0.0f) {
			break;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				weightControlPoints[i][j] -= 1.0f;
			}
		}
		PrintWeightOfControlPoints();
		glutPostRedisplay();
		break;
	case 'w':
		theta_x -= 10.0f;
		glutPostRedisplay();
		break;
	case 's':
		theta_x += 10.0f;
		glutPostRedisplay();
		break;
		break;
	case 'q':
		exit(0);
		break;
	}
}

void NurbsSurfaceExample() {
	PrintWeightOfControlPoints();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("NURBS Surface Example");
	InitLight();
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
}