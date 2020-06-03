#pragma once
#include "../Utilities/utilities.h"

class Model {
public:
	GLuint m_VBO, m_IBO;
	unsigned int m_indicesCount, m_verticesCount;
	Model();
	~Model();
	void InitModel(char* filename);
};