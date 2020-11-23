#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


// 물체의 확산 반사,경면 반사 
GLfloat mat_diffuse[] = { 0.25, 0.25, 1.0, 0.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.0 };
// 광원의 위치
GLfloat light_position[] = { 10.0, 10.0, 20.0, 1.0 };
// 물체 포인터 : GLUT 대신 GLU를 사용하여 물체를 그리기 위한 변수
GLUquadricObj *qObj;


//■■■■■■■■■■■■■■■■  텍스처 관련  ■■■■■■■■■■■■■■■■
#define numTextureObject 3
// 텍스처 기준 평면 : glTexGenfv() 사용을 위한 함수
GLfloat ref_plane[] = { 1.5, 1.5, 1.5, 0.0 };
// 텍스처 객체
unsigned int myTextureObject[numTextureObject];
int curIdx = 0;
#define stripeImageWidth 32
GLubyte stripeImage[4 * stripeImageWidth];	//텍스처 배열

										  // true : 텍스처로 대체, false : MODULATE - 물체와 텍스처 색의 곱
bool texture_evn_replace_mode = true;


// 텍스처 생성
void GenerateTexture() {
	for (int i = 0; i < stripeImageWidth; i++) {
		stripeImage[4 * i] = 255;
		stripeImage[4 * i + 1] = (i < 8) ? 0 : 255;
		stripeImage[4 * i + 2] = (i < 8) ? 0 : 255;
		stripeImage[4 * i + 3] = 0;
	}
}


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// myTextureObject를 현재 텍스처 객체로 설정 후 물체 그림
	glBindTexture(GL_TEXTURE_1D, myTextureObject[curIdx]);
	gluSphere(qObj, 1.5, 40, 40);
	glutSwapBuffers();

}

void Init() {

	// 물체 객체 생성 및 초기 설정
	qObj = gluNewQuadric();
	gluQuadricDrawStyle(qObj, GLU_FILL);

	// 물체 특성 셋팅
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);

	// 조명 기능, 광원 활성화 및 셋팅
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// 깊이 버퍼 활성화
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);

	// 텍스처 배열 생성
	GenerateTexture();
	glGenTextures(numTextureObject, myTextureObject);

	for (int i = 0; i < numTextureObject; i++) {
		// 현재 텍스처 객체 설정
		glBindTexture(GL_TEXTURE_1D, myTextureObject[i]);

		// 1. 텍스처 영상 명시
		glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, stripeImage);

		// 2. 자동 매핑 방법
		// 텍스처 s좌표  : linear - 기준 평면과 물체면 정점간의 거리에 의해 달당
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		// 텍스처 s좌표 : GL_OBJECT_PLANE - 물체 정점과 기준 평면 모두 모델 좌표계 기준
		glTexGenfv(GL_S, GL_OBJECT_PLANE, ref_plane);

		// 3. 텍스처 파라미터 명시 : 어떻게 확장시키고, 어떤 방식으로 계산하는지 결정
		glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// 4. 텍스처 환경 명시 : 물체 색과 텍스처 색의 조합 방법
		if (i == 0) {
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		}
		else if (i == 1) {
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
		else {
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		}

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_1D);
	}

}


void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40., (GLfloat)w / (GLfloat)h, 1., 10.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glTranslatef(0., 0., -1.);
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		curIdx = (curIdx + 1) % numTextureObject;
		printf("cur idx: %d\n", curIdx);
		glutPostRedisplay();
		break;
	case 's':
		curIdx = (numTextureObject + curIdx - 1) % numTextureObject;
		printf("cur idx: %d\n", curIdx);
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
	}
}


void textureOnSphere(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(700, 400);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Sphere with some textures");

	glutKeyboardFunc(MyKeyboard);
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(MyDisplay);

	Init();

	glutMainLoop();
}