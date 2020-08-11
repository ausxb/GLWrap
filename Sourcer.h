#pragma once
#include "stdafx.h"

namespace glwrap
{
	class Sourcer
	{
	private:
		char *data;
		HANDLE fh;
		DWORD bytes;
		LARGE_INTEGER flen;
	public:
		Sourcer(LPCWSTR file);
		LONGLONG length() const;
		const char* string() const;
		operator bool() const;
		~Sourcer();
	};

}
