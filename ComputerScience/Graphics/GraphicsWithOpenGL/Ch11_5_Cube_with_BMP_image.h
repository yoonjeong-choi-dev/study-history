#pragma once
#include <GL/glut.h>
#include <GL/GLAUX.H>
#include <stdio.h>
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

// 회전 값 관련 변수
GLfloat xRot, yRot, zRot;
const GLfloat delta_xRot = 0.3f, delta_yRot = 0.2f, delta_zRot = 0.4f;

// 텍스처 관련 변수
unsigned int textureObject[1];
// 외부 이미지를 텍스터로 저장한 저장공간의 포인터
AUX_RGBImageRec *pTextureImage[1];

// 애니메이션 관련
unsigned int animation_interval = 50;

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0, 0.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 텍스처 객체 선택
	glBindTexture(GL_TEXTURE_2D, textureObject[0]);

	// 육면체 그리기 & 수동 텍스처 매핑(각 정점의 텍스터 좌표를 설정)
	glBegin(GL_QUADS);

	// 앞면
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	// 뒷면
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

	// 윗면
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	// 아래면
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

	// 오른쪽 면
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	// 왼쪽 면
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glEnd();
	glutSwapBuffers();
}


void MyTimer(int val) {

	// x,y,z 축으로 해당 값만큼 회전시킴
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	// x,y,z축 회전값 업데이트
	xRot += delta_xRot;
	yRot += delta_yRot;
	zRot += delta_zRot;

	glutPostRedisplay();
	glutTimerFunc(animation_interval, MyTimer, 1);
}


void MyKeyboard(unsigned char keyPressed, int x, int y) {
	switch (keyPressed) {
	case 'q':
	case 'Q':
	case 27:
		exit(0);
		break;
	}
}

// 파일을 메모리에 저장하는 함수
AUX_RGBImageRec *LoadBMP(char *szFilename) {
	FILE* pFile = NULL;

	if (!szFilename) {
		return NULL;
	}

	pFile = fopen(szFilename, "r");
	if (pFile) {
		fclose(pFile);
		return auxDIBImageLoad(szFilename);
	}
	return NULL;
}

// 파일을 메모리에서 텍스처 메모리로 할당하는 함수
int LoadGLTextures(char* szFilePath) {
	int status = FALSE;

	glClearColor(0.0, 0.0, 0.0, 0.5);

	// 포인터를 널로 만든다
	memset(pTextureImage, 0, sizeof(void*) * 1);

	// 비트맵 파일을 텍스처로 로드하고 오류 확인
	if (pTextureImage[0] = LoadBMP(szFilePath)) {
		status = TRUE;

		// 텍스처 객체 생성
		glGenTextures(1, &textureObject[0]);

		// 텍스처 객체 설정
		glBindTexture(GL_TEXTURE_2D, textureObject[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
			pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE,
			pTextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}

	// 이미 텍스처가 존재하는 경우 텍스처 메모리 반환
	if (pTextureImage[0]) {
		// 텍스처 영상이 존재하는 경우
		if (pTextureImage[0]->data) {
			free(pTextureImage[0]->data);
		}
		free(pTextureImage[0]);
	}

	return status;
}


void Cube_with_BMP_image_example() {
	int choice;
	char* img_list[] = {
		"bmp_img/water.bmp",
		"bmp_img/sky.bmp",
		"bmp_img/snow.bmp",
		"bmp_img/mountain.bmp",
		"bmp_img/apple.bmp"
	};


	printf("1.water 2.sky 3.snow 4.mountain 5.apple\n");
	printf("Choose the image : ");
	scanf("%d", &choice);

	if (choice > 5 || choice < 0) {
		printf("Wrong input");
		return;
	}

	choice--;


	glutInitWindowSize(500, 500);
	glutInitWindowPosition(700, 400);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Cube with bmp image");

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(animation_interval, MyTimer, 1);

	// 텍스처 불러오기
	if (LoadGLTextures(img_list[choice])) {
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		glClearDepth(1.0);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glutMainLoop();
	}
	else {
		printf("Wrong image source path\n");
	}

}
