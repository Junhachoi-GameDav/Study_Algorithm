//���� ����Ʈ
// - �������� ���Ḯ��Ʈ�� ǥ���Ѱ� (������ �ٶ󺸴� �͸� �����ϸ��)
#include <bits/stdc++.h>
using namespace std;

const int V = 10;
vector<int> adj[V]; //���� a�� v��ŭ ����ڴٴ� ��
int visitied[V];

void go(int idx)
{
	cout << idx << '\n';
	visitied[idx] = 1; //�湮����
	for (int there : adj[idx])
	{
		if (visitied[there]) continue;
		go(there);
	}
}

int main() {
	adj[1].push_back(2);
	adj[2].push_back(1);

	adj[1].push_back(3);
	adj[3].push_back(1);

	adj[3].push_back(4);
	adj[4].push_back(3);

	for (int i = 0; i < V; i++)
	{
		//����� 0�̸鼭(����� ������ �ְ�) �湮�������� 
		if (adj[i].size() && visitied[i] == 0)
			go(i);
	}

	return 0;
}