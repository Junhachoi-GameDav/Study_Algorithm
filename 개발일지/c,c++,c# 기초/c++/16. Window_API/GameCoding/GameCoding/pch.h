#pragma once

#include "Types.h"
#include "Defines.h"
#include "Enums.h"
#include "Utils.h"
#include "Values.h"

#include <Windows.h>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

//c++ 20
#include <format>
// 파일 입출력 관련된 헤더 = 파일탐색기에 있는 기능 전부있다.
#include <filesystem>  //인터넷에서 찾아보면 자료많음
using namespace std;
namespace fs = std::filesystem;

//메모리 누수 확인 가능
#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif