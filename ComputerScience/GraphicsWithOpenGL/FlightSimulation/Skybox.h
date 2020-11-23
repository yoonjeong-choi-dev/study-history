#pragma once
/*
Skybox.h
- �ܺ� ������ �ѷ��δ� ��ī�̹ڽ��� �������ϴ� Ŭ���� ����
- ����� �ֺ��� ��� �ϴ��� �����ϴ� ��
- ��Ʈ�� ���� 6���� �ؽ�ó �������� ����ü ���θ� ������
	- ��� �� ������ ��� �κ�(Seam)������ ������ �ڿ������� �̾������� ���� ���� �ʿ�
	- �ڽ� ���ο��� ���� �ٶ󺸰� �����Ƿ� GLFrontFace(GL_CW)�� ���� �ʿ�
- ��� ������ �׻� ���ȭ�鿡 �ѷ����� �Ѵ�
	- ���� ���۸� ��Ȱ��ȭ �� �� ��ī�̹ڽ��� �׸���
	- Z ���� ���꿡�� ��ī�̹ڽ� ������ ������� �ʾ� ���ȭ�� ȿ���� ��Ÿ��
*/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/GLAUX.H>
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#define TEXURE_SIZE 3
#define GL_CLAMP_TO_EDGE 0x812F	//EDGE�� �������� ��踦 Ȯ��



class Skybox {
public:
	Skybox();
	~Skybox();
	void draw();

private:
	// ����ü�� �� �鿡 ���� �ؽ�ó ���� ����
	const char *textureFile[6] = {
		"FlightSimulationSource/front.bmp",
		"FlightSimulationSource/back.bmp",
		"FlightSimulationSource/left.bmp",
		"FlightSimulationSource/right.bmp",
		"FlightSimulationSource/up.bmp",
		"FlightSimulationSource/down.bmp"
	};

	typedef unsigned int uint;
	typedef const char* pcStr;
	uint textures[6];			// ����ü�� �� ���� �ؽ�ó id

	// �ؽ�ó ������ ���� ������ �ҷ����� �Լ�
	static uint _loadTexture(pcStr filename);
};