#include "Skybox.h"

// ������ : �� ����ü �ؽ�ó ������ �ҷ��� �ؽ�ó �޸𸮷� �Ҵ��ϰ� �ش� id�� ����
Skybox::Skybox() {
	for (int i = 0; i < 6; i++) {
		textures[i] = _loadTexture(textureFile[i]);
	}
}

Skybox::~Skybox() {

}

void Skybox::draw() {
	// �ؽ�ó ��� Ȱ��ȭ
	glEnable(GL_TEXTURE_2D);

	// ���� �𵨺� ��Ŀ��� ��� ����
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// ��� ȭ�鿡 �ѷ����� ���� �۾�
	// ���� ���۸� ��Ȱ��ȭ�ϰ�, GL_DECAL ������ ���� ����� �ٸ� ��ü ������ ������ ���� �ʰ� ��
	glDisable(GL_DEPTH_TEST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glColor3f(0, 0, 0);

	// 6���� �鿡 ���� �ؽ�ó ��ü�� ���ؼ� �ؽ��ĸ� ������
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

	// ���� ���� Ȱ��ȭ 
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

// �ش� �ؽ�ó ������ �ҷ��� �ؽ�ó �޸𸮿� �Ҵ��ϰ� �ش� id�� ��ȯ
Skybox::uint Skybox::_loadTexture(pcStr filename) {
	// ������ �޸𸮿� ����
	AUX_RGBImageRec* img = auxDIBImageLoadA(filename);

	// GL �ؽ�ó ��ü ����
	GLuint textureId;
	glGenTextures(1, &textureId);

	// GL �ؽ�ó ��ü ����
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->sizeX, img->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE, img->data);

	// �ؽ�ó Ȯ�� ������ ���� : ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// �ؽ�ó�� (s,t)�� ���⿡ ���� ���� ��� ���� : ���պ�(seam)�� �ε巴��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	// �޸� �Ҵ� ����
	free(img->data);
	free(img);

	return textureId;
}