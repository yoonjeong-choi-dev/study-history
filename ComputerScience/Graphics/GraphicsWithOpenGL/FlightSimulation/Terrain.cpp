#include "Terrain.h"
#include <iostream>
Terrain::Terrain(pcStr heightFile, pcStr surfaceTexFile, GLuint width, GLint height) {
	// 맵의 크기 설정
	_map_width = width;
	_map_height = height;

	// 텍스처 관련 변수 초기화
	img = NULL;
	_textureId_ground = 0;
	_textureId_water = 0;
	_height = 0;

	// 지형 텍스쳐 세팅 및 설정
	img = auxDIBImageLoad(surfaceTexFile);
	glGenTextures(1, &_textureId_ground);	// 지형 텍스처 객체 생성
	glBindTexture(GL_TEXTURE_2D, _textureId_ground);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
		img->sizeX, img->sizeY, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, img->data);
	// 텍스처 확장 보간법 설정 : 선형
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// 텍스쳐의 확장 방법 설정 : 반복 -> 맵이 끝없이 펼쳐진다
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// 물 텍스쳐 세팅 및 설정
	img = auxDIBImageLoad(waterTextureFile);
	glGenTextures(1, &_textureId_water);	// 물 텍스처 객체 생성
	glBindTexture(GL_TEXTURE_2D, _textureId_water);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
		img->sizeX, img->sizeY, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, img->data);
	// 텍스쳐의 확장 방법 설정 : 반복
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);


	// 지형데이터 파일을 통한 높이 데이터 저장
	_height = readRawData(heightFile, _map_width, _map_height);

	// 지형 높이의 최소값 구하기
	minHeight = 2 ^ 10;
	for (int i = 0; i < _map_width*height; i++) {
		if (minHeight>_height[i]) { 
			minHeight = _height[i]; 
		}
	}

	// 지형 높이 데이터 rescale : 최소 높이 기준으로 자른다
	for (int i = 0; i < _map_width*_map_height + 1; i++) {
		_height[i] -= minHeight;
	}

	// 물 높이는 지형 높이의 최소값을 이용하여 설정
	waterLevel = (GLfloat)minHeight + 100;

	// 지형 타일링하기 : 4단계 지형 타일 및 물에 대한 디스플레이 리스트
	baseTerrain = glGenLists(5);	
	
	// detail level1 지형
	glNewList(baseTerrain, GL_COMPILE);
	TileTerrain(1);
	glEndList();
	
	// detail level2 지형
	glNewList(baseTerrain + 1, GL_COMPILE);
	TileTerrain(4);
	glEndList();
	

	// detail level3 지형
	glNewList(baseTerrain + 2, GL_COMPILE);
	TileTerrain(8);
	glEndList();
	

	// detail level4 지형
	glNewList(baseTerrain + 3, GL_COMPILE);
	TileTerrain(16);
	glEndList();
	

	//물 그리기
	glNewList(baseTerrain + 4, GL_COMPILE);
	RenderWater();
	glEndList();
}

Terrain::~Terrain(){
	if (_height != 0) {
		delete[] _height;
	}
	if (_textureId_ground != 0) {
		glDeleteTextures(1, &_textureId_ground);
	}
	if (_textureId_water != 0) {
		glDeleteTextures(1, &_textureId_water);
	}
	if (img != 0) {
		free(img->data);
		free(img);
	}
}

// 지형 디스플레이 리스트 불러오는 함수
// 현재 위치를 중심으로 lod를 점점 낮춰가는 방식
void Terrain::RenderTerrain(GLfloat x, GLfloat y) {
	int i, j;

	// detail level1 지형 : 카메라 위치인 (x,y)에 대해서 1블럭
	// x 좌표 : getTileX(x)*(_map_width - 1)
	// y 좌표 : getTileY(y)*(_map_height - 1)
	glPushMatrix();
	glTranslatef(getTileX(x)*(_map_width - 1), 0.0, getTileY(y)*(_map_height - 1));
	glCallList(baseTerrain);
	glPopMatrix();

	// detail level2 지형 : level1 블럭 제외한 3*3 블럭 
	// x 좌표 : getTileX(x)*(_map_width - 1) + (i*(_map_width - 1))
	// y 좌표 : getTileY(y)*(_map_height - 1) + (j*(_map_height - 1))
	for (i = -1; i<2; i++) {
		for (j = -1; j<2; j++) {
			// level1 블럭 제외
			if (!(i == 0 && j == 0)) {
				glPushMatrix();
				glTranslatef(getTileX(x)*(_map_width - 1) + (i*(_map_width - 1)), 0.0, getTileY(y)*(_map_height - 1) + (j*(_map_height - 1)));
				glCallList(baseTerrain + 1);
				glPopMatrix();
			}
		}
	}

	// detail level3 지형 : level1,2 블럭 제외한 5*5 블럭
	// x 좌표 : getTileX(x)*(_map_width - 1) + (i*(_map_width - 1))
	// y 좌표 : getTileY(y)*(_map_height - 1) + (j*(_map_height - 1))
	for (i = -2; i<3; i++) {
		for (j = -2; j<3; j++) {
			// level1,2 블록 제외
			if ((i<-1 || i>1) || (j<-1 || j>1)) {
				glPushMatrix();
				glTranslatef(getTileX(x)*(_map_width - 1) + (i*(_map_width - 1)), 0.0, getTileY(y)*(_map_height - 1) + (j*(_map_height - 1)));
				glCallList(baseTerrain + 2);
				glPopMatrix();
			}
		}
	}

	// detail level4 지형 : level1,2,3 블럭 제외한 7*7 블럭
	// x 좌표 : getTileX(x)*(_map_width - 1) + (i*(_map_width - 1))
	// y 좌표 : getTileY(y)*(_map_height - 1) + (j*(_map_height - 1))
	for (i = -3; i<4; i++) {
		for (j = -3; j<4; j++) {
			// level1,2,3 블록 제외
			if ((i<-2 || i>2) || (j<-2 || j>2)) {
				glPushMatrix();
				glTranslatef(getTileX(x)*(_map_width - 1) + (i*(_map_width - 1)), 0.0, getTileY(y)*(_map_height - 1) + (j*(_map_height - 1)));
				glCallList(baseTerrain + 3);
				glPopMatrix();
			}
		}
	}

	// 물 디스플레이 리스트 : 5*5 면적
	// x 좌표 : getTileX(x)*(_map_width - 1) + (i*(_map_width - 1))
	// y 좌표 : getTileY(y)*(_map_height - 1) + (j*(_map_height - 1))
	for (i = -2; i<3; i++) {
		for (j = -2; j<3; j++) {
			glPushMatrix();
			glTranslatef(getTileX(x)*(_map_width - 1) + (i*(_map_width)-1), 0.0, getTileY(y)*(_map_height - 1) + (j*(_map_height - 1)));
			glCallList(baseTerrain + 4);
			glPopMatrix();
		}
	}
}

void Terrain::TileTerrain(GLint levelOfDetail) {
	glEnable(GL_TEXTURE_2D);

	// 모델뷰 행렬 설정
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// GL_DECAL 설정을 통해 지형이 다른 물체 색상의 영향을 받지 않게 함
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, _textureId_ground);

	// 가로,세로 이동 단위 설정
	float coordX = (float)1.0 / _map_width; 
	float coordZ = (float)1.0 / _map_height;

	// x,z축을 기준으로 그림 공간의 바닥에 매핑
	// LoD를 이용하여 x,z축을 움직인다
	for (int z = 0; z < _map_height; z += levelOfDetail) {
		// 지표면은 삼각형으로 타일링
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < _map_width; x += levelOfDetail) {
			// (x,z) 좌표의 높이 :  _height[z*_map_height + x]
			glTexCoord2f(coordX*x, coordZ*z);
			glVertex3f(x, _height[z*_map_height + x], z);
			// (x,z+levelOfDetail) 좌표의 높이 :  _height[(z+levelOfDetail)*_map_height + x]
			glTexCoord2f(coordX*x, coordZ*(z + levelOfDetail));
			glVertex3f(x, _height[(z + levelOfDetail)*_map_height + x], z + levelOfDetail);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Terrain::RenderWater() {
	// 물에 대한 텍스처 그리기
	glEnable(GL_TEXTURE_2D);
	// GL_MODULATE : 기존 물체면의 색과 텍스처의 색을 곱하여 최종색 결정
	// => 물의 투명한 정도를 반영하여 물체색을 표현
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// 안티 에일리어싱을 위한 혼합 함수 설정
	glEnable(GL_BLEND);			
	glDisable(GL_CULL_FACE);	// 후면제거 비활성화
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// 혼합함수 설정
	glColor4f(0.0, 0.4, 0.5, 0.7);

	// 물 텍스처 객체에 대한 텍스처 매핑
	glBindTexture(GL_TEXTURE_2D, _textureId_water);
	
	glBegin(GL_QUADS);	// 같은 물높이(waterLevel)를 유지하고 정점연결
	glTexCoord2f(0.0, 0.0);		glVertex3f(0.0, waterLevel, 0.0);
	glTexCoord2f(15.0, 0.0);	glVertex3f(0.0, waterLevel, _map_height);
	glTexCoord2f(15.0, 15.0);	glVertex3f(_map_height, waterLevel, _map_height);
	glTexCoord2f(0.0, 15.0);	glVertex3f(_map_height, waterLevel, 0.0);
	glEnd();

	// 원래 상태로 
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

GLfloat Terrain::getHeight(GLfloat _x, GLfloat _y) {
	int x, y;

	// 텍스쳐 이미지 범위를 넘어가면 지형의 반대편 좌표로
	if (_x < 0) {
		x = _map_width + ((int)_x%_map_width);
	}
	else {
		x = ((int)_x % _map_width);
	}
	// 텍스쳐 이미지 범위를 넘어가면 지형의 반대편 좌표로
	if (_y < 0) {
		y = _map_height + ((int)_y % _map_height);
	}
	else {
		y = ((int)_y % _map_height);
	}

	// y*_map_height + x : _height 배열에서 (x,y) 좌표에 대한 높이 정보
	// 높이/5+10를 통한 rescaling
	return _height[y*_map_height + x] / 5 + 10;
}


// [_map_width*k, _map_width*(k+1)) 사이에 x가 있는 경우 k번째 타일로 정의
GLint Terrain::getTileX(GLfloat x) {
	if (x > 0) {
		return ((int)x) / (int)_map_width;
	}
	// x가 음수면 x/_map_width 연산의 나머지가 음수
	// e.g) -7/4=-1 <=> -7 = 4*(-1) + (-3)
	// 따라서 나눗셈연산에서 -1을 해줘야함
	else {
		return ((int)x) / (int)_map_width - 1;
	}
}

GLint Terrain::getTileY(GLfloat y) {
	if (y > 0) {
		return ((int)y) / (int)_map_height;
	}
	else {
		return ((int)y) / (int)_map_height - 1;
	}
}

Terrain::ubyte* Terrain::readRawData(pcStr filename, uint w, uint h) {
	FILE* pFile;
	fopen_s(&pFile, filename, "rb");	// 지형 높이 데이터(.raw)열기

	// 파일이 없는 경우 예외 처리
	if (!pFile) {
		printf("file not found : $s\n", filename);
		throw std::exception();
	}

	// 헤더가없는 raw 파일 : 파일크기==이미지 픽셀수
	// w*h 크기 만큼의 공간을 할당하면 모든 데이터를 읽어올 수 있음
	ubyte* buffer = new ubyte[w*h];
	fread(buffer, sizeof(ubyte), w*h, pFile);
	fclose(pFile);
	return buffer;
}