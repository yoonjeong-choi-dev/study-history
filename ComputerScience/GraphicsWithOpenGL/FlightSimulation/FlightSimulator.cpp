#include "FlightSimulator.h"

bool FlightSimulator::keyPressed[256] = { false };

const char* FlightSimulator::terrainHeightFile = "FlightSimulationSource/terrain1.raw";
const char* FlightSimulator::terrainSurfaceFile = "FlightSimulationSource/snow512.bmp";
const double FlightSimulator::delta_slide_forward = 1.0;
const double FlightSimulator::delta_slide_side = 0.2;
const float FlightSimulator::delta_pitch = 0.5;
const float FlightSimulator::delta_yaw = 0.5;
const float FlightSimulator::delta_roll = 0.5;

Terrain* FlightSimulator::terrain = nullptr;
Skybox* FlightSimulator::skybox = nullptr;
Camera FlightSimulator::cam;

int FlightSimulator::run() {
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	// ������ ����
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(700, 400);
	glutCreateWindow("Flight Simulation");

	// �ݹ��Լ����
	glutReshapeFunc(FlightSimulator::Reshape);
	glutDisplayFunc(FlightSimulator::Display);
	glutIdleFunc(FlightSimulator::Idle);
	glutKeyboardFunc(FlightSimulator::Keyboard);
	glutKeyboardUpFunc(FlightSimulator::KeyboardUp);

	// ���̹��� �� �ĸ����� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	terrain = new Terrain(terrainHeightFile, terrainSurfaceFile, 257, 257);
	skybox = new Skybox();

	// ī�޶� ��ü ����
	cam = Camera();
	cam.set(4, 4, 4, 0, 0, 0, 0, 1, 0);
	cam.setShape(60.0f, 64.0f / 48.0f, 0.5f, 1000.0f);

	// ī�޶��� �ʱ� ��ġ�� ȸ���� ����
	cam.slide(0, 100, 0);
	cam.roll(0);
	cam.yaw(180);
	cam.pitch(45);

	atexit(FlightSimulator::dispose);
	printf("W: foward S: backwad A: left D: right\n");
	printf("JL: roll - ����� ��ü�� ȸ�� ��ų�� ���\n");
	printf("IK: pitch - ����� ���� ������ �Ҷ� ���\n");
	printf("QE: yaw - ����� ���� ������ �Ҷ� ���\n\n");
	printf("1,2: solid, wire rendering\n");
	glutMainLoop();

	return 0;
}

void FlightSimulator::dispose() {
	delete terrain;
	delete skybox;
	delete &cam;
}

void FlightSimulator::Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// ī�޶� ��ġ �ݿ� �� �ϴ��� �׸���
	glPushMatrix();
	glTranslatef(cam.eye.x, cam.eye.y, cam.eye.z);
	skybox->draw();
	glPopMatrix();

	// ���̿� ���ؼ� rescale ���ش�
	glScalef(1.0f, 0.2f, 1.0f);

	//ī�޶� ��ġ������ ������ �׸���(�Ÿ��� ���� lod�� ���̳��� �ϱ� ����)
	glPushMatrix();
	terrain->RenderTerrain(cam.eye.x, cam.eye.z);
	glPopMatrix();

	// �Ȱ� ȿ��
	fog();

	glFlush();
	glutSwapBuffers();
}

void FlightSimulator::Idle() {
	if (keyPressed['1'])
		glPolygonMode(GL_FRONT, GL_LINE);
	if (keyPressed['2'])
		glPolygonMode(GL_FRONT, GL_FILL);

	// ���� �̵�
	if (keyPressed['d']) { 
		cam.slide(delta_slide_side, 0, 0);
	}
	if (keyPressed['a']) {
		cam.slide(-delta_slide_side, 0, 0);
	}

	// �¿� �̵�
	if (keyPressed['s']) { 
		cam.slide(0, 0, delta_slide_forward);
	}
	if (keyPressed['w']) { 
		cam.slide(0, 0, -delta_slide_forward);
	}

	// ������ Colision Detection ��ǥ�� �Ʒ��� ī�޶� ���������� ��ǥ�� ���� ������Ŵ
	if (cam.eye.y < terrain->getHeight(cam.eye.x, cam.eye.z)) {
		cam.slide(0, 1.0, 0); 
	}


	// ��ġ : ����� ���� ������ �Ҷ� ���
	if (keyPressed['k']) { 
		cam.pitch(delta_pitch);
	}
	if (keyPressed['i']) { 
		cam.pitch(-delta_pitch); 
	}

	// �� : ����� ���� ������ �Ҷ� ���
	if (keyPressed['q']) { 
		cam.yaw(-delta_yaw);
	}
	if (keyPressed['e']) { 
		cam.yaw(delta_yaw);
	}

	// �� : ����� ��ü�� ȸ�� ��ų�� ���
	if (keyPressed['j']) { 
		cam.roll(delta_roll);
	}
	if (keyPressed['l']) { 
		cam.roll(-delta_roll);
	}


	else { 
		cam.slide(0, 0, 0);
	} 


	glutPostRedisplay();
}

void FlightSimulator::Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	gluPerspective(40.0, static_cast<GLdouble>(w / h), 1.0, 3000.0);
}

void FlightSimulator::Keyboard(unsigned char key, int x, int y) {
	keyPressed[key] = true;
}

void FlightSimulator::KeyboardUp(unsigned char key, int x, int y) {
	keyPressed[key] = false;
}

void FlightSimulator::fog() {
	// �Ȱ� ȿ��
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);	// �Ȱ� �Լ� ���� : �Ÿ��� ���� �� �Լ�

	
	GLfloat waterFogColor[4] = { 0.0,0.6,0.6,5.0 };
	GLfloat fogColor[4] = { 0.75,0.75,0.75,0.0 };

	// �� �ӿ� �ִ� ��� : Y��ǥ�� waterLevel���� ����
	if (cam.eye.y < (terrain->waterLevel - 75)) {
		// �Ȱ� ���� �� �Ÿ��� �����Ͽ� ����ó�� ���̰� ��
		glFogfv(GL_FOG_COLOR, waterFogColor);
		glFogf(GL_FOG_DENSITY, 0.075);
	}
	else {
		// �Ȱ� ���� �� �Ÿ��� �����Ͽ� ����ó�� ���̰� ��
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.001);
	}
}