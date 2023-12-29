#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//CalculatePath_right_hand();
	//CalculatePath_BFS();
	CalculatePath_AStar();
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
	// parent[y][x] = pos -> (y, x) pos에 의해 발견됨
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;

	//초기화
	parent[pos.y][pos.x] = pos; //자기자신에 의해서 발견


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
			parent[nextPos.y][nextPos.x] = pos;
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
		if (pos == parent[pos.y][pos.x]) { break; }
		//덮어쓰기 (뒤에서부터)
		pos = parent[pos.y][pos.x];
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


struct PQNode
{
	PQNode(int32 f, int32 g, Pos pos) : f(f), g(g) , pos(pos) {}

	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }


	int32 f;
	int32 g;
	Pos pos;
};

void Player::CalculatePath_AStar()
{
	// 채점
	// - 입구에서 얼마나 떨어져있는지?
	// - 출구에서 얼마나 떨어져있는지?
	// 두개를 계산해서 점수를 주는 방식
	// 공식은 정하기 나름. 출구를 우선으로 해도 되고 자기 맘대로 만들면 됨

	// F = G + H
	// F = 최종 점수 (작을 수록 좋음)
	// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용
	// H = 목적지에서 해당 좌표까지 이동하는데 드는 비용

	Pos start = _pos;
	Pos dest = _board->GetExitPos(); // 목적지

	Pos front[] =
	{
		Pos(-1, 0), // UP
		Pos(0, -1), // LEFT
		Pos(1, 0), // DOWN
		Pos(0, 1), // RIGHT
		Pos(-1, -1), // UP_LEFT
		Pos(1, -1), // DOWN_LEFT
		Pos(1, 1), // DOWN_RIGHT
		Pos(-1, 1), // UP_RIGHT
	};

	int32 cost[] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14
	};

	const int32 size = _board->GetSize();

	// best[y][x] -> 지금까지 (y,x)에 가장 좋은 비용(적을수록 좋음)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	//closedList -> closed[y][x] ? 1:0 -> (y,x)에 방문 했는지 여부 (발견이랑 다름)
	//추가옵션) 사실 best만으로 판별가능
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	//부모 추적용
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	//1) 예약 시스템
	//2) 뒤늦게 더 좋은 경로가 발견 -> 예외처리!

	//openList -> 지금까지 발견된 목록
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;


	//초기값 셋팅
	{
		int32 g = 0;
		// y의 차이와 x의 차이를 더해주고 10 곱한게 h라고 정해보자
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));

		pq.push(PQNode(g + h, g, start));
		best[start.y][start.x] = g + h;
		parent[start.y][start.x] = start;
	}

	while (pq.empty() == false)
	{
		// 제일 좋은 후보를 찾는다.
		PQNode node = pq.top();
		pq.pop();

		//동일한 좌표를 여러 경로로 찾아서
		//더 빠른 경로로 인해서 이미 방문(closed)된 경우 스킵
		if (closed[node.pos.y][node.pos.x]) { continue; }

		//이미 등록했지만 더 우수한 후보가 있다면 스킵(폐기)
		if (best[node.pos.y][node.pos.x] < node.f) { continue; }

		//방문
		closed[node.pos.y][node.pos.x] = true;

		//목적지에 도착했으면 바로 종료
		if (node.pos == dest) { break; }

		for (int32 dir = 0; dir < 8; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			//갈수있는 지역인지 확인
			if (CanGo(nextPos) == false) { continue; }
			if (closed[nextPos.y][nextPos.x]) { continue; }

			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			//다른 경로에서 더빠른 길을 찾았다면 스킵
			if (best[nextPos.y][nextPos.x] <= g + h) { continue; }

			//예약 진행
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode(g + h, g, nextPos));
			parent[nextPos.y][nextPos.x] = node.pos;
		}
	}

	_path.clear();
	Pos pos = dest;

	while (true)
	{
		_path.push_back(pos);

		// 시작점
		if (pos == parent[pos.y][pos.x])
			break;

		pos = parent[pos.y][pos.x];
	}

	/*vector<Pos> temp(_path.size());
	for (int i = 0; i < _path.size(); i++)
		temp[i] = _path[_path.size() - 1 - i];

	_path = temp;*/

	std::reverse(_path.begin(), _path.end());
}
