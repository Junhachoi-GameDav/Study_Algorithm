#include <iostream>
using namespace std;
#include <vector>
#include <queue>

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
	adjacent[0] = { 1, 3 };
}

int main() {

}