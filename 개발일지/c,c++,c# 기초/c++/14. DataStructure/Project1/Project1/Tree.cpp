#include <iostream>
using namespace std;
#include <vector>

class Node
{
public:
	Node(const char* data) :data(data) { }

public:
	const char* data;
	vector<Node*> children;
};

Node* CreateTree()
{
	Node* root = new Node("R1 개발실");
	{
		Node* node = new Node("기획팀");
		root->children.push_back(node);
		{
			Node* leaf = new Node("전투팀");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("경제팀");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("스토리팀");
			node->children.push_back(leaf);
		}
	}
	{
		Node* node = new Node("프로그래밍팀");
		root->children.push_back(node);
		{
			Node* leaf = new Node("클라팀");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("서버팀");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("엔진팀");
			node->children.push_back(leaf);
		}
	}
	{
		Node* node = new Node("아트팀");
		root->children.push_back(node);
		{
			Node* leaf = new Node("배경팀");
			node->children.push_back(leaf);
		}
		{
			Node* leaf = new Node("케릭터팀");
			node->children.push_back(leaf);
		}
	}

	return root;
}

//이때 재귀함수가 필요
// 깊이(depth) 루트에서 어떤 노드에 도달하기위해 거쳐가는 간선의 개수
void PrintTree(Node* root, int depth = 0)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "-";
	}

	cout << root->data << endl;

	int size = root->children.size();
	//포문 사이즈가 나중에 0이 되니까 간접적으로 조건이 걸린거임
	for (int i = 0; i < size; i++)
	{
		Node* node = root->children[i];
		PrintTree(node, depth + 1);
	}
}

//높히
int GetHeight(Node* root)
{
	int ret = 1; //제일 큰 높히값 담을 변수 (일단 1이 제일크니까)

	int size = root->children.size();
	for (int i = 0; i < size; i++)
	{
		Node* node = root->children[i];
		int h = GetHeight(node) + 1;

		if (ret < h) { ret = h; }
	}

	return ret;
}
//
//int main()
//{
//	Node* root = CreateTree();
//	PrintTree(root);
//
//	int h = GetHeight(root);
//}