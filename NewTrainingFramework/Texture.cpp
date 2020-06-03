#include "stdafx.h"
#include "Texture.h"
#include <iostream>
using namespace std;

Texture::Texture() {
	;
}

Texture::~Texture() {
	glDeleteTextures(1, &textureID);
}

void Texture::InitTexture(char* filename) {
	imageData = LoadTGA(filename, &width, &height, &bpp);

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, imageData);

	glBindTexture(GL_TEXTURE_2D, 0);
}