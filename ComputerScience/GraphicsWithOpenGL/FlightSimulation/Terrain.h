#pragma once
/*
Terrain.h
- �����ؽ���, ���ؽ���, �Ȱ��� �������� ����
- 2���� ������ �̿��� ��ǥ���� ������ �ο�
	- ��ο� �κ��� ���̰� ���� ���� �κ��� ���̰� ���ٰ� ����
	- �� ȭ���� ȸ������ ����� .raw ������ �̿�
- �ؽ�ó �� ���� ������ x,y���� ��ǥ���� x,z�࿡ �ش�
	- ���� ������ ȸ������ŭ ��ǥ���� y�� �������� �÷��� ������ �ش� �ؽ�ó ���� �÷� ĥ��
- ����
	- �ﰢ�� �޽��� �� ���� ���� ������ ���� ���� ���͸� ���Ͽ� ���� ����
	- ������ ���� �� ����
*/

#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <math.h>
#include <GL/glut.h>
#include <GL/GLAUX.H>
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include "Camera.h"



class Terrain {
private:
	typedef const char* pcStr;
	typedef unsigned int uint;
	typedef unsigned char ubyte;

	const char *waterTextureFile = "FlightSimulationSource/water.bmp";

	
	uint _textureId_ground, _textureId_water;	// �����ؽ��Ŀ� ���ؽ����� id
	AUX_RGBImageRec *img; // �ؽ��� �̹��� ��ü�� ����Ǵ� ������

	ubyte* _height;						// �������� �迭�� �����ϴ� ������
	GLint _map_width, _map_height;		// ���������� ���μ���ũ��
	GLuint baseTerrain;					// Ÿ���� �ε�����(���÷��� ����Ʈ)
	GLubyte minHeight;					// ������������ �ּҳ���
	
	// ���� ������(.raw) ���� �ҷ����� �Լ� : (���� ���, ���̸� ���� ũ��, ���̸� ����ũ��)
	static ubyte* readRawData(pcStr filename, uint width, uint height);

public:
	GLfloat waterLevel;		//���� ����

	Terrain(pcStr heightmap, pcStr surfaceTex, GLuint width, GLint height);
	~Terrain(void);

	// ���� �׸��� : ī�޶��� (x,y)��ǥ - (eye.x, eye.z) <- ���÷��� ����Ʈ �̿�
	void RenderTerrain(GLfloat x, GLfloat y);
	// LoD�� ���� Ÿ�ϸ�
	void TileTerrain(GLint levelOfDetail);
	// �� �׸���
	void RenderWater();
	// �ش� ��ġ(_x,_y) ���� ���ϱ�
	GLfloat getHeight(GLfloat _x, GLfloat _y);

	// �ش� ī�޶� ��ġ�� �ؽ�ó Ÿ���� �� ��ǥ ���ϱ�
	GLint getTileX(GLfloat x);
	GLint getTileY(GLfloat y);
};