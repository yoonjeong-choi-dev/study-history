#include "Terrain.h"
#include <iostream>
Terrain::Terrain(pcStr heightFile, pcStr surfaceTexFile, GLuint width, GLint height) {
	// ���� ũ�� ����
	_map_width = width;
	_map_height = height;

	// �ؽ�ó ���� ���� �ʱ�ȭ
	img = NULL;
	_textureId_ground = 0;
	_textureId_water = 0;
	_height = 0;

	// ���� �ؽ��� ���� �� ����
	img = auxDIBImageLoad(surfaceTexFile);
	glGenTextures(1, &_textureId_ground);	// ���� �ؽ�ó ��ü ����
	glBindTexture(GL_TEXTURE_2D, _textureId_ground);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
		img->sizeX, img->sizeY, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, img->data);
	// �ؽ�ó Ȯ�� ������ ���� : ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// �ؽ����� Ȯ�� ��� ���� : �ݺ� -> ���� ������ ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// �� �ؽ��� ���� �� ����
	img = auxDIBImageLoad(waterTextureFile);
	glGenTextures(1, &_textureId_water);	// �� �ؽ�ó ��ü ����
	glBindTexture(GL_TEXTURE_2D, _textureId_water);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
		img->sizeX, img->sizeY, 0, 
		GL_RGB, GL_UNSIGNED_BYTE, img->data);
	// �ؽ����� Ȯ�� ��� ���� : �ݺ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);


	// ���������� ������ ���� ���� ������ ����
	_height = readRawData(heightFile, _map_width, _map_height);

	// ���� ������ �ּҰ� ���ϱ�
	minHeight = 2 ^ 10;
	for (int i = 0; i < _map_width*height; i++) {
		if (minHeight>_height[i]) { 
			minHeight = _height[i]; 
		}
	}

	// ���� ���� ������ rescale : �ּ� ���� �������� �ڸ���
	for (int i = 0; i < _map_width*_map_height + 1; i++) {
		_height[i] -= minHeight;
	}

	// �� ���̴� ���� ������ �ּҰ��� �̿��Ͽ� ����
	waterLevel = (GLfloat)minHeight + 100;

	// ���� Ÿ�ϸ��ϱ� : 4�ܰ� ���� Ÿ�� �� ���� ���� ���÷��� ����Ʈ
	baseTerrain = glGenLists(5);	
	
	// detail level1 ����
	glNewList(baseTerrain, GL_COMPILE);
	TileTerrain(1);
	glEndList();
	
	// detail level2 ����
	glNewList(baseTerrain + 1, GL_COMPILE);
	TileTerrain(4);
	glEndList();
	

	// detail level3 ����
	glNewList(baseTerrain + 2, GL_COMPILE);
	TileTerrain(8);
	glEndList();
	

	// detail level4 ����
	glNewList(baseTerrain + 3, GL_COMPILE);
	TileTerrain(16);
	glEndList();
	

	//�� �׸���
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

// ���� ���÷��� ����Ʈ �ҷ����� �Լ�
// ���� ��ġ�� �߽����� lod�� ���� ���簡�� ���
void Terrain::RenderTerrain(GLfloat x, GLfloat y) {
	int i, j;

	// detail level1 ���� : ī�޶� ��ġ�� (x,y)�� ���ؼ� 1��
	// x ��ǥ : getTileX(x)*(_map_width - 1)
	// y ��ǥ : getTileY(y)*(_map_height - 1)
	glPushMatrix();
	glTranslatef(getTileX(x)*(_map_width - 1), 0.0, getTileY(y)*(_map_height - 1));
	glCallList(baseTerrain);
	glPopMatrix();

	// detail level2 ���� : level1 �� ������ 3*3 �� 
	// x ��ǥ : getTileX(x)*(_map_width - 1) + (i*(_map_width - 1))
	// y ��ǥ : getTileY(y)*(_map_height - 1) + (j*(_map_height - 1))
	for (i = -1; i<2; i++) {
		for (j = -1; j<2; j++) {
			// level1 �� ����
			if (!(i == 0 && j == 0)) {
				glPushMatrix();
				glTranslatef(getTileX(x)*(_map_width - 1) + (i*(_map_width - 1)), 0.0, getTileY(y)*(_map_height - 1) + (j*(_map_height - 1)));
				glCallList(baseTerrain + 1);
				glPopMatrix();
			}
		}
	}

	// detail level3 ���� : level1,2 �� ������ 5*5 ��
	// x ��ǥ : getTileX(x)*(_map_width - 1) + (i*(_map_width - 1))
	// y ��ǥ : getTileY(y)*(_map_height - 1) + (j*(_map_height - 1))
	for (i = -2; i<3; i++) {
		for (j = -2; j<3; j++) {
			// level1,2 ��� ����
			if ((i<-1 || i>1) || (j<-1 || j>1)) {
				glPushMatrix();
				glTranslatef(getTileX(x)*(_map_width - 1) + (i*(_map_width - 1)), 0.0, getTileY(y)*(_map_height - 1) + (j*(_map_height - 1)));
				glCallList(baseTerrain + 2);
				glPopMatrix();
			}
		}
	}

	// detail level4 ���� : level1,2,3 �� ������ 7*7 ��
	// x ��ǥ : getTileX(x)*(_map_width - 1) + (i*(_map_width - 1))
	// y ��ǥ : getTileY(y)*(_map_height - 1) + (j*(_map_height - 1))
	for (i = -3; i<4; i++) {
		for (j = -3; j<4; j++) {
			// level1,2,3 ��� ����
			if ((i<-2 || i>2) || (j<-2 || j>2)) {
				glPushMatrix();
				glTranslatef(getTileX(x)*(_map_width - 1) + (i*(_map_width - 1)), 0.0, getTileY(y)*(_map_height - 1) + (j*(_map_height - 1)));
				glCallList(baseTerrain + 3);
				glPopMatrix();
			}
		}
	}

	// �� ���÷��� ����Ʈ : 5*5 ����
	// x ��ǥ : getTileX(x)*(_map_width - 1) + (i*(_map_width - 1))
	// y ��ǥ : getTileY(y)*(_map_height - 1) + (j*(_map_height - 1))
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

	// �𵨺� ��� ����
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// GL_DECAL ������ ���� ������ �ٸ� ��ü ������ ������ ���� �ʰ� ��
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, _textureId_ground);

	// ����,���� �̵� ���� ����
	float coordX = (float)1.0 / _map_width; 
	float coordZ = (float)1.0 / _map_height;

	// x,z���� �������� �׸� ������ �ٴڿ� ����
	// LoD�� �̿��Ͽ� x,z���� �����δ�
	for (int z = 0; z < _map_height; z += levelOfDetail) {
		// ��ǥ���� �ﰢ������ Ÿ�ϸ�
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < _map_width; x += levelOfDetail) {
			// (x,z) ��ǥ�� ���� :  _height[z*_map_height + x]
			glTexCoord2f(coordX*x, coordZ*z);
			glVertex3f(x, _height[z*_map_height + x], z);
			// (x,z+levelOfDetail) ��ǥ�� ���� :  _height[(z+levelOfDetail)*_map_height + x]
			glTexCoord2f(coordX*x, coordZ*(z + levelOfDetail));
			glVertex3f(x, _height[(z + levelOfDetail)*_map_height + x], z + levelOfDetail);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Terrain::RenderWater() {
	// ���� ���� �ؽ�ó �׸���
	glEnable(GL_TEXTURE_2D);
	// GL_MODULATE : ���� ��ü���� ���� �ؽ�ó�� ���� ���Ͽ� ������ ����
	// => ���� ������ ������ �ݿ��Ͽ� ��ü���� ǥ��
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// ��Ƽ ���ϸ������ ���� ȥ�� �Լ� ����
	glEnable(GL_BLEND);			
	glDisable(GL_CULL_FACE);	// �ĸ����� ��Ȱ��ȭ
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// ȥ���Լ� ����
	glColor4f(0.0, 0.4, 0.5, 0.7);

	// �� �ؽ�ó ��ü�� ���� �ؽ�ó ����
	glBindTexture(GL_TEXTURE_2D, _textureId_water);
	
	glBegin(GL_QUADS);	// ���� ������(waterLevel)�� �����ϰ� ��������
	glTexCoord2f(0.0, 0.0);		glVertex3f(0.0, waterLevel, 0.0);
	glTexCoord2f(15.0, 0.0);	glVertex3f(0.0, waterLevel, _map_height);
	glTexCoord2f(15.0, 15.0);	glVertex3f(_map_height, waterLevel, _map_height);
	glTexCoord2f(0.0, 15.0);	glVertex3f(_map_height, waterLevel, 0.0);
	glEnd();

	// ���� ���·� 
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

GLfloat Terrain::getHeight(GLfloat _x, GLfloat _y) {
	int x, y;

	// �ؽ��� �̹��� ������ �Ѿ�� ������ �ݴ��� ��ǥ��
	if (_x < 0) {
		x = _map_width + ((int)_x%_map_width);
	}
	else {
		x = ((int)_x % _map_width);
	}
	// �ؽ��� �̹��� ������ �Ѿ�� ������ �ݴ��� ��ǥ��
	if (_y < 0) {
		y = _map_height + ((int)_y % _map_height);
	}
	else {
		y = ((int)_y % _map_height);
	}

	// y*_map_height + x : _height �迭���� (x,y) ��ǥ�� ���� ���� ����
	// ����/5+10�� ���� rescaling
	return _height[y*_map_height + x] / 5 + 10;
}


// [_map_width*k, _map_width*(k+1)) ���̿� x�� �ִ� ��� k��° Ÿ�Ϸ� ����
GLint Terrain::getTileX(GLfloat x) {
	if (x > 0) {
		return ((int)x) / (int)_map_width;
	}
	// x�� ������ x/_map_width ������ �������� ����
	// e.g) -7/4=-1 <=> -7 = 4*(-1) + (-3)
	// ���� ���������꿡�� -1�� �������
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
	fopen_s(&pFile, filename, "rb");	// ���� ���� ������(.raw)����

	// ������ ���� ��� ���� ó��
	if (!pFile) {
		printf("file not found : $s\n", filename);
		throw std::exception();
	}

	// ��������� raw ���� : ����ũ��==�̹��� �ȼ���
	// w*h ũ�� ��ŭ�� ������ �Ҵ��ϸ� ��� �����͸� �о�� �� ����
	ubyte* buffer = new ubyte[w*h];
	fread(buffer, sizeof(ubyte), w*h, pFile);
	fclose(pFile);
	return buffer;
}