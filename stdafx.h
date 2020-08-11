// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <Windows.h>

#ifdef _DEBUG
#include <stdexcept>
#include <string>
#include <sstream>
#endif


#include "GL/glew.h"
#define GLFW_DLL
#include "GLFW/glfw3.h"

// TODO: reference additional headers your program requires here
