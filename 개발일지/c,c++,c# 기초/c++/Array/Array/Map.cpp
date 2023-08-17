#include "Map.h"
#include <iostream>
#include "Helper.h"
using namespace std;

//1���� �迭
int Gmap1D[Map_Size * Map_Size] =
{
	1,1,1,1,1,
	1,0,0,0,1,
	1,0,2,0,1,
	1,0,0,0,1,
	1,1,1,1,1,
};

//2���� �迭
int Gmap2D[Map_Size][Map_Size] =
{
	{ 1,1,1,1,1 },
	{ 1,0,0,0,1 },
	{ 1,0,2,0,1 },
	{ 1,0,0,0,1 },
	{ 1,1,1,1,1 },
};

void PrintMap1D()
{
	SetCursorPosition(0, 0);

	for (int i = 0; i < Map_Size * Map_Size; i++)
	{
		//Ư������ ���ۿ� �˻�
		switch (Gmap1D[i])
		{
		case 0:
			cout << "��";
			break;
		case 1:
			cout << "��";
			break;
		case 2:
			cout << "��";
			break;
		}

		if ((i + 1) % Map_Size == 0)
		{
			cout << endl;
		}
	}
}

void PrintMap2D()
{
	SetCursorPosition(0, 0);

	for (int y = 0; y < Map_Size; y++)
	{
		for (int x = 0; x < Map_Size; x++)
		{
			switch (Gmap2D[y][x])
			{
			case 0:
				cout << "��";
				break;
			case 1:
				cout << "��";
				break;
			case 2:
				cout << "��";
				break;
			}
		}
		cout << endl;
	}
}