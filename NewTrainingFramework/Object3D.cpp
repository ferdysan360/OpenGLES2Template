#include "stdafx.h"
#include "Object3D.h"
#include <iostream>
using namespace std;

void Object3D::InitObject3D(char* model_filename, char* texture_filename, char* vs_filename, char* fs_filename) {
	model.InitModel(model_filename);
	texture.InitTexture(texture_filename);
	shaders.Init(vs_filename, fs_filename);
}

void Object3D::SetTransform(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat RotX, GLfloat RotY, GLfloat RotZ) {
	transform.position.x = posX;
	transform.position.y = posY;
	transform.position.z = posZ;
	transform.scale.x = scaleX;
	transform.scale.y = scaleY;
	transform.scale.z = scaleZ;
	transform.rotation.x = RotX;
	transform.rotation.y = RotY;
	transform.rotation.z = RotZ;
}

Matrix Object3D::GetWorldMatrix() {
	Matrix World, Scale, RotZ, RotX, RotY, Translate;
	
	World.SetIdentity();

	// set scale
	Scale.SetIdentity();
	Scale.SetScale(transform.scale);
	
	// set Rotation
	RotZ.SetIdentity();
	RotZ.SetRotationZ(transform.rotation.z);
	RotY.SetIdentity();
	RotY.SetRotationY(transform.rotation.y);
	RotX.SetIdentity();
	RotX.SetRotationX(transform.rotation.x);

	// set Translation
	Translate.SetIdentity();
	Translate.SetTranslation(transform.position);

	World = Scale * RotZ * RotX * RotY * Translate;
	return World;
}