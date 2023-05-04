#pragma once

//미리 컴파일된 헤더
#include <Windows.h>

#include <crtdbg.h>
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <map>
using std::map;
using std::make_pair;

#include<string>
using std::string;
using std::wstring;

#include <assert.h>
//#ifdef UNITY_BUILDe
#include "define.h"
//#endif

#include "struct.h"
#include "math.h"
#include "func.h"

#pragma comment(lib, "Msimg32.lib")

#include <cstddef>

#include <objidl.h>
#include <gdiplus.h>

using namespace Gdiplus;

#pragma comment(lib,"Gdiplus.lib")
