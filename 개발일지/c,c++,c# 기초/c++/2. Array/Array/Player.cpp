#include "Player.h"
#include "Map.h"
#include "Helper.h"

int Gplayer_X = 2;
int Gplayer_Y = 2;

bool canMove = true;

void MovePlayer(int x, int y)
{
	//���� üũ
	if (x < 0 || x >= Map_Size) { return; }
	if (y < 0 || y >= Map_Size) { return; }

	//��üũ ex) 2*5 + 2 = 12��° �� ���
	int index = y * Map_Size + x;
	if (Gmap1D[index] == 1) { return; }
	if (Gmap2D[y][x] == 1) {
		return;
	}


	// ���� ��ġ ����
	{
		int prevIndex = Gplayer_Y * Map_Size + Gplayer_X;
		Gmap1D[prevIndex] = 0;
		Gmap2D[Gplayer_Y][Gplayer_X] = 0;
	}

	//�� ��ġ �̵�
	{
		Gplayer_X = x;
		Gplayer_Y = y;
		int prevIndex = Gplayer_Y * Map_Size + Gplayer_X;
		Gmap1D[prevIndex] = 2;
		Gmap2D[Gplayer_Y][Gplayer_X] = 2;
	}

}

void HandleMove()
{
	//Ű��Ʈ�� ���� ������, �ٽ� �����ϼ� �ְ� 
	//�� �ѹ��� �����̰�
	if (Gmove_dir == md_none) {
		canMove = true;
		return;
	}

	//�����ϼ� �ִ���?
	if (canMove == false) { return; }

	canMove = false;

	switch (Gmove_dir)
	{
	case md_left:
		MovePlayer(Gplayer_X - 1, Gplayer_Y);
		break;
	case md_right:
		MovePlayer(Gplayer_X + 1, Gplayer_Y);
		break;
	case md_up:
		MovePlayer(Gplayer_X, Gplayer_Y - 1);
		break;
	case md_down:
		MovePlayer(Gplayer_X, Gplayer_Y + 1);
		break;
	}
}


