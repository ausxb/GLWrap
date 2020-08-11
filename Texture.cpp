#include "stdafx.h"
#include "Texture.h"


glwrap::Texture::Texture(GLenum target, GLsizei levels, GLenum format, GLsizei width, GLsizei height, GLsizei depth)
	: i_type{ target }, i_format{ format }, w{ width }, h{ height }, d{ depth }, mips { levels }
{
	glCreateTextures(target, 1, &handle);
	switch (i_type)
	{
	case GL_TEXTURE_1D:
		glTextureStorage1D(handle, mips, i_format, w);
		break;
	case GL_TEXTURE_2D:
	case GL_TEXTURE_1D_ARRAY:
		glTextureStorage2D(handle, mips, i_format, w, h);
		break;
	case GL_TEXTURE_3D:
	case GL_TEXTURE_2D_ARRAY:
		glTextureStorage3D(handle, mips, i_format, w, h, d);
		break;
	}
#ifdef _DEBUG
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		std::ostringstream msg{ "Texture constructor: error " };
		msg << e;
		throw std::runtime_error{ msg.str() };
	}
#endif
}

void glwrap::Texture::store(GLint miplevel, GLenum channelformat, GLenum datatype, const void *data)
{
	switch (i_type)
	{
	case GL_TEXTURE_1D:
		glTextureSubImage1D(handle, miplevel, 0, w, channelformat, datatype, data);
		break;
	case GL_TEXTURE_2D:
		glTextureSubImage2D(handle, miplevel, 0, 0, w, h, channelformat, datatype, data);
		break;
	case GL_TEXTURE_3D:
		glTextureSubImage3D(handle, miplevel, 0, 0, 0, w, h, d, channelformat, datatype, data);
		break;
	}
#ifdef _DEBUG
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		std::ostringstream msg{ "Texture store(): error " };
		msg << e;
		throw std::runtime_error{ msg.str() };
	}
#endif
}

void glwrap::Texture::storeSlice(GLint miplevel, GLint slice, GLenum channelformat, GLenum datatype, const void *data)
{
	switch (i_type)
	{
	case GL_TEXTURE_1D_ARRAY:
		glTextureSubImage2D(handle, miplevel, 0, slice, w, 1, channelformat, datatype, data);
		break;
	case GL_TEXTURE_2D_ARRAY:
		glTextureSubImage3D(handle, miplevel, 0, 0, slice, w, h, 1, channelformat, datatype, data);
		break;
	}
#ifdef _DEBUG
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		std::ostringstream msg{ "Texture storeSlice(): error " };
		msg << e;
		throw std::runtime_error{ msg.str() };
	}
#endif
}

void glwrap::Texture::bind(GLuint unit) const
{
	glBindTextureUnit(unit, handle);
}

glwrap::Texture::~Texture()
{
	glDeleteTextures(1, &handle);
}

GLenum glwrap::Texture::type() const
{
	return i_type;
}

GLuint glwrap::Texture::id() const
{
	return handle;
}
