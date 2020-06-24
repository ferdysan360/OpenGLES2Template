#include "stdafx.h"
#include "SkyBox.h"
#include <iostream>
using namespace std;

void SkyBox::InitSkyBox(char* model_filename, char* PX, char* NX, char* PY, char* NY, char* PZ, char* NZ, char* vs_filename, char* fs_filename) {
	model->InitModel(model_filename);
	texture->InitSkyBoxTexture(PX, NX, PY, NY, PZ, NZ);
	shaders->Init(vs_filename, fs_filename);
}

void SkyBox::Draw(Matrix View, Matrix Projection) {
	// skybox
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture->textureID);

	glUseProgram(this->shaders->GetProgram());

	glUniform1i(this->shaders->GetUniforms().texture, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->model->m_VBO);

	Matrix World3 = this->GetWorldMatrix();
	Matrix MVPMatrix3 = World3 * View * Projection;
	if (this->shaders->GetUniforms().mvp_matrix != -1) {
		glUniformMatrix4fv(this->shaders->GetUniforms().mvp_matrix, 1, GL_FALSE, MVPMatrix3.m[0]);
	}
	else {
		cout << "no matrix!" << endl;
	}

	if (this->shaders->GetAttributes().position != -1)
	{
		glEnableVertexAttribArray(this->shaders->GetAttributes().position);
		glVertexAttribPointer(this->shaders->GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	else {
		cout << "no position" << endl;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->model->m_IBO);

	glDrawElements(GL_TRIANGLES, this->model->m_indicesCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, this->m_verticesCount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void SkyBox::DrawReflection(Matrix View, Matrix Projection, Camera camera) {
	// ball
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture->textureID);

	glUseProgram(this->shaders->GetProgram());

	glUniform1i(this->shaders->GetUniforms().texture, 0);

	glBindBuffer(GL_ARRAY_BUFFER, this->model->m_VBO);

	Matrix World4 = this->GetWorldMatrix();
	Matrix MVPMatrix4 = World4 * View * Projection;
	if (this->shaders->GetUniforms().mvp_matrix != -1) {
		glUniformMatrix4fv(this->shaders->GetUniforms().mvp_matrix, 1, GL_FALSE, MVPMatrix4.m[0]);
	}
	else {
		cout << "no matrix!" << endl;
	}

	if (this->shaders->GetAttributes().position != -1)
	{
		glEnableVertexAttribArray(this->shaders->GetAttributes().position);
		glVertexAttribPointer(this->shaders->GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	else {
		cout << "no position" << endl;
	}

	if (this->shaders->GetAttributes().normal != -1)
	{
		glEnableVertexAttribArray(this->shaders->GetAttributes().normal);
		glVertexAttribPointer(this->shaders->GetAttributes().normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) + sizeof(Vector2));
	}
	else {
		cout << "no normal" << endl;
	}

	if (this->shaders->GetUniforms().model != -1) {
		glUniformMatrix4fv(this->shaders->GetUniforms().model, 1, GL_FALSE, World4.m[0]);
	}
	else {
		cout << "no model matrix!" << endl;
	}

	glBindBuffer(GL_ARRAY_BUFFER, camera.model->m_VBO);

	if (this->shaders->GetUniforms().camera != -1) {
		glEnableVertexAttribArray(this->shaders->GetUniforms().camera);
		glVertexAttribPointer(this->shaders->GetUniforms().camera, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	else {
		cout << "no camera pos!" << endl;
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->model->m_VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->model->m_IBO);

	glDrawElements(GL_TRIANGLES, this->model->m_indicesCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, ball.m_verticesCount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}