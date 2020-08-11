#include "stdafx.h"
#include "Shader.h"

#ifdef _DEBUG
#include <iostream>
#endif

glwrap::Shader::Shader(unsigned int shaderType) : i_type{shaderType}, handle{glCreateShader(i_type)}, deleted{false}
{
	
}

glwrap::Shader::~Shader()
{
	if(!deleted)
		glDeleteShader(handle);
}

bool glwrap::Shader::compile(const char *shaderSrc) const
{
	GLint compStatus;

	glShaderSource(handle, 1, &shaderSrc, NULL);

	glCompileShader(handle);
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compStatus);

	if (compStatus != GL_TRUE) 
		return false;

	return true;
}

#ifdef _DEBUG
void glwrap::Shader::log() const
{
	int status = GL_TRUE;
	GLint maxLength = 0, placed = 0;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &maxLength);
		if (maxLength > 0)
		{
			GLchar *errorLog = new GLchar[maxLength];
			glGetShaderInfoLog(handle, maxLength, &placed, errorLog);
			std::cout << errorLog << std::endl;
			delete[] errorLog;
		}
		glDeleteShader(handle);
	}
}
#endif

bool glwrap::Shader::clear()
{
	if(!deleted)
	{
		glDeleteShader(handle);
		deleted = true;
		return true;
	}
	return false;
}

unsigned int glwrap::Shader::type() const
{
	return i_type;
}

GLuint glwrap::Shader::id() const
{
	return handle;
}