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

void Texture::InitSkyBoxTexture() {
	//char* cubePixels[6];

	char* cubePixels0 = LoadTGA("../Resources/Textures/Skybox_Right.tga", &width, &height, &bpp);
	char* cubePixels1 = LoadTGA("../Resources/Textures/Skybox_Left.tga", &width, &height, &bpp);
	char* cubePixels2 = LoadTGA("../Resources/Textures/Skybox_Top.tga", &width, &height, &bpp);
	char* cubePixels3 = LoadTGA("../Resources/Textures/Skybox_Bottom.tga", &width, &height, &bpp);
	char* cubePixels4 = LoadTGA("../Resources/Textures/Skybox_Front.tga", &width, &height, &bpp);
	char* cubePixels5 = LoadTGA("../Resources/Textures/Skybox_Back.tga", &width, &height, &bpp);
	
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
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels0);
	// Load the cube face - Negative X
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels1);
	// Load the cube face - Positive Y
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels2);
	// Load the cube face - Negative Y
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels3);
	// Load the cube face - Positive Z
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels4);
	// Load the cube face - Negative Z
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixels5);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	/*for (int i = 0; i < 6; i++) {
		delete cubePixels[i];
	}*/
}