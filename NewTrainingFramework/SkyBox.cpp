#include "stdafx.h"
#include "SkyBox.h"

void SkyBox::InitSkyBox(char* model_filename, char* PX, char* NX, char* PY, char* NY, char* PZ, char* NZ, char* vs_filename, char* fs_filename) {
	model.InitModel(model_filename);
	texture.InitSkyBoxTexture(PX, NX, PY, NY, PZ, NZ);
	shaders.Init(vs_filename, fs_filename);
}