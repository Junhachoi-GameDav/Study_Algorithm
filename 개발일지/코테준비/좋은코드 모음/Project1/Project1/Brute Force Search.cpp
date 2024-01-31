// 완전탐색, 브루트포스, 모든경우의수 등등

//백트레킹 = 완전탐색에 가지치기를한것 모든경우의수를 구할필요없이 이미구한건 넘아가거나 하면됨

// 원복 =원상복구. 모든 경우의수를 구할려면 전에 수가 영향을 주워서는 안된다. 즉 초기화를 하란말.


//문제 긍정왕 홍철이의 구걸여행
//재귀함수를 통한 원복(dfs + 원복)
#include <bits/stdc++.h>
using namespace std;

const int n = 3;
int a[3][3] = {
	{10, 20, 21},
	{70, 90, 12},
	{80, 110, 120}
};
int visited[3][3];
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
vector<int> v;

void print()
{
	for (int i : v) cout << i << " ";
	cout << '\n';
}

void go(int y, int x)
{
	if (y == n - 1 && x == n - 2) { //2x2 까지 왔다면
		print();
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= n || nx < 0 || nx >= n || visited[ny][nx]) continue;
		visited[ny][nx] = 1;
		v.push_back(a[ny][nx]);

		go(ny, nx);

		visited[ny][nx] = 0;
		v.pop_back(); //a[ny][nx]
	}

}

int main() {
	visited[0][0] = 1;
	v.push_back(a[0][0]);
	go(0, 0);

	return 0;
}