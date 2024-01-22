#pragma once

#include "Types.h"
#include "Defines.h"
#include "Enums.h"

#include <Windows.h>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <format>
using namespace std;

//메모리 누수 확인 가능
#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif