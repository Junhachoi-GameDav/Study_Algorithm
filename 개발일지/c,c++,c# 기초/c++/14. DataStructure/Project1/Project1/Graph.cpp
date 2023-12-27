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


// DFS = ����Լ� = ����
// BFS =


//DFS
struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

//���� �湮�� ���
vector<bool> visited;

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
	for (int there = 0; there < 6; there++)
	{
		//���� �ִ���?
		if (adjacent[here][there] == 0) { continue; }

		//���� �湮���� �������� ���ؼ� �湮
		if (visited[there] == false) { Dfs(there); }
	}
}

int main() {

	CreateGraph_DFS();

	visited = vector<bool>(6, false);
	Dfs(0);
}