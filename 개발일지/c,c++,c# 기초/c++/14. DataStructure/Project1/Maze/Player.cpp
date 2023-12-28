#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//CalculatePath_right_hand();
	CalculatePath_BFS();
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

void Player::CalculatePath_right_hand()
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



	//목적지를 찾을때까지
	//_dir = DIR_UP; //0

	//while (pos != dest)
	//{
	//	int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
	//	if (CanGo(pos + front[newDir]))
	//	{
	//		//회전
	//		_dir = (_dir - 1) % DIR_COUNT;
	//		//한칸이동
	//		pos += front[_dir];
	//		//기록
	//		_path.push_back(pos);
	//		
	//	}
	//	else if (CanGo(pos + front[_dir]))
	//	{
	//		//한칸이동
	//		pos += front[_dir];
	//		//기록
	//		_path.push_back(pos);
	//	}
	//	else
	//	{
	//		_dir = (_dir + 1) % DIR_COUNT;
	//	}

	//	if (pos == dest) { break; }
	//}

	//내가 바라보는 방향 기준 앞에 있는 좌표
	//Pos next = pos + front[_dir];
	// 오른쪽으로 90도 회전
	//_dir = (_dir - 1) % DIR_COUNT;
	// 왼쪽으로 90도 회전
	//_dir = (_dir + 1) % DIR_COUNT;

	//int32 newDir = _dir;
	
}

void Player::CalculatePath_BFS()
{
	Pos pos = _pos;
	//목적지
	Pos dest = _board->GetExitPos();

	Pos front[4]
	{
		Pos(-1,0),	//up
		Pos(0,-1),	//left
		Pos(1,0),	//down
		Pos(0,1),	//right
	};

	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));
	// discovered[y][x] ?


	// extra)
	// parant[y][x] = pos -> (y, x) pos에 의해 발견됨
	vector<vector<Pos>> parant(size, vector<Pos>(size, Pos(-1, -1)));

	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;

	//초기화
	parant[pos.y][pos.x] = pos; //자기자신에 의해서 발견


	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		//목적지 도착
		if (pos == dest) { break; }

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = pos + front[dir];
			//갈수 있는 지역은 맞는지 확인
			if (CanGo(nextPos) == false) { continue; }

			//이미 다른 경로에 의해 발견한 지역
			if (discovered[nextPos.y][nextPos.x]) { continue; }

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parant[nextPos.y][nextPos.x] = pos;
		}
	}

	//패스
	_path.clear();
	//_path.push_back(pos);
	pos = dest; //목적지부터시작

	while (true)
	{
		_path.push_back(pos);

		//시작점
		if (pos == parant[pos.y][pos.x]) { break; }
		//덮어쓰기 (뒤에서부터)
		pos = parant[pos.y][pos.x];
	}

	//거꾸로 돌리기
	/*vector<Pos> temp(_path.size());
	for (int i = 0; i < _path.size(); i++)
	{
		temp[i] = _path[_path.size() - 1 - i];
	}
	_path = temp;*/

	//이런 방법도 있다.
	std::reverse(_path.begin(), _path.end());
}
