#include "BinarySearchTree.h"
#include <iostream>
#include <windows.h>
using namespace std;

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr) { return; }

	SetCursorPosition(x, y);

	cout << node->key;

	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);
}

//재귀함수
Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == nullptr || key == node->key) { return node; }

	if (key < node->key)
		return Search(node->left, key);
	else
		return Search(node->right, key);
}

Node* BinarySearchTree::Min(Node* node)
{
	if (node == nullptr) { return nullptr; }

	//제일 작은수는 그냥 왼쪽으로 계속 가면된다.
	while (node->left)//왼쪽이 없을떄까지
	{
		node = node->left;
	}
	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	if (node == nullptr) { return nullptr; }

	//제일 큰수는 그냥 오른쪽으로 계속 가면된다.
	while (node->right)//오른쪽이 없을때까지
	{
		node = node->right;
	}
	return node;
}

//그 다음으로 큰수를 찾는다면
Node* BinarySearchTree::Next(Node* node)
{
	if (node->right) { return Min(node->right); } //오른쪽에 있는것중에 제일작은것을 리턴
	Node* parent = node->parent; //부모자리 하나 만들고

	while (parent && node == parent->right)// 외쪽(작은수) 자식노드를 갖고있는 부모가 없을때까지
	{
		//올라감
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

void BinarySearchTree::insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	if (_root == nullptr)//루트가 변한게 없다.
	{
		_root = newNode;
		return;
	}

	//추가할 위치를 찾는다.
	Node* node = _root;
	Node* parent = nullptr;

	while (node) //노드를 찾을 때까지 (왼쪽 또는 오른쪽)
	{
		parent = node;
		if (key < node->key)
		{
			node = node->left;
		}
		else {
			node = node->right;
		}
	}

	newNode->parent = parent;

	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);// 삭제할 키들을 찾은후
	Delete(deleteNode); //아래 함수 실행
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr) { return; }

	if (node->left == nullptr)
	{
		Replace(node, node->right); //오른쪽에있는것을 연결
	}
	else if (node->right == nullptr)
	{
		Replace(node, node->left); //왼쪽에있는것을 연결
	}
	else//양쪽다 없다면
	{
		Node* next = Next(node);//15
		node->key = next->key;
		Delete(next); //재귀
	}
}

void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == nullptr)
	{ 
		_root = v;
	}
	else if (u == u->parent->left) //u가 u부모의 왼쪽 자식이였다면
	{
		u->parent->left = v;
	}
	else //오른쪽 자식이었다면
	{
		u->parent->right = v;
	}

	if (v)
		v->parent = u->parent;

	delete u;
}
