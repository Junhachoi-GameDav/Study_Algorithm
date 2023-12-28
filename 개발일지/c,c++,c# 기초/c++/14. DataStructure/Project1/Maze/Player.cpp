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
	// parant[y][x] = pos -> (y, x) pos�� ���� �߰ߵ�
	vector<vector<Pos>> parant(size, vector<Pos>(size, Pos(-1, -1)));

	queue<Pos> q;
	q.push(pos);
	discovered[pos.y][pos.x] = true;

	//�ʱ�ȭ
	parant[pos.y][pos.x] = pos; //�ڱ��ڽſ� ���ؼ� �߰�


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
			parant[nextPos.y][nextPos.x] = pos;
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
		if (pos == parant[pos.y][pos.x]) { break; }
		//����� (�ڿ�������)
		pos = parant[pos.y][pos.x];
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
