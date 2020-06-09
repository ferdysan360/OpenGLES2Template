// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Globals.h"
#include "Object3D.h"
#include "Camera.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

Shaders		myShaders;

Vertex		triangle1[3];
Vertex		triangle2[3];
Vertex		squareTriangle1[4];
Vertex		squareTriangle2[3];

Object3D woman1;
Object3D woman2;

Camera camera;

int Init( ESContext *esContext )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	
	//triangle 1 data
	triangle1[0].pos = Vector3(-0.5, 0.5, 0.0);
	triangle1[1].pos = Vector3(-1.0, -0.5, 0.0);
	triangle1[2].pos = Vector3(0.0, -0.5, 0.0);

	//triangle 2 data
	triangle2[0].pos = Vector3(0.5, 0.5, 0.0);
	triangle2[1].pos = Vector3(0.0, -0.5, 0.0);
	triangle2[2].pos = Vector3(1.0, -0.5, 0.0);

	//triangle 1 data
	squareTriangle1[0].pos = Vector3( 0.5,  0.5,  0.0 );
	squareTriangle1[1].pos = Vector3( -0.5, 0.5,  0.0 );
	squareTriangle1[2].pos = Vector3(  -0.5, -0.5,  0.0 );
	squareTriangle1[3].pos = Vector3(0.5, -0.5, 0.0);

	// Init 3D Object
	woman1.InitObject3D("../Resources/Models/Woman1.nfg", "../Resources/Textures/Woman1.tga", "../Resources/Shaders/WomanShaderVS.vs", "../Resources/Shaders/WomanShaderFS.fs");
	woman2.InitObject3D("../Resources/Models/Woman2.nfg", "../Resources/Textures/Woman2.tga", "../Resources/Shaders/WomanShaderVS.vs", "../Resources/Shaders/WomanShaderFS.fs");

	// Set Transform of 3D Object
	woman1.SetTransform(-0.5f, 0.0f, 2.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f);
	woman2.SetTransform(0.5f, 0.0f, 2.0f, 0.3f, 0.3f, 0.3f, 0.0f, 0.0f, 0.0f);
	camera.SetTransform(0.0f, 0.0f, 4.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

	//creation of shaders and program 
	myShaders.Init( "../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs" );

	return 0;
}

void DrawTwoTriangles( ESContext *esContext )
{
	glClear( GL_COLOR_BUFFER_BIT );

	
	GLuint vboId;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1) + sizeof(triangle2), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangle1), triangle1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangle1), sizeof(triangle2), triangle2);
	
	glUseProgram( myShaders.GetProgram() );

	if( myShaders.GetAttributes().position != -1 )
	{
		glEnableVertexAttribArray( myShaders.GetAttributes().position );
		glVertexAttribPointer( myShaders.GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), 0);
	}

	glDrawArrays( GL_TRIANGLES, 0, 6 );

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers( esContext->eglDisplay, esContext->eglSurface );
}

void DrawSquare(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint vboId;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareTriangle1), squareTriangle1, GL_STATIC_DRAW);

	int indices[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	GLuint iboId;
	//glGenBuffers(1, &iboId);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(squareTriangle1), squareTriangle1);
	//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareTriangle1), sizeof(squareTriangle2), squareTriangle2);

	glUseProgram(myShaders.GetProgram());

	if (myShaders.GetAttributes().position != -1)
	{
		glEnableVertexAttribArray(myShaders.GetAttributes().position);
		glVertexAttribPointer(myShaders.GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void DrawSquareIBO(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint vboId;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareTriangle1), squareTriangle1, GL_STATIC_DRAW);

	int indices[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	GLuint iboId;
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glUseProgram(myShaders.GetProgram());

	if (myShaders.GetAttributes().position != -1)
	{
		glEnableVertexAttribArray(myShaders.GetAttributes().position);
		glVertexAttribPointer(myShaders.GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void DrawModel(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Matrix World1 = woman1.GetWorldMatrix();
	Matrix View = camera.GetViewMatrix();
	Matrix Projection = camera.GetProjectionMatrix();

	// woman 1
	glBindTexture(GL_TEXTURE_2D, woman1.texture.textureID);

	glUseProgram(woman1.shaders.GetProgram());

	glUniform1i(woman1.shaders.GetUniforms().texture, 0);

	glBindBuffer(GL_ARRAY_BUFFER, woman1.model.m_VBO);

	Matrix MVPMatrix1 = World1 * View * Projection;
	if (woman1.shaders.GetUniforms().mvp_matrix != -1) {
		glUniformMatrix4fv(woman1.shaders.GetUniforms().mvp_matrix, 1, GL_FALSE, MVPMatrix1.m[0]);
	}
	else {
		cout << "no matrix!" << endl;
	}
	

	if (woman1.shaders.GetAttributes().position != -1)
	{
		glEnableVertexAttribArray(woman1.shaders.GetAttributes().position);
		glVertexAttribPointer(woman1.shaders.GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	else {
		cout << "no position" << endl;
	}

	if (woman1.shaders.GetUniforms().textureCoors != -1)
	{
		glEnableVertexAttribArray(woman1.shaders.GetUniforms().textureCoors);
		glVertexAttribPointer(woman1.shaders.GetUniforms().textureCoors, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}
	else
	{
		cout << "no texture coors!" << endl;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, woman1.model.m_IBO);

	glDrawElements(GL_TRIANGLES, woman1.model.m_indicesCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, woman1.m_verticesCount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// -----------------------------------

	// woman 2
	glBindTexture(GL_TEXTURE_2D, woman2.texture.textureID);

	glUseProgram(woman2.shaders.GetProgram());

	glUniform1i(woman2.shaders.GetUniforms().texture, 0);

	glBindBuffer(GL_ARRAY_BUFFER, woman2.model.m_VBO);

	Matrix World2 = woman2.GetWorldMatrix();
	Matrix MVPMatrix2 = World2 * View * Projection;
	if (woman2.shaders.GetUniforms().mvp_matrix != -1) {
		glUniformMatrix4fv(woman2.shaders.GetUniforms().mvp_matrix, 1, GL_FALSE, MVPMatrix2.m[0]);
	}
	else {
		cout << "no matrix!" << endl;
	}

	if (woman2.shaders.GetAttributes().position != -1)
	{
		glEnableVertexAttribArray(woman2.shaders.GetAttributes().position);
		glVertexAttribPointer(woman2.shaders.GetAttributes().position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	else {
		cout << "no position" << endl;
	}

	if (woman2.shaders.GetUniforms().textureCoors != -1)
	{
		glEnableVertexAttribArray(woman2.shaders.GetUniforms().textureCoors);
		glVertexAttribPointer(woman2.shaders.GetUniforms().textureCoors, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}
	else
	{
		cout << "no texture coors!" << endl;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, woman2.model.m_IBO);

	glDrawElements(GL_TRIANGLES, woman2.model.m_indicesCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, woman1.m_verticesCount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update( ESContext *esContext, float deltaTime )
{
	woman1.transform.rotation.y += 1.0f * deltaTime;
	woman2.transform.rotation.z += 1.0f * deltaTime;
}

void Key( ESContext *esContext, unsigned char key, bool bIsPressed )
{
	if (bIsPressed) {
		switch (key) {
			case 'W':
				camera.transform.position.y += 0.1f;
				break;
			case 'S':
				camera.transform.position.y -= 0.1f;
				break;
			case 'A':
				camera.transform.position.x -= 0.1f;
				break;
			case 'D':
				camera.transform.position.x += 0.1f;
				break;
			case 'Q':
				camera.transform.position.z += 0.1f;
				break;
			case 'E':
				camera.transform.position.z -= 0.1f;
				break;
			case VK_UP:
				camera.transform.rotation.x += 0.05f;
				break;
			case VK_DOWN:
				camera.transform.rotation.x -= 0.05f;
				break;
			case VK_LEFT:
				camera.transform.rotation.y += 0.05f;
				break;
			case VK_RIGHT:
				camera.transform.rotation.y -= 0.05f;
				break;
			case 'Z':
				camera.transform.rotation.z += 0.05f;
				break;
			case 'C':
				camera.transform.rotation.z -= 0.05f;
				break;
		}
	}
}

void CleanUp()
{
	//Cleaning up the buffers
	
	//glDeleteBuffers( 1, &vboId );
	//glDeleteBuffers( 1, &iboId );
}

int _tmain( int argc, _TCHAR* argv[] )
{
	ESContext esContext;

	esInitContext( &esContext );

	esCreateWindow( &esContext, "Hello OpenGLES 2", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH );

	if( Init( &esContext ) != 0 )
		return 0;

	//esRegisterDrawFunc( &esContext, DrawTwoTriangles );
	//esRegisterDrawFunc( &esContext, DrawSquare );
	//esRegisterDrawFunc(&esContext, DrawSquareIBO);
	esRegisterDrawFunc(&esContext, DrawModel);
	esRegisterUpdateFunc( &esContext, Update );
	esRegisterKeyFunc( &esContext, Key );

	esMainLoop( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf( "Press any key...\n" );
	_getch();

	return 0;
}

