//인접 리스트
// - 정점마다 연결리스트로 표현한것 (정점이 바라보는 것만 연결하면됨)
#include <bits/stdc++.h>
using namespace std;

const int V = 10;
vector<int> adj[V]; //백터 a를 v만큼 만들겠다는 뜻
int visitied[V];

void go(int idx)
{
	cout << idx << '\n';
	visitied[idx] = 1; //방문했음
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
		//사이즈가 0이면서(연결된 정점이 있고) 방문안했으면 
		if (adj[i].size() && visitied[i] == 0)
			go(i);
	}

	return 0;
}