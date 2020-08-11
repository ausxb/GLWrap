#pragma once
#ifndef SHADER_CLASS
#define SHADER_CLASS
#include "stdafx.h"

namespace glwrap
{
	class Shader
	{
	private:
		GLenum i_type;
		GLuint handle;
		bool deleted;

	public:
		/*static constexpr unsigned int VTX_SHD = GL_VERTEX_SHADER;
		static constexpr unsigned int TC_SHD = GL_TESS_CONTROL_SHADER;
		static constexpr unsigned int TE_SHD = GL_TESS_EVALUATION_SHADER;
		static constexpr unsigned int GEOM_SHD = GL_GEOMETRY_SHADER;
		static constexpr unsigned int FRG_SHD = GL_FRAGMENT_SHADER;*/

		explicit Shader(unsigned int shaderType);
		~Shader();

		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) = delete;

		bool compile(const char *shaderSrc) const;
#ifdef _DEBUG
		void log() const;
#endif
		bool clear();
		unsigned int type() const;
		GLuint id() const;
	};
}
#endif