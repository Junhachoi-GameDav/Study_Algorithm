#include <iostream>
#include "Helper.h"
#include "Map.h"
#include "Player.h"
using namespace std;

int main()
{
	SetCursorOnOff(false);

	MovePlayer(3, 2);

	while (true)
	{
		//�Է�
		HandleKeyInput();

		//����
		HandleMove();

		//���
		//PrintMap1D();
		PrintMap2D();
	}
}