#include <iostream>
using namespace std;
#include <vector>
#include <queue>

//�׷��� �̹����� ���ǿ� ����


//��ȿ���������� �̷������� �۵��Ѵٴ� ���ÿ� �Լ�(�̷��� �ȸ����.)
void CreateGraph_1()
{
	struct Vertex
	{
		vector<Vertex*> edges;
	};

	vector<Vertex> v(6); // �������� �迭

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// 0���� 3���� ����Ǿ��ֳ�?
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


// ����ö �뼱�� = ���� �幮�幮 ���� = ��������Ʈ�� ������
// �ν�Ÿ ģ�� = ���� �ſ� �����ϰ� ���� = ��������Ʈ�� ��ȿ����({}�ȿ��� �ʹ� ����)

//���� ����Ʈ : ���� ����� �ֵ�'��' �־��ش�.
void CreateGraph_2()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6);

	//���߹迭 ó�� ���;ȿ� ���͸� �־ ����
	vector<vector<int>> adjacent;
	adjacent.resize(6);

	//adjacent[0].puch_back(1);
	//adjacent[0].puch_back(3);
	adjacent[0] = { 1 , 3 };
	adjacent[1] = { 1 , 2 , 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// 0��->3������ ����Ǿ��ֳ�?
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

//���� ���
void CreateGraph_3()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6);

	//����� ����� ��ķ� ���� = ǥ�� �����Ѵٴ� ��
	//��)
	//[x][o][x][o][x][x]
	//[o][x][o][o][x][x]
	//[x][x][x][x][x][x]
	//[x][x][x][x][o][x]
	//[x][x][x][x][x][x]
	//[x][x][x][x][0][x]

	//adjacent[from][to] ?
	// ����� �̿��� �׷��� ǥ��
	// �޸� �Ҹ� ��������, ���� ����
	vector<vector<bool>> adjacent(6, vector<bool>(6, false)); //2�����迭�� �迭�ȿ� �ִ°͵� false�� �ʱ�ȭ
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	// 0��->3�� ���� �Ǿ��ֳ�?
	bool connected = adjacent[0][3];


	//���� = ��Ʈ�����ε� ����� �ְ� ����ġ�� �ټ��ִ�.
	vector<vector<int>> adjacent2 =
	{
		//�������� ����� false�� -1�� ǥ��
		{-1, 15, -1, 35, -1, -1},
		{15, -1, +5, 10, -1, -1},
		{-1, +5, -1, -1, -1, -1},
		{35, 10, -1, -1, +5, -1},
		{-1, -1, -1, +5, -1, +5},
		{-1, -1, -1, -1, +5, -1}
	};
}


// DFS (depth first search) = ��Ե� ���� �İ�� ã�¹��
// Ʈ���� ����ϴ�.(�� Ʈ���� �Ʒ����� �ѹ������θ� ���������� �̰� ������̴�.)

// BFS (breath first search) = �ʺ� �켱 Ž�� 
// ���� �ټ����� ���� ����. ���Լ���

// DFS = ����Լ� = ����
// BFS = ť


struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

//���� �湮�� ��� = DFS ��
vector<bool> visited;

//���� �߰��� ��� = BFS ��
vector<bool> discovered;

#pragma region DFS

void CreateGraph_DFS()
{
	vertices.resize(6);

	//���� ����Ʈ
	/*adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1 , 3 };
	adjacent[1] = { 1 , 2 , 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };*/

	//���� ���
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
	//�湮�ߴ���
	visited[here] = true;
	cout << "Visited : " << here << endl;

	//������ ���� �� üũ , ��������Ʈ
	// �ð����⵵ O(V+E) e�� �������� v^2�� �Ȱ��Ƽ� ������ ������ �Ǻ��Ҽ�����
	// ���� �幮�幮 ���� = ��������Ʈ�� ������
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
	//		Dfs(there); //����Լ��� �ٽ� ����
	//	}
	//}

	// ���� ��� ���� 
	// �ð� ���⵵ O(V^2)
	// ���� �ſ� �����ϰ� ���� = ��������Ʈ�� ��ȿ����({}�ȿ��� �ʹ� ����)
	for (int there = 0; there < 6; there++)
	{
		//���� �ִ���?
		if (adjacent[here][there] == 0) { continue; }

		//���� �湮���� �������� ���ؼ� �湮
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

	//���� ����Ʈ
	/*adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1 , 3 };
	adjacent[1] = { 1 , 2 , 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };*/

	//���� ���
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
	//�̷������� ������ ����� �ִܰŸ��� �˼��ִ�.

	// ������ ���ؼ� �߰ߵǾ��°�?
	vector<int> parant(6, -1);
	// ���������� �󸶳� ������ �ִ°�?
	vector<int> dist(6, -1);

	queue<int> q;
	q.push(here);
	discovered[here] = true;

	//�ʱ�ȭ
	parant[here] = here; //�ڱ��ڽſ� ���ؼ� ã���Ŵ�.
	dist[here] = 0; //0���� ����

	while (q.empty() == false)
	{
		here = q.front(); //�ְ� �湮�����ϱ�
		q.pop(); // ����

		cout << "Visited : " << here << endl;

		//������ �Ѵ� �Ȱ���.

		//���� ����Ʈ��
		//int size = adjacent[here].size();
		//for (int i = 0; i < size; i++)
		//{
		//	int there = adjacent[here][i];
		//	if (discovered[there]) { continue; }
		//	
		//	q.push(there); //�湮�� �ƴ� ����(ť��� ���ڿ� �־���� ��ٸ��� ���� front pop���� �ְ���
		//	discovered[there] = true;
		//}

		//���� ��� ��
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

// ���ͽ�Ʈ�� = BFS ���׷��̵� ����(BFS�� �켱���� ť�� �Ѱ�)
// ��ο� ����ġ�� �༭ ���� ��� ���� ���°�
// �켱���� ť
#pragma region ���ͽ�Ʈ��
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

	//�� const�� �����Ͱ� ���Ѱ��� ���� �ٸ� �Լ��̴�.
	//const�� �ȿ��� �Լ��� �������� �ʰڴٴ� ��
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
	vector<int> best(6, INT32_MAX); //��Ʈ�� �Ҽ��ִ� �ִ� ��
	vector<int> parent(6, -1);

	//�ʱ�ȭ
	pq.push(VertexCost(0, here));
	best[here] = 0;
	parent[here] = here;

	while (pq.empty() == false)
	{
		//���� ���� �ĺ� ã��
		VertexCost v = pq.top();
		pq.pop();

		int cost = v.cost;
		here = v.vertex;

		//�� ª�� ��θ� �ڴʰ� ã�Ҵٸ� ��ŵ(���� ���ʿ�����ϱ�)
		if (best[here] < cost) { continue; }

		//�湮
		cout << "�湮! " << here << endl;

		for (int there = 0; there < 6; there++)
		{
			//������� �ʾҴٸ� ��ŵ
			if (adjacent[here][there] == -1) { continue; }

			//�� ���� ��θ� ���ſ� ã������ ��ŵ(Ȥ�� �𸣴ϱ� ������)
			int nextCost = best[here] + adjacent[here][there];
			if (nextCost >= best[there]) { continue; }

			//���ݱ��� ã�� ����� �ּ��� ��ġ�� ����
			//���߿� �������� ���ŵɼ� ����
			best[there] = nextCost;
			parent[there] = here;
			pq.push(VertexCost(nextCost, there));
		}
	}
}

#pragma endregion


// A* (���̽�Ÿ) �˰��� = ���ͽ�Ʈ�� + �������� �˰�����
// BFS�� ���ͽ�Ʈ��� �������� ���� ������ ����
// Player.cpp���� ���� ����

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