#pragma once
/*
FlightSimulator.h
- ����� �ùķ��̼��� �ϱ� ���� �ùķ�����

< �䱸 ���� > 
- ������� ���� �̵� �� Roll/Pitch/Yaw ȿ�� ����
- �ܺ� ������ �ѷ��δ� ��ī�̹ڽ�
- ���� �𵨸�
- ȣ�� �贩������ ���� ȿ��
- ����⿡�� �̻��� �߻� �� �浹 Ž���� ���� ������ ����/������ ������� ������ ��ƼŬ �ý������� ǥ��
*/

#include <stdio.h>
#include <math.h>
#include "Terrain.h"
#include "Skybox.h"
#include <GL/GLAUX.H>
#include <gl/glut.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

class FlightSimulator {
private:
	static Terrain* terrain;		//���� ��ü
	static Skybox* skybox;		//��ī�̹ڽ� ��ü
	static Camera cam;			//ī�޶� ��ü
	static bool keyPressed[256];	// Ű���� ���� 

	// ���� ��� ����
	static const char *terrainHeightFile;
	static const char *terrainSurfaceFile;

	// �̵� �� ȸ���� ���� ��� ���� 
	static const double delta_slide_forward;
	static const double delta_slide_side;
	static const float delta_pitch;
	static const float delta_yaw;
	static const float delta_roll;

private:
	static void dispose();		// ����� ����
	static void Display();		// display �ݹ�
	static void Idle();		// idle �ݹ�
	static void Reshape(int w, int h);	// reshape �ݹ�
	static void Keyboard(unsigned char key, int x, int y);		//keyboard �ݹ�
	static void KeyboardUp(unsigned char key, int x, int y);	//keyboardUp �ݹ�
	static void fog();
public:
	static int run();			// ���� �Լ�
};

