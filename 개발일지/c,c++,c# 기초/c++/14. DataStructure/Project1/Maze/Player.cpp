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
		
		//�̵�
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

	//������
	Pos dest = _board->GetExitPos();

	//_dir;	//���� ���� ����
	//pos;	//���� ��ǥ

	//����ġ ������ ������������� �̰Դ� ����� ���
	//2d ���ӿ��� ������ ���̾��� ����̶���.
	Pos front[4]
	{
		Pos(-1,0),	//up
		Pos(0,-1),	//left
		Pos(1,0),	//down
		Pos(0,1),	//right
	};



	//�������� ã��������
	//_dir = DIR_UP; //0

	//while (pos != dest)
	//{
	//	int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
	//	if (CanGo(pos + front[newDir]))
	//	{
	//		//ȸ��
	//		_dir = (_dir - 1) % DIR_COUNT;
	//		//��ĭ�̵�
	//		pos += front[_dir];
	//		//���
	//		_path.push_back(pos);
	//		
	//	}
	//	else if (CanGo(pos + front[_dir]))
	//	{
	//		//��ĭ�̵�
	//		pos += front[_dir];
	//		//���
	//		_path.push_back(pos);
	//	}
	//	else
	//	{
	//		_dir = (_dir + 1) % DIR_COUNT;
	//	}

	//	if (pos == dest) { break; }
	//}

	//���� �ٶ󺸴� ���� ���� �տ� �ִ� ��ǥ
	//Pos next = pos + front[_dir];
	// ���������� 90�� ȸ��
	//_dir = (_dir - 1) % DIR_COUNT;
	// �������� 90�� ȸ��
	//_dir = (_dir + 1) % DIR_COUNT;

	//int32 newDir = _dir;
	
}

void Player::CalculatePath_BFS()
{
	Pos pos = _pos;
	//������
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
	// parent[y][x] = pos -> (y, x) pos�� ���� �߰ߵ�
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;

	//�ʱ�ȭ
	parent[pos.y][pos.x] = pos; //�ڱ��ڽſ� ���ؼ� �߰�


	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		//������ ����
		if (pos == dest) { break; }

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = pos + front[dir];
			//���� �ִ� ������ �´��� Ȯ��
			if (CanGo(nextPos) == false) { continue; }

			//�̹� �ٸ� ��ο� ���� �߰��� ����
			if (discovered[nextPos.y][nextPos.x]) { continue; }

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos.y][nextPos.x] = pos;
		}
	}

	//�н�
	_path.clear();
	//_path.push_back(pos);
	pos = dest; //���������ͽ���

	while (true)
	{
		_path.push_back(pos);

		//������
		if (pos == parent[pos.y][pos.x]) { break; }
		//����� (�ڿ�������)
		pos = parent[pos.y][pos.x];
	}

	//�Ųٷ� ������
	/*vector<Pos> temp(_path.size());
	for (int i = 0; i < _path.size(); i++)
	{
		temp[i] = _path[_path.size() - 1 - i];
	}
	_path = temp;*/

	//�̷� ����� �ִ�.
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
	// ä��
	// - �Ա����� �󸶳� �������ִ���?
	// - �ⱸ���� �󸶳� �������ִ���?
	// �ΰ��� ����ؼ� ������ �ִ� ���
	// ������ ���ϱ� ����. �ⱸ�� �켱���� �ص� �ǰ� �ڱ� ����� ����� ��

	// F = G + H
	// F = ���� ���� (���� ���� ����)
	// G = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ���
	// H = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ���

	Pos start = _pos;
	Pos dest = _board->GetExitPos(); // ������

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

	// best[y][x] -> ���ݱ��� (y,x)�� ���� ���� ���(�������� ����)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	//closedList -> closed[y][x] ? 1:0 -> (y,x)�� �湮 �ߴ��� ���� (�߰��̶� �ٸ�)
	//�߰��ɼ�) ��� best������ �Ǻ�����
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	//�θ� ������
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	//1) ���� �ý���
	//2) �ڴʰ� �� ���� ��ΰ� �߰� -> ����ó��!

	//openList -> ���ݱ��� �߰ߵ� ���
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;


	//�ʱⰪ ����
	{
		int32 g = 0;
		// y�� ���̿� x�� ���̸� �����ְ� 10 ���Ѱ� h��� ���غ���
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));

		pq.push(PQNode(g + h, g, start));
		best[start.y][start.x] = g + h;
		parent[start.y][start.x] = start;
	}

	while (pq.empty() == false)
	{
		// ���� ���� �ĺ��� ã�´�.
		PQNode node = pq.top();
		pq.pop();

		//������ ��ǥ�� ���� ��η� ã�Ƽ�
		//�� ���� ��η� ���ؼ� �̹� �湮(closed)�� ��� ��ŵ
		if (closed[node.pos.y][node.pos.x]) { continue; }

		//�̹� ��������� �� ����� �ĺ��� �ִٸ� ��ŵ(���)
		if (best[node.pos.y][node.pos.x] < node.f) { continue; }

		//�湮
		closed[node.pos.y][node.pos.x] = true;

		//�������� ���������� �ٷ� ����
		if (node.pos == dest) { break; }

		for (int32 dir = 0; dir < 8; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			//�����ִ� �������� Ȯ��
			if (CanGo(nextPos) == false) { continue; }
			if (closed[nextPos.y][nextPos.x]) { continue; }

			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			//�ٸ� ��ο��� ������ ���� ã�Ҵٸ� ��ŵ
			if (best[nextPos.y][nextPos.x] <= g + h) { continue; }

			//���� ����
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

		// ������
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
