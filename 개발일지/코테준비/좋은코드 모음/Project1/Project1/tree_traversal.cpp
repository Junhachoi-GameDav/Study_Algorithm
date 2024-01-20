//������ȸ ��Ʈ ������ ���°� �ƴ϶� �ǹ� �ڽ� ������ ���� ���
//post ~ : ~���Ŀ�

#include <bits/stdc++.h>
using namespace std;

vector<int> adj[1004];
int visited[1004];

void postOrder(int here)
{
	if (visited[here] == 0)
	{
		// ���� ����
		if (adj[here].size() == 1) //�ڽ��� �ϳ��� �������� ��
			postOrder(adj[here][0]);
		if (adj[here].size() == 2)
		{
			postOrder(adj[here][0]);
			postOrder(adj[here][1]);
		}
		visited[here] = 1; //���� 1 ����
		cout << here << " ";
	}
}


//������ȸ (dfs) ������ ��� ��Ʈ ������ ���°�
// pre ~ : ~������

void preOrder(int here)
{
	if (visited[here] == 0)
	{
		visited[here] = 1; //�̰� ������
		cout << here << " ";
		if (adj[here].size() == 1)
			preOrder(adj[here][0]);
		if (adj[here].size() == 2) {
			preOrder(adj[here][0]);
			preOrder(adj[here][1]);
		}

	}
}


//������ȸ ��� �� �ڽ��� ���ʳ�带 �湮�� �ڽ��� �湮�ϰ� �������� �湮�ϴ°�
// in ~

void inOrder(int here)
{
	if (visited[here] == 0)
	{
		if (adj[here].size() == 1) //���ʹۿ� ���ٸ�
		{
			inOrder(adj[here][0]); 
			visited[here] = 1;
		}
		else if (adj[here].size() == 2)
		{
			inOrder(adj[here][0]);
			visited[here] = 1;
			inOrder(adj[here][1]);
		}
		else
		{
			visited[here] = 1;
		}
	}
}

//������ȸ (bfs)�� �̰�


int main() {
	return 0;
}