#include "stdafx.h"
#include "Program.h"
#include "Shader.h" //For complete type, forward declared in class header

#ifdef _DEBUG
#include <iostream>
#endif

glwrap::Program::Program() : handle{glCreateProgram()}
{

}

glwrap::Program::~Program()
{
	glDeleteProgram(handle);
}

unsigned int glwrap::Program::attach(Shader &shader)
{
	glAttachShader(handle, shader.id());
	return glGetError();
}

unsigned int glwrap::Program::detach(Shader &shader)
{
	glDetachShader(handle, shader.id());
	return glGetError();
}

void glwrap::Program::link() const
{
	glLinkProgram(handle);
}

#ifdef _DEBUG
void glwrap::Program::log() const
{
	int status = GL_TRUE;
	GLint maxLength = 0, placed = 0;
	glGetProgramiv(handle, GL_LINK_STATUS, &status);
#ifdef CPP_EXCEPTIONS
	try
	{
#endif
		if(status != GL_TRUE)
		{ 
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &maxLength);
			if (maxLength > 0)
			{
				GLchar *log = new GLchar[maxLength];
				glGetProgramInfoLog(handle, maxLength, &placed, log);
				std::cout << log << std::endl;
				delete[] log;
			}
			glDeleteProgram(handle);
		}
#ifdef CPP_EXCEPTIONS
	}
	catch(std::bad_alloc &e)
	{
		return;
	}
#endif
}
#endif

void glwrap::Program::use() const
{
	glUseProgram(handle);
}

GLint glwrap::Program::attribute(const GLchar *name) const
{
	return glGetAttribLocation(handle, name);
}

GLint glwrap::Program::uniform(const GLchar *name) const
{
	return glGetUniformLocation(handle, name);
}

void glwrap::Program::setBool(GLint location, bool value) const
{
	glUniform1i(location, (int)value);
}

void glwrap::Program::setInt(GLint location, int value) const
{
	glUniform1i(location, value);
}

void glwrap::Program::setUnsigned(GLint location, unsigned value) const
{
	glUniform1ui(location, value);
}

void glwrap::Program::setFloat(GLint location, float value) const
{
	glUniform1f(location, value);
}

void glwrap::Program::setVec2(GLint location, const float *value) const
{
	glUniform2fv(location, 1, value);
}

void glwrap::Program::setVec2(GLint location, float x, float y) const
{
	glUniform2f(location, x, y);
}

void glwrap::Program::setVec3(GLint location, const float *value) const
{
	glUniform3fv(location, 1, value);
}

void glwrap::Program::setVec3(GLint location, float x, float y, float z) const
{
	glUniform3f(location, x, y, z);
}

void glwrap::Program::setVec4(GLint location, const float *value) const
{
	glUniform4fv(location, 1, value);
}

void glwrap::Program::setVec4(GLint location, float x, float y, float z, float w) const
{
	glUniform4f(location, x, y, z, w);
}

void glwrap::Program::setMat2(GLint location, const float *value) const
{
	glUniformMatrix2fv(location, 1, GL_FALSE, value);
}

void glwrap::Program::setMat3(GLint location, const float *value) const
{
	glUniformMatrix3fv(location, 1, GL_FALSE, value);
}

void glwrap::Program::setMat4(GLint location, const float *value) const
{
	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void glwrap::Program::fragOut(GLuint colorNumber, const char *name) const
{
	glBindFragDataLocation(handle, colorNumber, name);
}

GLuint glwrap::Program::id() const
{
	return handle;
}