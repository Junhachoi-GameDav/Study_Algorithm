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