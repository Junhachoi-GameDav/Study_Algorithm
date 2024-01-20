//후위순회 루트 노드부터 세는게 아니라 맨밑 자식 노드부터 세는 방법
//post ~ : ~이후에

#include <bits/stdc++.h>
using namespace std;

vector<int> adj[1004];
int visited[1004];

void postOrder(int here)
{
	if (visited[here] == 0)
	{
		// 들어가는 과정
		if (adj[here].size() == 1) //자식이 하나면 왼쪽으로 들어감
			postOrder(adj[here][0]);
		if (adj[here].size() == 2)
		{
			postOrder(adj[here][0]);
			postOrder(adj[here][1]);
		}
		visited[here] = 1; //가서 1 찍음
		cout << here << " ";
	}
}


//전위순회 (dfs) 기존에 방법 루트 노드부터 세는거
// pre ~ : ~이전의

void preOrder(int here)
{
	if (visited[here] == 0)
	{
		visited[here] = 1; //이게 먼저임
		cout << here << " ";
		if (adj[here].size() == 1)
			preOrder(adj[here][0]);
		if (adj[here].size() == 2) {
			preOrder(adj[here][0]);
			preOrder(adj[here][1]);
		}

	}
}


//중위순회 가운데 즉 자신의 왼쪽노드를 방문후 자신을 방문하고 오른쪽을 방문하는것
// in ~

void inOrder(int here)
{
	if (visited[here] == 0)
	{
		if (adj[here].size() == 1) //왼쪽밖에 없다면
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

//레벨순회 (bfs)가 이것


int main() {
	return 0;
}