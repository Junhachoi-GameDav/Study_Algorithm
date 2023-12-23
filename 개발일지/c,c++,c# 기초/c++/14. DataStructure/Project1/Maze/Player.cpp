#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	CalculatePath();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size()) { return; }

	_sumTick += deltaTick;

	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;
		
		//이동
		_pos = _path[_pathIndex];
		_pathIndex++;
	}
		
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::CalculatePath()
{
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	//목적지
	Pos dest = _board->GetExitPos();

	//_dir;	//내가 보는 방향
	//pos;	//현재 좌표

	//스위치 문으로 만들수도있지만 이게더 고급진 방법
	//2d 게임에서 굉장히 많이쓰는 방법이란다.
	Pos front[4]
	{
		Pos(-1,0),	//up
		Pos(0,-1),	//left
		Pos(1,0),	//down
		Pos(0,1),	//right
	};

	//for (int i = 0; i < 20; i++)
	//{
	//	//Pos next = pos + front[_dir];

	//	if (CanGo(pos + front[_dir]))
	//	{
	//		pos += front[0];
	//		_path.push_back(pos);
	//	}
	//	else if (CanGo(pos + front[1]))
	//	{
	//		pos += Pos(1, 0);
	//		_path.push_back(pos);
	//	}
	//	else if (CanGo(pos + front[2]))
	//	{
	//		pos += Pos(1, 0);
	//		_path.push_back(pos);
	//	}
	//	else if (CanGo(pos + front[3]))
	//	{
	//		pos += Pos(1, 0);
	//		_path.push_back(pos);
	//	}
	//	pos += front[2];
	//	_path.push_back(pos);
	//}

	_dir = DIR_UP; //0

	while (pos != dest)
	{
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))
		{
			//회전
			_dir = (_dir - 1) % DIR_COUNT;
			//한칸이동
			pos += front[_dir];
			//기록
			_path.push_back(pos);
			
		}
		else if (CanGo(pos + front[_dir]))
		{
			//한칸이동
			pos += front[_dir];
			//기록
			_path.push_back(pos);
		}
		else
		{
			_dir = (_dir + 1) % DIR_COUNT;
		}

		if (pos == dest) { break; }
	}

	//내가 바라보는 방향 기준 앞에 있는 좌표
	//Pos next = pos + front[_dir];
	// 오른쪽으로 90도 회전
	//_dir = (_dir - 1) % DIR_COUNT;
	// 왼쪽으로 90도 회전
	//_dir = (_dir + 1) % DIR_COUNT;

	//int32 newDir = _dir;

	//목적지를 찾을때까지
	//while (pos != dest)
	//{
	//	//1. 현재 바라보는 방향기준으로  오른쪽으로 갈수있는지 확인
	//	int32 newDir = (_dir - 1) % DIR_COUNT;
	//	if (CanGo(pos + front[newDir]))
	//	{
	//		//오른쪽으로 90도 회전
	//		_dir = (_dir - 1) % DIR_COUNT;
	//		//앞으로 한 보 전진
	//		pos += front[_dir];
	//		//좌표 기록
	//		_path.push_back(pos);
	//		
	//	}
	//	//2. 전진 할수 있는지 확인
	//	else if (CanGo(pos + front[3]))
	//	{
	//		//앞으로 한 보 전진
	//		pos += front[_dir];
	//		//좌표 기록
	//		_path.push_back(pos);
	//	}
	//	// 3.둘다 아닐때 돌기
	//	else
	//	{
	//		//왼쪽으로 90도 회전
	//		_dir = (_dir + 1) % DIR_COUNT;
	//	}
	//}
}
