#include "stdafx.h"
#include "Sampler.h"


glwrap::Sampler::Sampler()
{
	glCreateSamplers(1, &handle);
}


glwrap::Sampler::~Sampler()
{
	glDeleteSamplers(1, &handle);
}

void glwrap::Sampler::set(GLenum pname, GLint param)
{
	glSamplerParameteri(handle, pname, param);
}

void glwrap::Sampler::set(GLenum pname, GLfloat param)
{
	glSamplerParameterf(handle, pname, param);
}

void glwrap::Sampler::bind(GLuint unit) const
{
	glBindSampler(unit, handle);
}

GLuint glwrap::Sampler::id() const
{
	return handle;
}
