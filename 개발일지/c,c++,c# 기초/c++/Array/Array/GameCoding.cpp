#include <iostream>
#include "Helper.h"
#include "Map.h"
using namespace std;

int Gplayer_X = 2;
int Gplayer_Y = 2;

void MovePlayer(int x, int y)
{
	//범위 체크
	if (x < 0 || x >= Map_Size) { return; }
	if (y < 0 || y >= Map_Size) { return; }
	
	//벽체크 ex) 2*5 + 
	int index = y * Map_Size + x;
	if (Gmap1D[index] == 1) { return; }
}

int main()
{
	SetCursorOnOff(false);

	while (true)
	{
		//입력

		//로직

		//출력
		PrintMap1D();
	}
}