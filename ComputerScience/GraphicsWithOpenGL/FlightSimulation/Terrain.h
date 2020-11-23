#pragma once
/*
Terrain.h
- 지면텍스쳐, 물텍스쳐, 안개를 지형으로 구성
- 2차원 영상을 이용해 지표면의 높낮이 부여
	- 어두운 부분은 높이가 낮고 밝은 부분은 높이가 높다고 가정
	- 각 화소의 회색도가 저장된 .raw 파일을 이용
- 텍스처 및 높이 영상의 x,y축은 지표면의 x,z축에 해당
	- 높이 영상의 회색도만큼 지표면의 y축 방향으로 올려진 정점에 해당 텍스처 영상 컬러 칠함
- 조명
	- 삼각형 메시의 두 변에 대한 외적을 통해 법선 벡터를 구하여 조명에 적용
	- 지엘의 조명 모델 적용
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

	
	uint _textureId_ground, _textureId_water;	// 지형텍스쳐와 물텍스쳐의 id
	AUX_RGBImageRec *img; // 텍스쳐 이미지 객체와 연결되는 포인터

	ubyte* _height;						// 지형높이 배열과 연결하는 포인터
	GLint _map_width, _map_height;		// 단위지형의 가로세로크기
	GLuint baseTerrain;					// 타일의 인덱스값(디스플레이 리스트)
	GLubyte minHeight;					// 지형데이터의 최소높이
	
	// 지형 데이터(.raw) 파일 불러오는 함수 : (파일 경로, 높이맵 가로 크기, 높이맵 세로크기)
	static ubyte* readRawData(pcStr filename, uint width, uint height);

public:
	GLfloat waterLevel;		//수면 높이

	Terrain(pcStr heightmap, pcStr surfaceTex, GLuint width, GLint height);
	~Terrain(void);

	// 지형 그리기 : 카메라의 (x,y)좌표 - (eye.x, eye.z) <- 디스플레이 리스트 이용
	void RenderTerrain(GLfloat x, GLfloat y);
	// LoD를 위한 타일링
	void TileTerrain(GLint levelOfDetail);
	// 물 그리기
	void RenderWater();
	// 해당 위치(_x,_y) 높이 구하기
	GLfloat getHeight(GLfloat _x, GLfloat _y);

	// 해당 카메라 위치의 텍스처 타일의 블럭 좌표 구하기
	GLint getTileX(GLfloat x);
	GLint getTileY(GLfloat y);
};