#pragma once
#include "Vector.h" //엄청 간단한거니까 그냥 헤더 파일 넣ㅇ어씅ㅁ

class Board;

class Player
{
	enum
	{
		MOVE_TICK = 100
	};
public:

	void	Init(Board* board);
	void	Update(uint64 deltaTick);


	void	SetPos(Pos pos) { _pos = pos; }
	Pos		GetPos() { return _pos; }

	bool	CanGo(Pos pos);

private:
	void	CalculatePath();

private:
	Pos		_pos;
	int32	_dir = DIR_UP;
	Board*	_board = nullptr;

	//동적 배열
	Vector	_path;
	int32	_pathIndex = 0;
	uint64	_sumTick = 0;
};

