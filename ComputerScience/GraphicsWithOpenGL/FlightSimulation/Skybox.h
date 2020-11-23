#pragma once
/*
Skybox.h
- 외부 공간을 둘러싸는 스카이박스를 렌더링하는 클래스 정의
- 비행기 주변의 배경 하늘을 묘사하는 것
- 비트맵 영상 6개를 텍스처 매핑으로 육면체 내부면 렌더링
	- 면과 면 사이의 닿는 부분(Seam)에서는 구름이 자연스럽게 이어지도록 영상 조정 필요
	- 박스 내부에서 면을 바라보고 있으므로 GLFrontFace(GL_CW)로 설정 필요
- 배경 영상은 항상 배경화면에 뿌려져야 한다
	- 깊이 버퍼를 비활성화 한 후 스카이박스를 그린다
	- Z 버퍼 연산에서 스카이박스 정보를 사용하지 않아 배경화면 효과가 나타남
*/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/GLAUX.H>
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#define TEXURE_SIZE 3
#define GL_CLAMP_TO_EDGE 0x812F	//EDGE의 색상으로 경계를 확장



class Skybox {
public:
	Skybox();
	~Skybox();
	void draw();

private:
	// 육면체의 각 면에 대한 텍스처 파일 정의
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
	uint textures[6];			// 육면체의 각 면의 텍스처 id

	// 텍스처 파일을 통해 데이터 불러오는 함수
	static uint _loadTexture(pcStr filename);
};