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

//���漱���� �� ->���߿� ���ò��ϱ� �ʰ� �˾Ƽ� �����ϰ� �ϴ� �׳� �Ѿ�� ��
// �ص������� �������ϸ� ������ �������ƾ��Ѵ�.
//include "pl~~ �̰�������
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

	//������ ��ǥ �� ������ ��ǥ

	Pos				GetEnterPos() { return Pos(1, 1); }
	Pos				GetExitPos() { return Pos(_size - 2, _size - 2); }

private:
	TileType	_tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE];
	int32		_size = 0;
	Player*		_player = nullptr;
};

