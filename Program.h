#pragma once
#ifndef PROGRAM_CLASS
#define PROGRAM_CLASS
#include "stdafx.h"

namespace glwrap
{
	class Shader;

	class Program
	{
	private:
		GLuint handle;

	public:
		explicit Program();
		~Program();

		Program(const Program&) = delete;
		Program(Program&&) = delete;
		Program& operator=(const Program&) = delete;
		Program& operator=(Program&&) = delete;

		unsigned int attach(Shader &shader);
		unsigned int detach(Shader &shader);
		void link() const;
#ifdef _DEBUG
		void log() const;
#endif
		void use() const;

		GLint attribute(const GLchar *name) const;
		GLint uniform(const GLchar *name) const;

		void setBool(GLint location, bool value) const;
		void setInt(GLint location, int value) const;
		void setUnsigned(GLint location, unsigned value) const;
		void setFloat(GLint location, float value) const;
		void setVec2(GLint location, const float *value) const;
		void setVec2(GLint location, float x, float y) const;
		void setVec3(GLint location, const float *value) const;
		void setVec3(GLint location, float x, float y, float z) const;
		void setVec4(GLint location, const float *value) const;
		void setVec4(GLint location, float x, float y, float z, float w) const;
		void setMat2(GLint location, const float *value) const;
		void setMat3(GLint location, const float *value) const;
		void setMat4(GLint location, const float *value) const;

		void fragOut(GLuint colorNumber, const char *name) const;
		GLuint id() const;
	};
#endif
}