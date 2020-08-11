#pragma once

namespace glwrap
{
	class Sampler
	{
	private:
		GLuint handle;
	public:
		Sampler();
		~Sampler();
		void set(GLenum pname, GLint param);
		void set(GLenum pname, GLfloat param);
		void bind(GLuint unit) const;
		GLuint id() const;
	};
}