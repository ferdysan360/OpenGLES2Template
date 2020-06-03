#include "stdafx.h"
#include "Model.h"
#include <iostream>
using namespace std;

Model::Model() {
	;
}

Model::~Model() {
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

void Model::InitModel(char* filename) {
	// Woman model load
	Vertex* verticesData;
	int* indicesData;
	FILE* pFile;
	errno_t err = fopen_s(&pFile, filename, "r");
	if (!err) {
		fscanf_s(pFile, "NrVertices: %d", &m_verticesCount);
		fgetc(pFile);

		verticesData = new Vertex[m_verticesCount];
		for (int i = 0; i < m_verticesCount; i++) {
			fscanf_s(pFile, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
				&verticesData[i].pos.x, &verticesData[i].pos.y, &verticesData[i].pos.z, &verticesData[i].norm.x, &verticesData[i].norm.y,
				&verticesData[i].norm.z, &verticesData[i].binorm.x, &verticesData[i].binorm.y, &verticesData[i].binorm.z,
				&verticesData[i].tgt.x, &verticesData[i].tgt.y, &verticesData[i].tgt.z, &verticesData[i].uv.x, &verticesData[i].uv.y);
			fgetc(pFile);
		}

		cout << verticesData[12].pos.x << endl;

		fscanf_s(pFile, "NrIndices: %d", &m_indicesCount);
		fgetc(pFile);

		indicesData = new int[m_indicesCount];
		int indicesPairs = m_indicesCount / 3;
		for (int i = 0; i < indicesPairs; i++) {
			fscanf_s(pFile, "   %*d.    %d,    %d,    %d", &indicesData[i * 3], &indicesData[(i * 3) + 1], &indicesData[(i * 3) + 2]);
			fgetc(pFile);
		}

		cout << indicesData[30] << endl;

		fclose(pFile);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_verticesCount, verticesData, GL_STATIC_DRAW);

		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_indicesCount, indicesData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glEnable(GL_DEPTH_TEST);

		delete indicesData;
		delete verticesData;

		cout << "success! Model loaded!" << endl;
	}
	else {
		cout << "fail to load file" << endl;
	}

}