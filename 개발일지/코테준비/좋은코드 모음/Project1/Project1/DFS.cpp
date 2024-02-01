//#include <bits/stdc++.h>
//using namespace std;
//const int n = 5;
//vector<int> a[n];
//int visitied[n];
//
//void Dfs1(int u) //���ٸ��� �ε�� ���� ���
//{
//	visitied[u] = 1;
//	cout << u << endl;
//	for (int v : a[u])
//	{
//		if (visitied[v] == 0)
//			Dfs1(v);
//	}
//	cout << u << "�κ��� ���۵� �Լ��� �����" << endl;
//	return;
//}
//void Dfs2(int u)// ���Ծ �׳� �� �ϴ� ���
//{
//	if (visitied[u]) { return; }
//	visitied[u] = 1;
//	cout << u << endl;
//	for (int there : a[u])
//	{
//		Dfs2(there);
//	}
//	cout << u << "�κ��� ���۵� �Լ��� �����" << endl;
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
//		if (a[ny][nx] == 1 && !visitied[ny][nx]) //���ڵ尡 �߿��� = a[ny][nx]�� 1 �� ���� �Ǿ��ְ� �湮 �ȵȰ��̸�
//		{
//			Dfs(ny, nx); //Ž��
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
//				cout << i << " : " << j << "dfs�� ���۵Ǿ����ϴ�.\n";
//			}
//		}
//	}
//
//	cout << cnt;
//	return 0;
//}

//
// ��Ʈ�� Dfs
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


// ���4 ���� dfs + ����
#include <bits/stdc++.h>
using namespace std;

int n, l, r, sum = 0, cnt = 0;
int arr[54][54], visited[54][54];

int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };

vector<pair<int, int>> v;

void Dfs(int y, int x, vector<pair<int, int>>& v)
{
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= n || nx < 0 || nx >= n || visited[ny][nx]) continue;
		int ret = abs(arr[ny][nx] - arr[y][x]);
		if (ret >= l && ret <= r)
		{
			visited[ny][nx] = 1;
			v.push_back({ ny,nx });
			sum += arr[ny][nx];
			Dfs(ny, nx, v);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> l >> r;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}

	while (true)
	{
		bool flag = 0;
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!visited[i][j])
				{
					v.clear();
					visited[i][j] = 1;
					v.push_back({ i,j });
					sum = arr[i][j];
					Dfs(i, j, v);
					if (v.size() == 1) continue;
					for (pair<int, int> it : v)
					{
						arr[it.first][it.second] = sum / v.size();
						flag = 1;
					}
				}
			}
		}
		if (!flag) break;
		cnt++;
	}
	cout << cnt;

	return 0;
}