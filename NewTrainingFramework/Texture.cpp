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

void Texture::InitSkyBoxTexture(char* PX, char* NX, char* PY, char* NY, char* PZ, char* NZ) {
	//char* cubePixels[6];

	int width0, height0, bpp0;
	int width1, height1, bpp1;
	int width2, height2, bpp2;
	int width3, height3, bpp3;
	int width4, height4, bpp4;
	int width5, height5, bpp5;

	char* cubePixels0 = LoadTGA(PX, &width0, &height0, &bpp0);
	char* cubePixels1 = LoadTGA(NX, &width1, &height1, &bpp1);
	char* cubePixels2 = LoadTGA(PY, &width2, &height2, &bpp2);
	char* cubePixels3 = LoadTGA(NY, &width3, &height3, &bpp3);
	char* cubePixels4 = LoadTGA(PZ, &width4, &height4, &bpp4);
	char* cubePixels5 = LoadTGA(NZ, &width5, &height5, &bpp5);
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/*for (int i = 0; i < 6; i++)
	{
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_RGB,
			512,
			512,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			cubePixels[i]);
	}*/

	// Load the cube face - Positive X
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width0, height0, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels0);
	// Load the cube face - Negative X
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels1);
	// Load the cube face - Positive Y
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels2);
	// Load the cube face - Negative Y
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels3);
	// Load the cube face - Positive Z
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width4, height4, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels4);
	// Load the cube face - Negative Z
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width5, height5, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels5);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	/*for (int i = 0; i < 6; i++) {
		delete cubePixels[i];
	}*/
}