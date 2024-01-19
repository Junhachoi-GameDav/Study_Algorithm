//#include <bits/stdc++.h>
//using namespace std;
//
//// {0, 0} 좌표에서 4방향으로 탐색하는 좌표
//const int dy[] = { -1, 0, 1, 0 };
//const int dx[] = { 0, 1, 0 ,-1 };
//
//int main() {
//	int y = 0, x = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		int ny = y + dy[i];
//		int nx = x + dx[i];
//		cout << ny << " " << nx << '\n';
//	}
//
//	return 0;
//}
/*
#include <bits/stdc++.h>
using namespace std;

// {0, 0} 좌표에서 8방향(대각선 포함)으로 탐색하는 좌표
const int dy[] = { -1, 0, 1, 0, 1, 1, 0, -1 };
const int dx[] = { 0, 1, 0 ,-1, 0, -1, -1, -1 };

int main() {
	int y = 0, x = 0;
	for (int i = 0; i < 8; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];
		cout << ny << " " << nx << '\n';
	}

	return 0;
}
*/
/*
#include <bits/stdc++.h>
using namespace std;

const int n = 3;
int arr[n][n], visitied[n][n];
const int dy[] = { -1, 0 ,1, 0 };
const int dx[] = { 0, 1 ,0, -1 };

void go(int y, int x)
{
	visitied[y][x] = 1;
	cout << y << " : " << x << '\n';
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue; //맵밖에 벗어날때 또한 a[-1]이 되면 오류(언더플로우)남
		if (arr[ny][nx] == 0) continue;
		if (visitied[ny][nx]) continue;
		go(ny, nx);
	}
	return;
}

int main() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}
	go(0, 0);

	return 0;
}
*/