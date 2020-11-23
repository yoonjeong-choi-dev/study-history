#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


// ��ü�� Ȯ�� �ݻ�,��� �ݻ� 
GLfloat mat_diffuse[] = { 0.25, 0.25, 1.0, 0.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.0 };
// ������ ��ġ
GLfloat light_position[] = { 10.0, 10.0, 20.0, 1.0 };
// ��ü ������ : GLUT ��� GLU�� ����Ͽ� ��ü�� �׸��� ���� ����
GLUquadricObj *qObj;


//�����������������  �ؽ�ó ����  �����������������
#define numTextureObject 3
// �ؽ�ó ���� ��� : glTexGenfv() ����� ���� �Լ�
GLfloat ref_plane[] = { 1.5, 1.5, 1.5, 0.0 };
// �ؽ�ó ��ü
unsigned int myTextureObject[numTextureObject];
int curIdx = 0;
#define stripeImageWidth 32
GLubyte stripeImage[4 * stripeImageWidth];	//�ؽ�ó �迭

										  // true : �ؽ�ó�� ��ü, false : MODULATE - ��ü�� �ؽ�ó ���� ��
bool texture_evn_replace_mode = true;


// �ؽ�ó ����
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

	// myTextureObject�� ���� �ؽ�ó ��ü�� ���� �� ��ü �׸�
	glBindTexture(GL_TEXTURE_1D, myTextureObject[curIdx]);
	gluSphere(qObj, 1.5, 40, 40);
	glutSwapBuffers();

}

void Init() {

	// ��ü ��ü ���� �� �ʱ� ����
	qObj = gluNewQuadric();
	gluQuadricDrawStyle(qObj, GLU_FILL);

	// ��ü Ư�� ����
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);

	// ���� ���, ���� Ȱ��ȭ �� ����
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// ���� ���� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);

	// �ؽ�ó �迭 ����
	GenerateTexture();
	glGenTextures(numTextureObject, myTextureObject);

	for (int i = 0; i < numTextureObject; i++) {
		// ���� �ؽ�ó ��ü ����
		glBindTexture(GL_TEXTURE_1D, myTextureObject[i]);

		// 1. �ؽ�ó ���� ���
		glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, stripeImage);

		// 2. �ڵ� ���� ���
		// �ؽ�ó s��ǥ  : linear - ���� ���� ��ü�� �������� �Ÿ��� ���� �޴�
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		// �ؽ�ó s��ǥ : GL_OBJECT_PLANE - ��ü ������ ���� ��� ��� �� ��ǥ�� ����
		glTexGenfv(GL_S, GL_OBJECT_PLANE, ref_plane);

		// 3. �ؽ�ó �Ķ���� ��� : ��� Ȯ���Ű��, � ������� ����ϴ��� ����
		glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// 4. �ؽ�ó ȯ�� ��� : ��ü ���� �ؽ�ó ���� ���� ���
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