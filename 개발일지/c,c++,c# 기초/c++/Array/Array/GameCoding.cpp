#include <iostream>
#include "Helper.h"
#include "Map.h"
using namespace std;

int Gplayer_X = 2;
int Gplayer_Y = 2;

void MovePlayer(int x, int y)
{
	//���� üũ
	if (x < 0 || x >= Map_Size) { return; }
	if (y < 0 || y >= Map_Size) { return; }
	
	//��üũ ex) 2*5 + 
	int index = y * Map_Size + x;
	if (Gmap1D[index] == 1) { return; }
}

int main()
{
	SetCursorOnOff(false);

	while (true)
	{
		//�Է�

		//����

		//���
		PrintMap1D();
	}
}