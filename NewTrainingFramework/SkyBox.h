#pragma once
#include "../Utilities/utilities.h"
#include "Object3D.h"

class SkyBox : public Object3D {
public:
	void InitSkyBox(char* model_filename, char* texture_filename, char* vs_filename, char* fs_filename);
};