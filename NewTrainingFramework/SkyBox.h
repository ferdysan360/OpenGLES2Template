#pragma once
#include "../Utilities/utilities.h"
#include "Object3D.h"
#include "Camera.h"

class SkyBox : public Object3D {
public:
	void InitSkyBox(char* model_filename, char* PX, char* NX, char* PY, char* NY, char* PZ, char* NZ, char* vs_filename, char* fs_filename);
	void Draw(Matrix View, Matrix Projection);
	void DrawReflection(Matrix View, Matrix Projection, Camera camera);
};