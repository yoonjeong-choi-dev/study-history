#pragma once
/*
FlightSimulator.h
- 비행기 시뮬레이션을 하기 위한 시뮬레이터

< 요구 사항 > 
- 비행기의 전진 이동 및 Roll/Pitch/Yaw 효과 구현
- 외부 공간을 둘러싸는 스카이박스
- 지형 모델링
- 호수 배누에서의 블렌딩 효과
- 비행기에서 미사일 발사 후 충돌 탐지에 의한 지면의 먼지/파편이 흩어지는 현상을 파티클 시스템으로 표현
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
	static Terrain* terrain;		//지형 객체
	static Skybox* skybox;		//스카이박스 객체
	static Camera cam;			//카메라 객체
	static bool keyPressed[256];	// 키보드 관련 

	// 파일 경로 설정
	static const char *terrainHeightFile;
	static const char *terrainSurfaceFile;

	// 이동 및 회전에 대한 상수 정의 
	static const double delta_slide_forward;
	static const double delta_slide_side;
	static const float delta_pitch;
	static const float delta_yaw;
	static const float delta_roll;

private:
	static void dispose();		// 종료시 수행
	static void Display();		// display 콜백
	static void Idle();		// idle 콜백
	static void Reshape(int w, int h);	// reshape 콜백
	static void Keyboard(unsigned char key, int x, int y);		//keyboard 콜백
	static void KeyboardUp(unsigned char key, int x, int y);	//keyboardUp 콜백
	static void fog();
public:
	static int run();			// 메인 함수
};

