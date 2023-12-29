#include <iostream>
using namespace std;
#include <vector>
#include <queue>

//그래프 이미지는 강의에 있음


//비효율적이지만 이런식으로 작동한다는 예시용 함수(이렇게 안만든다.)
void CreateGraph_1()
{
	struct Vertex
	{
		vector<Vertex*> edges;
	};

	vector<Vertex> v(6); // 여섯개의 배열

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// 0번이 3번에 연결되어있나?
	bool connected = false;

	int size = v[0].edges.size();
	for (int i = 0; i < size; i++)
	{
		Vertex* vertex = v[0].edges[i];
		if (vertex == &v[3])
		{
			connected = true;
		}
	}
}


// 지하철 노선도 = 서로 드문드문 연결 = 인접리스트가 적당함
// 인스타 친구 = 서로 매우 뺵빽하게 연결 = 인접리스트가 비효율적({}안에가 너무 많음)

//인접 리스트 : 실제 연결된 애들'만' 넣어준다.
void CreateGraph_2()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6);

	//이중배열 처럼 백터안에 백터를 넣어서 관리
	vector<vector<int>> adjacent;
	adjacent.resize(6);

	//adjacent[0].puch_back(1);
	//adjacent[0].puch_back(3);
	adjacent[0] = { 1 , 3 };
	adjacent[1] = { 1 , 2 , 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// 0번->3번으로 연결되어있나?
	bool connected = false;

	int size = adjacent[0].size();
	for (int i = 0; i < size; i++)
	{
		int vertex = adjacent[0][i];
		if (vertex == 3)
		{
			connected = true;
		}
	}
}

//인접 행렬
void CreateGraph_3()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6);

	//연결된 목록을 행렬로 관리 = 표로 관리한다는 뜻
	//예)
	//[x][o][x][o][x][x]
	//[o][x][o][o][x][x]
	//[x][x][x][x][x][x]
	//[x][x][x][x][o][x]
	//[x][x][x][x][x][x]
	//[x][x][x][x][0][x]

	//adjacent[from][to] ?
	// 행렬을 이용한 그래프 표현
	// 메모리 소모 심하지만, 빠른 접근
	vector<vector<bool>> adjacent(6, vector<bool>(6, false)); //2차원배열에 배열안에 있는것들 false로 초기화
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	// 0번->3번 연결 되어있나?
	bool connected = adjacent[0][3];


	//응용 = 인트등으로도 만들수 있고 가중치도 줄수있다.
	vector<vector<int>> adjacent2 =
	{
		//이중으로 만들뒤 false는 -1로 표현
		{-1, 15, -1, 35, -1, -1},
		{15, -1, +5, 10, -1, -1},
		{-1, +5, -1, -1, -1, -1},
		{35, 10, -1, -1, +5, -1},
		{-1, -1, -1, +5, -1, +5},
		{-1, -1, -1, -1, +5, -1}
	};
}


// DFS (depth first search) = 어떻게든 깊이 파고들어서 찾는방법
// 트리랑 비슷하다.(단 트리는 아래로즉 한방향으로만 가능했지만 이건 양방향이다.)

// BFS (breath first search) = 너비 우선 탐색 
// 먼저 줄선놈이 먼저 들어간다. 선입선출

// DFS = 재귀함수 = 스택
// BFS = 큐


struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

//내가 방문한 목록 = DFS 용
vector<bool> visited;

//내가 발견한 목록 = BFS 용
vector<bool> discovered;

#pragma region DFS

void CreateGraph_DFS()
{
	vertices.resize(6);

	//인접 리스트
	/*adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1 , 3 };
	adjacent[1] = { 1 , 2 , 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };*/

	//인접 행렬
	adjacent = vector<vector<int>>
	{
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0},
	};
}

void Dfs(int here)
{
	//방문했는지
	visited[here] = true;
	cout << "Visited : " << here << endl;

	//인접한 길을 다 체크 , 인접리스트
	// 시간복잡도 O(V+E) e가 많아지면 v^2랑 똑같아서 뭐가더 나은지 판별할수없음
	// 서로 드문드문 연결 = 인접리스트가 적당함
	// 
	// V = Vertex
	// E = Edge
	// 
	//int size = adjacent[here].size();
	//for (int i = 0; i < size; i++)
	//{
	//	int there = adjacent[here][i];
	//	if (visited[there] == false)
	//	{
	//		Dfs(there); //재귀함수로 다시 실행
	//	}
	//}

	// 인접 행렬 버전 
	// 시간 복잡도 O(V^2)
	// 서로 매우 뺵빽하게 연결 = 인접리스트가 비효율적({}안에가 너무 많음)
	for (int there = 0; there < 6; there++)
	{
		//길이 있는지?
		if (adjacent[here][there] == 0) { continue; }

		//아직 방문하지 않은곳에 한해서 방문
		if (visited[there] == false) { Dfs(there); }
	}
}

void DfsAll()
{
	visited = vector<bool>(6, false);

	for (int i = 0; i < 6; i++)
	{
		if (visited[i] == false)
		{
			Dfs(i);
		}
	}
}

#pragma endregion

#pragma region BFS
void CreateGraph_BFS()
{
	vertices.resize(6);

	//인접 리스트
	/*adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1 , 3 };
	adjacent[1] = { 1 , 2 , 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };*/

	//인접 행렬
	adjacent = vector<vector<int>>
	{
		{0,1,0,1,0,0},
		{1,0,1,1,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0},
		{0,0,0,0,0,0},
		{0,0,0,0,1,0},
	};
}

void Bfs(int here)
{
	//이런식으로 조건을 만들면 최단거리도 알수있다.

	// 누구에 의해서 발견되었는가?
	vector<int> parant(6, -1);
	// 시작점에서 얼마나 떨어져 있는가?
	vector<int> dist(6, -1);

	queue<int> q;
	q.push(here);
	discovered[here] = true;

	//초기화
	parant[here] = here; //자기자신에 의해서 찾은거다.
	dist[here] = 0; //0에서 시작

	while (q.empty() == false)
	{
		here = q.front(); //넣고 방문했으니까
		q.pop(); // 꺼냄

		cout << "Visited : " << here << endl;

		//어차피 둘다 똑같다.

		//인접 리스트용
		//int size = adjacent[here].size();
		//for (int i = 0; i < size; i++)
		//{
		//	int there = adjacent[here][i];
		//	if (discovered[there]) { continue; }
		//	
		//	q.push(there); //방문이 아닌 예약(큐라는 상자에 넣어놓고 기다리고 위에 front pop으로 넣고빼기
		//	discovered[there] = true;
		//}

		//인접 행렬 용
		for (int there = 0; there < 6; there++)
		{
			if (adjacent[here][there] == 0) { continue; }

			if (discovered[there]) { continue; }

			q.push(there);
			discovered[there] = true;

			parant[there] = here;
			dist[there] = dist[here] + 1;
		}
	}
}

void BfsAll()
{
	discovered = vector<bool>(6, false);
	for (int i = 0; i < 6; i++)
	{
		if (discovered[i] == false) { Bfs(i); }
	}
}

#pragma endregion

// 다익스트라 = BFS 업그레이드 버전(BFS에 우선순위 큐를 한것)
// 경로에 가중치를 줘서 먼저 어디를 갈지 고르는것
// 우선순위 큐
#pragma region 다익스트라
void CreateGraph_Dijikstra()
{
	vertices.resize(6);

	adjacent = vector<vector<int>>(6, vector<int>(6, -1));
	adjacent[0][1] = adjacent[1][0] = 15;
	adjacent[0][3] = adjacent[3][0] = 35;
	adjacent[1][2] = adjacent[2][1] = 5;
	adjacent[1][3] = adjacent[3][1] = 10;
	adjacent[3][4] = adjacent[4][3] = 5;
	adjacent[5][4] = adjacent[4][5] = 5;
}

struct VertexCost
{
	VertexCost(int cost, int vertex) : cost(cost), vertex(vertex) {}

	//비교 const를 붙힌것과 안한것은 전혀 다른 함수이다.
	//const는 안에서 함수를 수정하지 않겠다는 뜻
	bool operator<(const VertexCost& other) const
	{
		return cost < other.cost;
	}

	bool operator>(const VertexCost& other) const
	{
		return cost > other.cost;
	}


	int cost;
	int vertex;
};

void Dijikstra(int here)
{
	priority_queue<VertexCost, vector<VertexCost>, greater<VertexCost>> pq;
	vector<int> best(6, INT32_MAX); //인트로 할수있는 최대 값
	vector<int> parent(6, -1);

	//초기화
	pq.push(VertexCost(0, here));
	best[here] = 0;
	parent[here] = here;

	while (pq.empty() == false)
	{
		//제일 좋은 후보 찾기
		VertexCost v = pq.top();
		pq.pop();

		int cost = v.cost;
		here = v.vertex;

		//더 짧은 경로를 뒤늦게 찾았다면 스킵(굳이 갈필요없으니까)
		if (best[here] < cost) { continue; }

		//방문
		cout << "방문! " << here << endl;

		for (int there = 0; there < 6; there++)
		{
			//연결되지 않았다면 스킵
			if (adjacent[here][there] == -1) { continue; }

			//더 좋은 경로를 과거에 찾았으면 스킵(혹시 모르니까 또해줌)
			int nextCost = best[here] + adjacent[here][there];
			if (nextCost >= best[there]) { continue; }

			//지금까지 찾은 경로중 최선의 수치면 갱신
			//나중에 언제든지 갱신될수 있음
			best[there] = nextCost;
			parent[there] = here;
			pq.push(VertexCost(nextCost, there));
		}
	}
}

#pragma endregion


// A* (에이스타) 알고리즘 = 다익스트라 + 목적지를 알고있음
// BFS나 다익스트라는 목적지에 대한 개념이 없음
// Player.cpp에서 구현 ㄱㄱ

int main() {

	//CreateGraph_DFS();
	//CreateGraph_BFS();
	CreateGraph_Dijikstra();

	//Dfs(0);
	//DfsAll();
	//Bfs(0);
	//BfsAll();
	Dijikstra(0);
}