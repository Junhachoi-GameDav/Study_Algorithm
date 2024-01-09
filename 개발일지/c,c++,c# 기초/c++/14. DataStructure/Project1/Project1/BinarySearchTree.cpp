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

//����Լ�
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

	//���� �������� �׳� �������� ��� ����ȴ�.
	while (node->left)//������ ����������
	{
		node = node->left;
	}
	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	if (node == nullptr) { return nullptr; }

	//���� ū���� �׳� ���������� ��� ����ȴ�.
	while (node->right)//�������� ����������
	{
		node = node->right;
	}
	return node;
}

//�� �������� ū���� ã�´ٸ�
Node* BinarySearchTree::Next(Node* node)
{
	if (node->right) { return Min(node->right); } //�����ʿ� �ִ°��߿� ������������ ����
	Node* parent = node->parent; //�θ��ڸ� �ϳ� �����

	while (parent && node == parent->right)// ����(������) �ڽĳ�带 �����ִ� �θ� ����������
	{
		//�ö�
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

void BinarySearchTree::insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	if (_root == nullptr)//��Ʈ�� ���Ѱ� ����.
	{
		_root = newNode;
		return;
	}

	//�߰��� ��ġ�� ã�´�.
	Node* node = _root;
	Node* parent = nullptr;

	while (node) //��带 ã�� ������ (���� �Ǵ� ������)
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
	Node* deleteNode = Search(_root, key);// ������ Ű���� ã����
	Delete(deleteNode); //�Ʒ� �Լ� ����
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr) { return; }

	if (node->left == nullptr)
	{
		Replace(node, node->right); //�����ʿ��ִ°��� ����
	}
	else if (node->right == nullptr)
	{
		Replace(node, node->left); //���ʿ��ִ°��� ����
	}
	else//���ʴ� ���ٸ�
	{
		Node* next = Next(node);//15
		node->key = next->key;
		Delete(next); //���
	}
}

void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == nullptr)
	{ 
		_root = v;
	}
	else if (u == u->parent->left) //u�� u�θ��� ���� �ڽ��̿��ٸ�
	{
		u->parent->left = v;
	}
	else //������ �ڽ��̾��ٸ�
	{
		u->parent->right = v;
	}

	if (v)
		v->parent = u->parent;

	delete u;
}
