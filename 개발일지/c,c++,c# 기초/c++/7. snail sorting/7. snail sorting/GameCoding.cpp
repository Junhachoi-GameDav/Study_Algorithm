#include <iostream>
#include <iomanip> // ��� ������ �迭�ҋ� ���� = ���� ���İ����� ���� 
using namespace std;

const int Max = 100;
int Board[Max][Max];
int n;

void PrintBoard()
{
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			//����� 0���� ä��� 2��¥���� ������ ��
			cout << setfill('0') << setw(2) << Board[y][x] << " ";
		}
		cout << endl;
	}
}

enum DIR
{
	RIGHT = 0,
	DOWN = 1,
	LEFT = 2,
	UP = 3,
};

bool CanGo(int y, int x)
{
	//�� �ٱ� üũ
	if (y < 0 || y >= n) { return false; }
	if (x < 0 || x >= n) { return false; }
	
	// �̹� �������̶�� 0�� �ƴϰ���
	if (Board[y][x] != 0)
	{
		return false;
	}

	return true;
}

void SetBoard()
{
	int dir = RIGHT;
	int num = 1;


	//�� ��ġ
	int y = 0;
	int x = 0;

	//�Ǵٸ� ���
	//�迭�� �̿��� ���   �̰��� Ŭ�� �ڵ�?!?!?!?!
	int d_y[] = { 0, 1, 0 ,-1 };
	int d_x[] = { 1, 0, -1 ,0 };

	while (true)
	{
		Board[y][x] = num;

		if (num == n * n) { break; }

		int nextY = y + d_y[dir]; //  �̰��� Ŭ�� �ڵ� ? !? !? !? !
		int nextX = x + d_x[dir];

		/*switch (dir)
		{
		case RIGHT:
			nextY = y;
			nextX = x + 1;
			break;
		case DOWN:
			nextY = y + 1;
			nextX = x;
			break;
		case LEFT:
			nextY = y;
			nextX = x - 1;
			break;
		case UP:
			nextY = y - 1;
			nextX = x;
			break;
		}*/

		if (CanGo(nextY, nextX))
		{
			y = nextY;
			x = nextX;
			num++;
		}
		else
		{
			//�̰��� Ŭ�� �ڵ�?!?!?!?!
			dir = (dir + 1) % 4;

			/*switch (dir)
			{
			case RIGHT:
				dir = DOWN;
				break;
			case DOWN:
				dir = LEFT;
				break;
			case LEFT:
				dir = UP;
				break;
			case UP:
				dir = RIGHT;
				break;
			}*/
		}
	}
}


int main()
{
	cin >> n;

	SetBoard();

	PrintBoard();


}