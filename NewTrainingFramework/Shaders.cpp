#include "stdafx.h"
#include "Shaders.h"

int Shaders::Init( char * fileVertexShader, char * fileFragmentShader )
{
	m_vertexShader = esLoadShader( GL_VERTEX_SHADER, fileVertexShader );

	if( m_vertexShader == 0 )
	{
		return -1;
	}

	m_fragmentShader = esLoadShader( GL_FRAGMENT_SHADER, fileFragmentShader );

	if( m_fragmentShader == 0 )
	{
		glDeleteShader( m_vertexShader );
		return -2;
	}

	m_program = esLoadProgram( m_vertexShader, m_fragmentShader );

	//finding location of attributes
	m_attributes.position = glGetAttribLocation( m_program, "a_posL" );
	m_attributes.normal = glGetAttribLocation(m_program, "a_normal");

	//finding location of uniforms
	m_uniforms.texture = glGetUniformLocation(m_program, "u_texture");
	m_uniforms.textureCoors = glGetAttribLocation(m_program, "a_uv");
	m_uniforms.mvp_matrix = glGetUniformLocation(m_program, "u_world");
	m_uniforms.model = glGetUniformLocation(m_program, "u_w");
	m_uniforms.camera = glGetUniformLocation(m_program, "u_camPosition");
	
	return 0;
}

GLuint Shaders::GetProgram() const
{
	return m_program;
}

Shaders::Attributes Shaders::GetAttributes() const
{
	return m_attributes;
}

Shaders::Uniforms Shaders::GetUniforms() const
{
	return m_uniforms;
}

Shaders::~Shaders()
{
	glDeleteProgram( m_program );
	glDeleteShader( m_vertexShader );
	glDeleteShader( m_fragmentShader );
}