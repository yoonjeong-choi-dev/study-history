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

	// 윈도우 설정
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(700, 400);
	glutCreateWindow("Flight Simulation");

	// 콜백함수등록
	glutReshapeFunc(FlightSimulator::Reshape);
	glutDisplayFunc(FlightSimulator::Display);
	glutIdleFunc(FlightSimulator::Idle);
	glutKeyboardFunc(FlightSimulator::Keyboard);
	glutKeyboardUpFunc(FlightSimulator::KeyboardUp);

	// 깊이버퍼 및 후면제거 활성화
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	terrain = new Terrain(terrainHeightFile, terrainSurfaceFile, 257, 257);
	skybox = new Skybox();

	// 카메라 객체 설정
	cam = Camera();
	cam.set(4, 4, 4, 0, 0, 0, 0, 1, 0);
	cam.setShape(60.0f, 64.0f / 48.0f, 0.5f, 1000.0f);

	// 카메라의 초기 위치와 회전각 설정
	cam.slide(0, 100, 0);
	cam.roll(0);
	cam.yaw(180);
	cam.pitch(45);

	atexit(FlightSimulator::dispose);
	printf("W: foward S: backwad A: left D: right\n");
	printf("JL: roll - 비행기 자체를 회전 시킬때 사용\n");
	printf("IK: pitch - 비행기 높이 조절을 할때 사용\n");
	printf("QE: yaw - 비행기 방향 조절을 할때 사용\n\n");
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

	// 카메라 위치 반영 후 하늘을 그린다
	glPushMatrix();
	glTranslatef(cam.eye.x, cam.eye.y, cam.eye.z);
	skybox->draw();
	glPopMatrix();

	// 높이에 대해서 rescale 해준다
	glScalef(1.0f, 0.2f, 1.0f);

	//카메라 위치에서의 지형을 그린다(거리에 따른 lod를 차이나게 하기 위함)
	glPushMatrix();
	terrain->RenderTerrain(cam.eye.x, cam.eye.z);
	glPopMatrix();

	// 안개 효과
	fog();

	glFlush();
	glutSwapBuffers();
}

void FlightSimulator::Idle() {
	if (keyPressed['1'])
		glPolygonMode(GL_FRONT, GL_LINE);
	if (keyPressed['2'])
		glPolygonMode(GL_FRONT, GL_FILL);

	// 전후 이동
	if (keyPressed['d']) { 
		cam.slide(delta_slide_side, 0, 0);
	}
	if (keyPressed['a']) {
		cam.slide(-delta_slide_side, 0, 0);
	}

	// 좌우 이동
	if (keyPressed['s']) { 
		cam.slide(0, 0, delta_slide_forward);
	}
	if (keyPressed['w']) { 
		cam.slide(0, 0, -delta_slide_forward);
	}

	// 간단한 Colision Detection 지표면 아래로 카메라가 내려갈때는 지표면 위로 유지시킴
	if (cam.eye.y < terrain->getHeight(cam.eye.x, cam.eye.z)) {
		cam.slide(0, 1.0, 0); 
	}


	// 피치 : 비행기 높이 조절을 할때 사용
	if (keyPressed['k']) { 
		cam.pitch(delta_pitch);
	}
	if (keyPressed['i']) { 
		cam.pitch(-delta_pitch); 
	}

	// 요 : 비행기 방향 조절을 할때 사용
	if (keyPressed['q']) { 
		cam.yaw(-delta_yaw);
	}
	if (keyPressed['e']) { 
		cam.yaw(delta_yaw);
	}

	// 롤 : 비행기 자체를 회전 시킬때 사용
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
	// 안개 효과
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);	// 안개 함수 설정 : 거리에 대한 농도 함수

	
	GLfloat waterFogColor[4] = { 0.0,0.6,0.6,5.0 };
	GLfloat fogColor[4] = { 0.75,0.75,0.75,0.0 };

	// 물 속에 있는 경우 : Y좌표가 waterLevel보다 작음
	if (cam.eye.y < (terrain->waterLevel - 75)) {
		// 안개 색상 및 거리를 변경하여 물속처럼 보이게 함
		glFogfv(GL_FOG_COLOR, waterFogColor);
		glFogf(GL_FOG_DENSITY, 0.075);
	}
	else {
		// 안개 색상 및 거리를 변경하여 물밖처럼 보이게 함
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.001);
	}
}