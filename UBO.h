#pragma once
#include "stdafx.h"

namespace glwrap
{
	class UBO
	{
	private:
		GLuint ubo;
		unsigned int members;
		GLuint program;
		GLuint uniformBlockIndex;
		GLint uniformBlockBinding,
			uniformBlockDataSize,
			uniformBlockNameLength,
			uniformBlockActiveUniforms; //uniformBlockActiveUniformIndices would be redundant
		GLuint* uniformMemberIndices;
		GLint *blockTypes,
			*blockArraySizes,
			*blockNameLengths,
			*uniformBlockIndices,
			*blockOffsets,
			*blockArrayStrides,
			*blockMatrixStrides,
			*blockIsRowMajor;
	public:
		UBO(const unsigned int count); //Delayed load, used when the shader program has not been set up yet
		UBO(const GLchar *blockName, const GLchar **qualifiedNames, const unsigned int count, const GLuint prog); //Program must be a valid operational program
		~UBO();

		void loadNames(const GLchar *blockName, const GLchar **qualifiedNames, const GLuint prog);
		void assignBindingPoint(GLuint bindingPoint); //Called if binding point is not specified in shader
		void bindBuffer(GLuint bindingPoint); //Called once binding point is assigned or known

		const GLuint* uniformIndex();
		const GLint* uniformType();
		const GLint* arraySize();
		const GLint* nameLength();
		const GLint* blockIndex();
		const GLint* uniformOffset();
		const GLint* arrayStride();
		const GLint* matrixStride();
		const GLint* isRowMajor();

		//Each member is specified with the index of the member in the array of member names originally used to get the uniform indices
		void loadElement(unsigned int index, void *value, unsigned int bytes);
		void loadVector(unsigned int index, void *value, unsigned int bytesPer, unsigned int dimension);
		void loadArray(unsigned int index, void *data, unsigned int bytesPer, unsigned int elements);
		void loadMatrix(unsigned int index, void *data, unsigned int bytesPer, unsigned int columns, unsigned int rows); //GLSL is column major
		//CreateMultiUBO to allow one buffer to hold data for multiple uniform blocks using glBindBufferRange() to streamline ops
	};
}
