#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class Utils
{
public:
	static void DrowText(HDC hdc, Pos pos, const wstring& str);

	static void DrowReat(HDC hdc, Pos pos, int32 w, int32 h);

	static void DrowCircle(HDC hdc, Pos pos, int32 radius);

	static void DrowLine(HDC hdc, Pos from, Pos to);


};

