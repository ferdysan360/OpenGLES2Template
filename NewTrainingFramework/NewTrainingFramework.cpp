// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

Shaders		myShaders;
Vertex		triangle1[3];
Vertex		triangle2[3];
Vertex		squareTriangle1[3];
Vertex		squareTriangle2[3];

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

	//triangle 2 data
	squareTriangle2[0].pos = Vector3(0.5, 0.5, 0.0);
	squareTriangle2[1].pos = Vector3(-0.5, -0.5, 0.0);
	squareTriangle2[2].pos = Vector3(0.5, -0.5, 0.0);

	//creation of shaders and program 
	myShaders.Init( "../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs" );

	// Woman model load
	Vertex *verticesData;
	int *indicesData;
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "../Resources/Models/Woman1.nfg", "r");
	if (!err) {
		int verticesCount, indicesCount, indicesPair;
		verticesCount = 0;
		indicesCount = 0;

		fscanf_s(pFile, "NrVertices: %d", &verticesCount);
		fgetc(pFile);

		verticesData = new Vertex[verticesCount];
		for (int i = 0; i < verticesCount; i++) {
			fscanf_s(pFile, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
				&verticesData[i].pos.x, &verticesData[i].pos.y, &verticesData[i].pos.z, &verticesData[i].norm.x, &verticesData[i].norm.y,
				&verticesData[i].norm.z, &verticesData[i].binorm.x, &verticesData[i].binorm.y, &verticesData[i].binorm.z,
				&verticesData[i].tgt.x, &verticesData[i].tgt.y, &verticesData[i].tgt.z, &verticesData[i].uv.x, &verticesData[i].uv.y);
			fgetc(pFile);
		}

		fscanf_s(pFile, "NrIndices: %d", &indicesCount);
		fgetc(pFile);

		indicesData = new int[indicesCount];
		int indicesPairs = indicesCount / 3;
		for (int i = 0; i < indicesPairs; i++) {
			fscanf_s(pFile, "   %*d.    %d,    %d,    %d", &indicesData[i*3], &indicesData[(i*3)+1], &indicesData[(i*3)+2]);
			fgetc(pFile);
		}

	}
	else {
		cout << "fail" << endl;
	}
	fclose(pFile);

	GLuint vboId;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);

	GLuint iboId;
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareTriangle1) + sizeof(squareTriangle2), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(squareTriangle1), squareTriangle1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(squareTriangle1), sizeof(squareTriangle2), squareTriangle2);

	int indices[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
	indices[4] = 4;
	indices[5] = 5;

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareTriangle1) + sizeof(squareTriangle2), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(squareTriangle1), squareTriangle1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(squareTriangle1), sizeof(squareTriangle2), squareTriangle2);

	int indices[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
	indices[4] = 4;
	indices[5] = 5;

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

void Update( ESContext *esContext, float deltaTime )
{

}

void Key( ESContext *esContext, unsigned char key, bool bIsPressed )
{

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
	esRegisterDrawFunc(&esContext, DrawSquareIBO);
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

