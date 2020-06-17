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

void Object3D::Draw(Matrix View, Matrix Projection) {
	// woman 1
	glBindTexture(GL_TEXTURE_2D, this->texture.textureID);

	glUseProgram(this->shaders.GetProgram());

	glUniform1i(this->shaders.GetUniforms().texture, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->model.m_VBO);

	Matrix World1 = this->GetWorldMatrix();
	Matrix MVPMatrix1 = World1 * View * Projection;
	if (this->shaders.GetUniforms().mvp_matrix != -1) {
		glUniformMatrix4fv(this->shaders.GetUniforms().mvp_matrix, 1, GL_FALSE, MVPMatrix1.m[0]);
	}
	else {
		cout << "no matrix!" << endl;
	}


	if (this->shaders.GetAttributes().position != -1)
	{
		glEnableVertexAttribArray(this->shaders.GetAttributes().position);
		glVertexAttribPointer(this->shaders.GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	else {
		cout << "no position" << endl;
	}

	if (this->shaders.GetUniforms().textureCoors != -1)
	{
		glEnableVertexAttribArray(this->shaders.GetUniforms().textureCoors);
		glVertexAttribPointer(this->shaders.GetUniforms().textureCoors, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}
	else
	{
		cout << "no texture coors!" << endl;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->model.m_IBO);

	glDrawElements(GL_TRIANGLES, this->model.m_indicesCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, this->m_verticesCount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}