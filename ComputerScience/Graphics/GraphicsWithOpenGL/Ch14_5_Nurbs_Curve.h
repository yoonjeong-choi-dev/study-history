#pragma once
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
//#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
//#pragma comment(linker, "/ENTRY:mainCRTStartup")

// 제어점에 대한 가중치 배열
static GLfloat weightControlPoints[4][4] = {
	{ 4.0, 4.0, 4.0, 4.0 },
	{ 4.0, 4.0, 4.0, 4.0 },
	{ 4.0, 4.0, 4.0, 4.0 },
	{ 4.0, 4.0, 4.0, 4.0 }
};
// 제어점의 화면상 위치 
// controlPointsCoordi[i][j][x/y/z] = (i,j)번째 제어점의 x/y/z 좌표
static GLfloat controlPointsCoordi[4][4][4];
// 제어점 배열 
// controlPoints[i][j][x/y/z]
static GLfloat controlPoints[4][4][4];
// 나트 벡터
GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
// 너브스 객체
static GLUnurbsObj *theNurbs = nullptr;

// 화면 크기 관련
GLint width = 300, height = 300;

// 제어점 색
GLfloat point_mat_diffuse[] = { 1.0, 0.5, 1.0, 1.0 };
GLfloat point_mat_specular[] = { 0.8, 0.0, 0.8, 0.0 };
GLfloat point_mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat point_mat_shininess[] = { 30.0 };

//곡면의 색
GLfloat surface_mat_diffuse[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat surface_mat_specular[] = { 0.8, 0.0, 0.8, 0.0 };
GLfloat surface_mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat surface_mat_shininess[] = { 30.0 };


// 회전 관련
GLfloat theta_x = 45.0f;

void InitSurfaceWithControlPoints() {
	int s, t;
	
	// 제어점 위치 초기화
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
				// 제어점 정보 초기화
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

	// 컬러 초기화
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// 주어진 제어점에 대한 곡면 생성
	glEnable(GL_AUTO_NORMAL);
	InitSurfaceWithControlPoints();
	theNurbs = gluNewNurbsRenderer();
	
	
}

void InitLight() {
	// 광원 위치 설정
	GLfloat light0_pos[] = { 3.0, 1.0,1.0,1.0 };
	GLfloat light1_pos[] = { -3.0,1.0,1.0,1.0 };

	// 광원 모델 설정
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);

	// 광원 위치 설정
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

	// 광원 모드 및 광원 활성화
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// 깊이 버퍼 활성화
	glEnable(GL_DEPTH_TEST);

	// 컬러 초기화
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// 주어진 제어점에 대한 곡면 생성
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

	// 제어점에 대한 곡면 생성
	CreateSurface();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -15.0);

	// 전체 모델
	glPushMatrix();
	glRotatef(theta_x, 1.0, 0.0, 0.0);

	// 제어점 위치 표시하기
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 각 제어점을 화면에 나타내기 위해서
			glPushMatrix();

			// 제어점 색 설정
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

	// 제어점을 통한 경계 선분 표시하기
	glPushMatrix();

	// y축 방향 : x축 고정
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
	// x축 방향 : y축 고정
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

	// 곡면 그리기
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