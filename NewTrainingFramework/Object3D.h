#pragma once
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Transform.h"

class Object3D {
public:
	Object3D();

	Model *model;
	Texture *texture;
	Shaders *shaders;
	Transform transform;

	void InitObject3D(char* model_filename, char* texture_filename, char* vs_filename, char* fs_filename);
	void SetTransform(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat RotX, GLfloat RotY, GLfloat RotZ);
	Matrix GetWorldMatrix();

	void Draw(Matrix View, Matrix Projection);
};