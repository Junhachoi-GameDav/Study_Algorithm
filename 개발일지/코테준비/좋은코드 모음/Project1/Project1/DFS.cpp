//#include <bits/stdc++.h>
//using namespace std;
//const int n = 5;
//vector<int> a[n];
//int visitied[n];
//
//void Dfs1(int u) //돌다리를 두들겨 보는 방법
//{
//	visitied[u] = 1;
//	cout << u << endl;
//	for (int v : a[u])
//	{
//		if (visitied[v] == 0)
//			Dfs1(v);
//	}
//	cout << u << "로부터 시작된 함수가 종료됨" << endl;
//	return;
//}
//void Dfs2(int u)// 못먹어도 그냥 ㄱ 하는 방법
//{
//	if (visitied[u]) { return; }
//	visitied[u] = 1;
//	cout << u << endl;
//	for (int there : a[u])
//	{
//		Dfs2(there);
//	}
//	cout << u << "로부터 시작된 함수가 종료됨" << endl;
//}
//
//
//int main() {
//	a[1].push_back(2);
//	a[1].push_back(3);
//	a[2].push_back(4);
//	a[4].push_back(2);
//	a[2].push_back(5);
//	//Dfs1(1);
//	Dfs2(1);
//}
//
//#include <bits/stdc++.h>
//using namespace std;
//
//int dy[] = { -1, 0, 1, 0 };
//int dx[] = { 0, 1, 0, -1 };
//int n, m, cnt = 0, ny, nx;
//
//int a[104][104];
//bool visitied[104][104];
//
//void Dfs(int y, int x)
//{
//	visitied[y][x] = 1;
//	cout << y << " : " << x << '\n';
//	for (int i = 0; i < 4; i++)
//	{
//		ny = y + dy[i];
//		nx = x + dx[i];
//		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
//		if (a[ny][nx] == 1 && !visitied[ny][nx]) //이코드가 중요함 = a[ny][nx]가 1 즉 길이 되어있고 방문 안된곳이면
//		{
//			Dfs(ny, nx); //탐색
//		}
//	}
//	return;
//}
//
//int main() {
//
//	cin >> n >> m;
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < m; j++)
//		{
//			cin >> a[i][j];
//		}
//	}
//
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < m; j++)
//		{
//			if (a[i][j] == 1 && !visitied[i][j])
//			{
//				Dfs(i, j);
//				cnt++;
//				cout << i << " : " << j << "dfs가 시작되었습니다.\n";
//			}
//		}
//	}
//
//	cout << cnt;
//	return 0;
//}

//
// 인트형 Dfs
// 
//int Dfs(int here)
//{
//	int ret = 1;
//	visited[here] = 1;
//
//	for (int there : v[here])
//	{
//		if (visited[there]) continue;
//		visited[there] = 1;
//		ret += Dfs(there);
//	}
//	return ret;
//}