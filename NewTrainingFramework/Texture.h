#pragma once
#include "../Utilities/utilities.h"

class Texture {
public:
	GLuint textureID;
	char* imageData;
	int width, height, bpp;
	Texture();
	~Texture();
	void InitTexture(char* filename);
	void InitSkyBoxTexture(char* PX, char* NX, char* PY, char* NY, char* PZ, char* NZ);
};