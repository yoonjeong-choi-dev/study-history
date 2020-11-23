#include "Skybox.h"

// 생성자 : 각 육면체 텍스처 파일을 불러와 텍스처 메모리로 할당하고 해당 id를 저장
Skybox::Skybox() {
	for (int i = 0; i < 6; i++) {
		textures[i] = _loadTexture(textureFile[i]);
	}
}

Skybox::~Skybox() {

}

void Skybox::draw() {
	// 텍스처 모드 활성화
	glEnable(GL_TEXTURE_2D);

	// 현재 모델뷰 행렬에서 배경 적용
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// 배경 화면에 뿌려지기 위한 작업
	// 깊이 버퍼를 비활성화하고, GL_DECAL 설정을 통해 배경이 다른 물체 색상의 영향을 받지 않게 함
	glDisable(GL_DEPTH_TEST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glColor3f(0, 0, 0);

	// 6개의 면에 대한 텍스처 객체에 대해서 텍스쳐를 입힌다
	// 1. front
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-TEXURE_SIZE, -TEXURE_SIZE, -TEXURE_SIZE);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(TEXURE_SIZE, -TEXURE_SIZE, -TEXURE_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(TEXURE_SIZE, TEXURE_SIZE, -TEXURE_SIZE);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-TEXURE_SIZE, TEXURE_SIZE, -TEXURE_SIZE);
	glEnd();

	// 2. back
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(TEXURE_SIZE, -TEXURE_SIZE, TEXURE_SIZE);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-TEXURE_SIZE, -TEXURE_SIZE, TEXURE_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-TEXURE_SIZE, TEXURE_SIZE, TEXURE_SIZE);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(TEXURE_SIZE, TEXURE_SIZE, TEXURE_SIZE);
	glEnd();

	// 3. left
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(TEXURE_SIZE, -TEXURE_SIZE, -TEXURE_SIZE);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(TEXURE_SIZE, -TEXURE_SIZE, TEXURE_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(TEXURE_SIZE, TEXURE_SIZE, TEXURE_SIZE);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(TEXURE_SIZE, TEXURE_SIZE, -TEXURE_SIZE);
	glEnd();

	// 4. right
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-TEXURE_SIZE, -TEXURE_SIZE, TEXURE_SIZE);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-TEXURE_SIZE, -TEXURE_SIZE, -TEXURE_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-TEXURE_SIZE, TEXURE_SIZE, -TEXURE_SIZE);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-TEXURE_SIZE, TEXURE_SIZE, TEXURE_SIZE);
	glEnd();

	// 5. up
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-TEXURE_SIZE, TEXURE_SIZE, -TEXURE_SIZE);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(TEXURE_SIZE, TEXURE_SIZE, -TEXURE_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(TEXURE_SIZE, TEXURE_SIZE, TEXURE_SIZE);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-TEXURE_SIZE, TEXURE_SIZE, TEXURE_SIZE);
	glEnd();

	// 6. down
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-TEXURE_SIZE, -TEXURE_SIZE, TEXURE_SIZE);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(TEXURE_SIZE, -TEXURE_SIZE, TEXURE_SIZE);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(TEXURE_SIZE, -TEXURE_SIZE, -TEXURE_SIZE);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-TEXURE_SIZE, -TEXURE_SIZE, -TEXURE_SIZE);
	glEnd();

	// 깊이 버퍼 활성화 
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

// 해당 텍스처 파일을 불러와 텍스처 메모리에 할당하고 해당 id를 반환
Skybox::uint Skybox::_loadTexture(pcStr filename) {
	// 파일을 메모리에 저장
	AUX_RGBImageRec* img = auxDIBImageLoadA(filename);

	// GL 텍스처 객체 생성
	GLuint textureId;
	glGenTextures(1, &textureId);

	// GL 텍스처 객체 설정
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->sizeX, img->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE, img->data);

	// 텍스처 확장 보간법 설정 : 선형
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 텍스처의 (s,t)의 방향에 대한 래핑 모드 설정 : 접합부(seam)을 부드럽게
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	// 메모리 할당 해제
	free(img->data);
	free(img);

	return textureId;
}