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

void Player::CalculatePath()
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
			//ȸ��
			_dir = (_dir - 1) % DIR_COUNT;
			//��ĭ�̵�
			pos += front[_dir];
			//���
			_path.push_back(pos);
			
		}
		else if (CanGo(pos + front[_dir]))
		{
			//��ĭ�̵�
			pos += front[_dir];
			//���
			_path.push_back(pos);
		}
		else
		{
			_dir = (_dir + 1) % DIR_COUNT;
		}

		if (pos == dest) { break; }
	}

	//���� �ٶ󺸴� ���� ���� �տ� �ִ� ��ǥ
	//Pos next = pos + front[_dir];
	// ���������� 90�� ȸ��
	//_dir = (_dir - 1) % DIR_COUNT;
	// �������� 90�� ȸ��
	//_dir = (_dir + 1) % DIR_COUNT;

	//int32 newDir = _dir;

	//�������� ã��������
	//while (pos != dest)
	//{
	//	//1. ���� �ٶ󺸴� �����������  ���������� �����ִ��� Ȯ��
	//	int32 newDir = (_dir - 1) % DIR_COUNT;
	//	if (CanGo(pos + front[newDir]))
	//	{
	//		//���������� 90�� ȸ��
	//		_dir = (_dir - 1) % DIR_COUNT;
	//		//������ �� �� ����
	//		pos += front[_dir];
	//		//��ǥ ���
	//		_path.push_back(pos);
	//		
	//	}
	//	//2. ���� �Ҽ� �ִ��� Ȯ��
	//	else if (CanGo(pos + front[3]))
	//	{
	//		//������ �� �� ����
	//		pos += front[_dir];
	//		//��ǥ ���
	//		_path.push_back(pos);
	//	}
	//	// 3.�Ѵ� �ƴҶ� ����
	//	else
	//	{
	//		//�������� 90�� ȸ��
	//		_dir = (_dir + 1) % DIR_COUNT;
	//	}
	//}
}
