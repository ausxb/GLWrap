#include "stdafx.h"
#include "UBO.h"

glwrap::UBO::UBO(const unsigned int count) : ubo{ 0 }, members{ count }, program{ 0 },
	//Uniform block object values
	uniformBlockIndex{ GL_INVALID_INDEX },
	uniformBlockBinding{ 0 },
	uniformBlockDataSize{ 0 },
	uniformBlockNameLength{ 0 },
	uniformBlockActiveUniforms{ 0 },
	//Member uniform values
	uniformMemberIndices{ nullptr },
	blockTypes{ nullptr },
	blockArraySizes{ nullptr },
	blockNameLengths{ nullptr },
	uniformBlockIndices{ nullptr },
	blockOffsets{ nullptr },
	blockArrayStrides{ nullptr },
	blockMatrixStrides{ nullptr },
	blockIsRowMajor{ nullptr }
{
	glCreateBuffers(1, &ubo);
}

glwrap::UBO::UBO(const GLchar *blockName, const GLchar **qualifiedNames, const unsigned int count, const GLuint prog) : ubo{ 0 }, members{ count }, program{ prog },
	uniformMemberIndices{ new GLuint[members] },
	blockTypes{ new GLint[members] },
	blockArraySizes{ new GLint[members] },
	blockNameLengths{ new GLint[members] },
	uniformBlockIndices{ new GLint[members] },
	blockOffsets{ new GLint[members] },
	blockArrayStrides{ new GLint[members] },
	blockMatrixStrides{ new GLint[members] },
	blockIsRowMajor{ new GLint[members] }
{
	glCreateBuffers(1, &ubo);

	uniformBlockIndex = glGetUniformBlockIndex(program, blockName);

	glGetActiveUniformBlockiv(program, uniformBlockIndex, GL_UNIFORM_BLOCK_BINDING, &uniformBlockBinding);
	glGetActiveUniformBlockiv(program, uniformBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockDataSize);
	glGetActiveUniformBlockiv(program, uniformBlockIndex, GL_UNIFORM_BLOCK_NAME_LENGTH, &uniformBlockNameLength);
	glGetActiveUniformBlockiv(program, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &uniformBlockActiveUniforms);

	glGetUniformIndices(program, members, qualifiedNames, uniformMemberIndices);
	glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_TYPE, blockTypes);
	glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_SIZE, blockArraySizes);
	glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_NAME_LENGTH, blockNameLengths);
	glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_BLOCK_INDEX, uniformBlockIndices);
	glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_OFFSET, blockOffsets);
	glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_ARRAY_STRIDE, blockArrayStrides);
	glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_MATRIX_STRIDE, blockMatrixStrides);
	glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_IS_ROW_MAJOR, blockIsRowMajor);

	glNamedBufferStorage(ubo, uniformBlockDataSize, NULL, GL_MAP_WRITE_BIT);
}


glwrap::UBO::~UBO()
{
	glDeleteBuffers(1, &ubo);
	if (uniformMemberIndices)
		delete[] uniformMemberIndices;
	if (blockTypes)
		delete[] blockTypes;
	if (blockArraySizes)
		delete[] blockArraySizes;
	if (blockNameLengths)
		delete[] blockNameLengths;
	if (uniformBlockIndices)
		delete[] uniformBlockIndices;
	if (blockOffsets)
		delete[] blockOffsets;
	if (blockArrayStrides)
		delete[] blockArrayStrides;
	if (blockMatrixStrides)
		delete[] blockMatrixStrides;
	if (blockIsRowMajor)
		delete[] blockIsRowMajor;
}

void glwrap::UBO::loadNames(const GLchar *blockName, const GLchar **qualifiedNames, const GLuint prog)
{
	if (uniformMemberIndices) //Constructor initialized, would cause memleak
		return;

	program = prog;

	uniformMemberIndices = new GLuint[members];
	glGetUniformIndices(program, members, qualifiedNames, uniformMemberIndices);

	uniformBlockIndex = glGetUniformBlockIndex(prog, blockName);
	glGetActiveUniformBlockiv(program, uniformBlockIndex, GL_UNIFORM_BLOCK_BINDING, &uniformBlockBinding);
	glGetActiveUniformBlockiv(program, uniformBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockDataSize);
	glGetActiveUniformBlockiv(program, uniformBlockIndex, GL_UNIFORM_BLOCK_NAME_LENGTH, &uniformBlockNameLength);
	glGetActiveUniformBlockiv(program, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &uniformBlockActiveUniforms);

	glNamedBufferStorage(ubo, uniformBlockDataSize, NULL, GL_MAP_WRITE_BIT);
}

void glwrap::UBO::assignBindingPoint(GLuint bindingPoint)
{
	if (!uniformMemberIndices) //Litmus test for immediate initialization of all buffers
		return;

	glUniformBlockBinding(
		program,
		uniformBlockIndex,
		bindingPoint
	);
}

void glwrap::UBO::bindBuffer(GLuint bindingPoint)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ubo);
}

const GLuint* glwrap::UBO::uniformIndex()
{
	return uniformMemberIndices; //Could be nullptr, consider removing method
}

const GLint* glwrap::UBO::uniformType()
{
	if (!uniformMemberIndices) //Not all required data is known yet, return without modification
	{
		return nullptr;
	}
	else if (!blockTypes)
	{
		blockTypes = new GLint[members];
		glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_TYPE, blockTypes);
		return blockTypes;
	}
	else
	{
		return blockTypes;
	}
}

const GLint* glwrap::UBO::arraySize()
{
	if (!uniformMemberIndices)
	{
		return nullptr;
	}
	else if (!blockArraySizes)
	{
		blockArraySizes = new GLint[members];
		glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_SIZE, blockArraySizes);
		return blockArraySizes;
	}
	else
	{
		return blockArraySizes;
	}
}

const GLint* glwrap::UBO::nameLength()
{
	if (!uniformMemberIndices)
	{
		return nullptr;
	}
	else if (!blockNameLengths)
	{
		blockNameLengths = new GLint[members];
		glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_NAME_LENGTH, blockNameLengths);
		return blockNameLengths;
	}
	else
	{
		return blockNameLengths;
	}
}

const GLint* glwrap::UBO::blockIndex()
{
	if (!uniformMemberIndices)
	{
		return nullptr;
	}
	else if (!uniformBlockIndices)
	{
		uniformBlockIndices = new GLint[members];
		glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_BLOCK_INDEX, uniformBlockIndices);
		return uniformBlockIndices;
	}
	else
	{
		return uniformBlockIndices;
	}
}

const GLint* glwrap::UBO::uniformOffset()
{
	if (!uniformMemberIndices)
	{
		return nullptr;
	}
	else if (!blockOffsets)
	{
		blockOffsets = new GLint[members];
		glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_OFFSET, blockOffsets);
		return blockOffsets;
	}
	else
	{
		return blockOffsets;
	}
}

const GLint* glwrap::UBO::arrayStride()
{
	if (!uniformMemberIndices)
	{
		return nullptr;
	}
	else if (!blockArrayStrides)
	{
		blockArrayStrides = new GLint[members];
		glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_ARRAY_STRIDE, blockArrayStrides);
		return blockArrayStrides;
	}
	else
	{
		return blockArrayStrides;
	}
}

const GLint* glwrap::UBO::matrixStride()
{
	if (!uniformMemberIndices)
	{
		return nullptr;
	}
	else if (!blockMatrixStrides)
	{
		blockMatrixStrides = new GLint[members];
		glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_MATRIX_STRIDE, blockMatrixStrides);
		return blockMatrixStrides;
	}
	else
	{
		return blockMatrixStrides;
	}
}

const GLint* glwrap::UBO::isRowMajor()
{
	if (!uniformMemberIndices)
	{
		return nullptr;
	}
	else if (!blockIsRowMajor)
	{
		blockIsRowMajor = new GLint[members];
		glGetActiveUniformsiv(program, members, uniformMemberIndices, GL_UNIFORM_IS_ROW_MAJOR, blockIsRowMajor);
		return blockIsRowMajor;
	}
	else
	{
		return blockIsRowMajor;
	}
}

void glwrap::UBO::loadElement(unsigned int index, void *value, unsigned int bytes)
{
	if (!uniformMemberIndices)
		return;
	
	const GLint *off = uniformOffset();

	void *buffer = glMapNamedBufferRange(ubo, off[index], bytes, GL_MAP_WRITE_BIT);
#ifdef _DEBUG
	if (buffer == nullptr)
	{
		GLenum e = glGetError();
		std::ostringstream msg{ "UBO loadElement(): glMapNamedBufferRange() raised " };
		msg << e;
		throw std::runtime_error{ msg.str() };
	}
#endif
	//memcpy(buffer, value, bytes);
	CopyMemory(buffer, value, bytes);
	glUnmapNamedBuffer(ubo);
}

void glwrap::UBO::loadVector(unsigned int index, void *value, unsigned int bytesPer, unsigned int dimension)
{
	if (!uniformMemberIndices)
		return;

	const GLint *off = uniformOffset();

	void *buffer = glMapNamedBufferRange(ubo, off[index], bytesPer * dimension, GL_MAP_WRITE_BIT);
#ifdef _DEBUG
	if (buffer == nullptr)
	{
		GLenum e = glGetError();
		std::ostringstream msg{ "UBO loadVector(): glMapNamedBufferRange() raised " };
		msg << e;
		throw std::runtime_error{ msg.str() };
	}
#endif
	//memcpy(buffer, value, bytesPer * dimension);
	CopyMemory(buffer, value, bytesPer * dimension);
	glUnmapNamedBuffer(ubo);
}

void glwrap::UBO::loadArray(unsigned int index, void *data, unsigned int bytesPer, unsigned int elements)
{
	if (!uniformMemberIndices)
		return;
	 
	const GLint *off = uniformOffset(), *st = arrayStride();
	uintptr_t src = reinterpret_cast<uintptr_t>(data), dst = reinterpret_cast<uintptr_t>(glMapNamedBufferRange(ubo, off[index], elements * st[index], GL_MAP_WRITE_BIT));
	void *buffer = reinterpret_cast<void*>(dst);
#ifdef _DEBUG
	if (buffer == nullptr)
	{
		GLenum e = glGetError();
		std::ostringstream msg{ "UBO loadArray(): glMapNamedBufferRange() raised " };
		msg << e;
		throw std::runtime_error{ msg.str() };
	}
#endif

	for (int n = 0; n < elements; n++)
	{
		buffer = reinterpret_cast<void*>(dst + st[index] * n);
		//memcpy(buffer, reinterpret_cast<void*>(src + n * bytesPer), bytesPer);
		CopyMemory(buffer, reinterpret_cast<void*>(src + n * bytesPer), bytesPer);
	}
	glUnmapNamedBuffer(ubo);
}

void glwrap::UBO::loadMatrix(unsigned int index, void *data, unsigned int bytesPer, unsigned int columns, unsigned int rows)
{
	if (!uniformMemberIndices)
		return;

	const GLint *off = uniformOffset(), *mst = matrixStride();
	uintptr_t src = reinterpret_cast<uintptr_t>(data), dst = reinterpret_cast<uintptr_t>(glMapNamedBufferRange(ubo, off[index], columns * mst[index], GL_MAP_WRITE_BIT));
	void *buffer = reinterpret_cast<void*>(dst);
#ifdef _DEBUG
	if (buffer == nullptr)
	{
		GLenum e = glGetError();
		std::ostringstream msg{ "UBO loadMatrix(): glMapNamedBufferRange() raised " };
		msg << e;
		throw std::runtime_error{ msg.str() };
	}
#endif

	for (int m = 0; m < columns; m++)
	{
		buffer = reinterpret_cast<void*>(dst + mst[index] * m);
		//memcpy(buffer, reinterpret_cast<void*>(src + m * rows * bytesPer), rows * bytesPer);
		CopyMemory(buffer, reinterpret_cast<void*>(src + m * rows * bytesPer), rows * bytesPer);
	}
	glUnmapNamedBuffer(ubo);
}