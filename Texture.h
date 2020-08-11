#pragma once
#include "stdafx.h"

namespace glwrap
{
	class Texture
	{
	private:
		GLuint handle;
		GLenum i_type, i_format;
		GLsizei w, h, d, mips;
	public:
		Texture(GLenum target, GLsizei levels, GLenum format, GLsizei width, GLsizei height, GLsizei depth);
		~Texture();

		void store(GLint miplevel, GLenum channelformat, GLenum datatype, const void *data);
		void storeSlice(GLint miplevel, GLint slice, GLenum channelformat, GLenum datatype, const void *data);
		void bind(GLuint unit) const;

		GLenum type() const;
		GLuint id() const;
	};
}
