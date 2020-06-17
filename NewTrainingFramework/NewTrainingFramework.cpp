// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Globals.h"
#include "Object3D.h"
#include "Camera.h"
#include "SkyBox.h"
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
Object3D terrain;
SkyBox ball;
SkyBox skybox;

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
	skybox.InitSkyBox("../Resources/Models/SkyBox.nfg", 
		"../Resources/Textures/SkyBox_Right.tga",
		"../Resources/Textures/SkyBox_Left.tga",
		"../Resources/Textures/SkyBox_Top.tga",
		"../Resources/Textures/SkyBox_Bottom.tga",
		"../Resources/Textures/SkyBox_Front.tga",
		"../Resources/Textures/SkyBox_Back.tga",
		"../Resources/Shaders/CubeShaderVS.vs",
		"../Resources/Shaders/CubeShaderFS.fs");
	ball.InitSkyBox("../Resources/Models/Ball.nfg",
		"../Resources/Textures/SkyBox_Right.tga",
		"../Resources/Textures/SkyBox_Left.tga",
		"../Resources/Textures/SkyBox_Top.tga",
		"../Resources/Textures/SkyBox_Bottom.tga",
		"../Resources/Textures/SkyBox_Front.tga",
		"../Resources/Textures/SkyBox_Back.tga",
		"../Resources/Shaders/EnvMapShaderVS.vs",
		"../Resources/Shaders/EnvMapShaderFS.fs");
	terrain.InitObject3D("../Resources/Models/Terrain.nfg", "../Resources/Textures/Dirt.tga", "../Resources/Shaders/WomanShaderVS.vs", "../Resources/Shaders/WomanShaderFS.fs");

	// Set Transform of 3D Object
	woman1.SetTransform(-0.5f, 0.0f, 2.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f);
	woman2.SetTransform(0.5f, 0.0f, 2.0f, 0.3f, 0.3f, 0.3f, 0.0f, 0.0f, 0.0f);
	camera.SetTransform(0.0f, 0.0f, 4.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	skybox.SetTransform(0.0f, 0.0f, 0.0f, 10.0f, 10.0f, 10.0f, 0.0f, 0.0f, 0.0f);
	ball.SetTransform(0.0f, 1.0f, 2.0f, 0.01f, 0.01f, 0.01f, 0.0f, 0.0f, 0.0f);
	//ball.SetTransform(0.0f, 1.0f, 0.0f, 0.4f, 0.4f, 0.4f, 0.0f, 0.0f, 0.0f);
	terrain.SetTransform(0.0f, -7.0f, 0.0f, 0.15f, 0.15f, 0.15f, 0.0f, 0.0f, 0.0f);

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

	//GLuint iboId;
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

	Matrix View = camera.GetViewMatrix();
	Matrix Projection = camera.GetProjectionMatrix();

	woman1.Draw(View, Projection);

	woman2.Draw(View, Projection);

	skybox.Draw(View, Projection);

	ball.DrawReflection(View, Projection, camera);

	terrain.Draw(View, Projection);

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
		if (GetAsyncKeyState('W'))
			camera.transform.position.y += 0.1f;
		if (GetAsyncKeyState('S'))
			camera.transform.position.y -= 0.1f;
		if (GetAsyncKeyState('A'))
			camera.transform.position.x -= 0.1f;
		if (GetAsyncKeyState('D'))
			camera.transform.position.x += 0.1f;
		if (GetAsyncKeyState('Q'))
		{
			Vector4 forward;
			forward.x = 0.0f;
			forward.y = 0.0f;
			forward.z = 0.1f;
			forward.w = 1.0f;

			Matrix world = camera.GetWorldMatrix();
			Vector4 new_pos = forward * world;
			camera.transform.position.x = new_pos.x;
			camera.transform.position.y = new_pos.y;
			camera.transform.position.z = new_pos.z;
		}
		if (GetAsyncKeyState('E'))
		{
			Vector4 forward;
			forward.x = 0.0f;
			forward.y = 0.0f;
			forward.z = -0.1f;
			forward.w = 1.0f;

			Matrix world = camera.GetWorldMatrix();
			Vector4 new_pos = forward * world;
			camera.transform.position.x = new_pos.x;
			camera.transform.position.y = new_pos.y;
			camera.transform.position.z = new_pos.z;
		}
		if (GetAsyncKeyState(VK_UP))
			camera.transform.rotation.x += 0.05f;
		if (GetAsyncKeyState(VK_DOWN))
			camera.transform.rotation.x -= 0.05f;
		if (GetAsyncKeyState(VK_LEFT))
			camera.transform.rotation.y += 0.05f;
		if (GetAsyncKeyState(VK_RIGHT))
			camera.transform.rotation.y -= 0.05f;
		if (GetAsyncKeyState('Z'))
			camera.transform.rotation.z += 0.05f;
		if (GetAsyncKeyState('C'))
			camera.transform.rotation.z -= 0.05f;
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
	cout << "Press any key..." << endl;;
	_getch();

	return 0;
}

