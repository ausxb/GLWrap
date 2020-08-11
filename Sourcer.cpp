#include "stdafx.h"
#include "Sourcer.h"

glwrap::Sourcer::Sourcer(LPCWSTR file) :
	data{ nullptr },
	fh{ CreateFile( file, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) },
	bytes{ 0 }
{
	if (fh == INVALID_HANDLE_VALUE)
	{
		flen.QuadPart = 0;
	}
	else
	{
		GetFileSizeEx(fh, &flen);
		data = static_cast<char*>(HeapAlloc(GetProcessHeap(), 0, flen.QuadPart + 1));
		ReadFile(fh, data, flen.QuadPart, &bytes, 0);
		data[flen.QuadPart] = '\0';
	}
}

LONGLONG glwrap::Sourcer::length() const
{
	return bytes;
}

const char* glwrap::Sourcer::string() const
{
	return data;
}

glwrap::Sourcer::operator bool() const
{
	return fh != INVALID_HANDLE_VALUE;
}

glwrap::Sourcer::~Sourcer()
{
	HeapFree(GetProcessHeap(), 0, data);
	data = nullptr;
	CloseHandle(fh);
	bytes = 0;
	flen.QuadPart = 0;
}
