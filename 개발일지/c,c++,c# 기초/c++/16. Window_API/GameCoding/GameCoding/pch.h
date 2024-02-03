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
// ���� ����� ���õ� ��� = ����Ž���⿡ �ִ� ��� �����ִ�.
#include <filesystem>  //���ͳݿ��� ã�ƺ��� �ڷḹ��
using namespace std;
namespace fs = std::filesystem;

//�޸� ���� Ȯ�� ����
#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif