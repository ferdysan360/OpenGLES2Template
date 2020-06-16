#include "stdafx.h"
#include "SkyBox.h"

void SkyBox::InitSkyBox(char* model_filename, char* texture_filename, char* vs_filename, char* fs_filename) {
	model.InitModel(model_filename);
	texture.InitSkyBoxTexture();
	shaders.Init(vs_filename, fs_filename);
}