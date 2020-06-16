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
	void InitSkyBoxTexture();
};