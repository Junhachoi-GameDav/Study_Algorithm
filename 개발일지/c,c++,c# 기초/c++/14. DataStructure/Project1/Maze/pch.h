#pragma once

//여기에 계속 사용할 헤더를 모아놓으면 된다.

#include "Types.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//모두다 public으로 설정한거니까 구조체
struct Pos
{
	Pos() {}
	Pos(int32 y, int32 x) : y(y), x(x) {}

	// 일일히 다른 함수에서 조건으로 비교할필요없이 여기서 비교해서 
	// 리턴하자

	bool operator == (const Pos& other)
	{
		// y랑 상대방의 y랑 비교 && x랑 상대방의 x랑 비교 (둘다 같으면 true 리턴)
		return y == other.y && x == other.x;
	}

	bool operator != (const Pos& other)
	{
		return !(*this == other); //자신을 주소(포이터)로 타고가서 트루면 펄스 내보내라
	}

	Pos operator+(const Pos& other)
	{
		Pos ret;
		ret.y = y + other.y;
		ret.x = x + other.x;
		return ret;
	}

	Pos& operator+=(const Pos& other)
	{
		y += other.y;
		x += other.x;
		return *this;
	}

	int32 y = 0;
	int32 x = 0;
};

enum Dir
{
	DIR_UP		= 0,
	DIR_LEFT	= 1,
	DIR_DOWN	= 2,
	DIR_RIGHT	= 3,

	DIR_COUNT	= 4,
};