#pragma once
#include "ConsoleHelper.h"

enum
{
	BOARD_MAX_SIZE =100
};

enum class TileType
{
	NONE =0,
	EMPTY,
	WALL
};

//전방선언을 해 ->나중에 나올꺼니까 너가 알아서 연결하고 일단 그냥 넘어가란 뜻
// 해데끼리는 어지간하면 인쿠르드 하지말아야한다.
//include "pl~~ 이거하지마
class Player;

class Board
{
public:

	Board();
	~Board();

	void			Init(int32 size, Player* player); 
	void			Render();

	void			GenerateMap();
	TileType		GetTileType(Pos pos);
	ConsoleColor	GetTileColor(Pos pos);

	//시작할 좌표 및 마지막 좌표

	Pos				GetEnterPos() { return Pos(1, 1); }
	Pos				GetExitPos() { return Pos(_size - 2, _size - 2); }

private:
	TileType	_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE];
	int32		_size = 0;
	Player*		_player = nullptr;
};

