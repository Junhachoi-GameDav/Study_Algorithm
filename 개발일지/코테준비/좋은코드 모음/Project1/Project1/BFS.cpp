//#include <bits/stdc++.h>
//using namespace std;
//
//vector<int> adj[100];
//int visitied[100];
//int node_list[] = { 10, 12, 14, 16, 18, 20, 22, 24 };
//
//void Bfs(int here)
//{
//	queue<int> q;
//	visitied[here] = 1;
//	q.push(here);
//	while (q.size()) //ť���ִٸ�
//	{
//		int here = q.front();
//		q.pop();
//		for (int there : adj[here]) //���� ������ �ڽĵ� ��������
//		{
//			if (visitied[there]) continue;
//			visitied[there] = visitied[here] + 1;
//			q.push(there);
//		}
//	}
//}
//
//
//int main() {
//	adj[10].push_back(12);
//	adj[10].push_back(14);
//	adj[10].push_back(16);
//
//	adj[12].push_back(18);
//	adj[12].push_back(20);
//
//	adj[20].push_back(22);
//	adj[20].push_back(24);
//	Bfs(10);
//	for (int i : node_list)
//	{
//		cout << i << " : " << visitied[i] << '\n';
//	}
//	cout << "10������ 24 ����� �ִܰŸ��� = " << visitied[24] - 1;
//}

#include <bits/stdc++.h>
using namespace std;

const int max_n = 104;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0 ,-1 };
int n, m, x, y, ny, nx, s_pos_y, s_pos_x, obj_y, obj_x;
int a[max_n][max_n], visitied[max_n][max_n];

int main() {

	cin >> n >> m;
	cin >> s_pos_y >> s_pos_x;
	cin >> obj_y >> obj_x;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> a[i][j];
		}
	}

	queue<pair<int, int>> q;
	visitied[s_pos_y][s_pos_x] = 1;
	q.push({ s_pos_y, s_pos_x }); // pair �� {}
	while (q.size())
	{
		tie(y, x) = q.front(); // tie = pair, tuple���� ���� �༮���� ������ ���� ������ �ѹ��� �޾� �� ������
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			ny = y + dy[i];
			nx = x + dx[i];
			if (ny < 0 || ny >= n || nx < 0 || nx >= m || a[ny][nx] == 0) continue;
			if (visitied[ny][nx]) continue;
			visitied[ny][nx] = visitied[y][x] + 1;
			q.push({ ny, nx });
		}
	}
	//cout << visitied[obj_y][obj_y];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << visitied[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}