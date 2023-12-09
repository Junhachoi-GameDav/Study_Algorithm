#pragma once
#include <iostream>
using namespace std;

class Node
{
	//typedef int T; //옛날 버전
	using T = int; //요즘 버전
public:
	Node(int data) : data(data), prev(nullptr), next(nullptr){} //생성자


public:
	T data;
	Node* prev;
	Node* next;
};

class List
{
public:
	List()
	{
		_head = new Node(0); //더미
		_tail = new Node(0); //더미
		_head->next = _tail;
		_tail->prev = _head;
	}
	~List()
	{
		Node* node = _head;
		while (node)
		{
			Node* deleteNode = node;
			node = node->next; //한깐씩 이동하는 효과
			delete deleteNode;
		}
	}

	//하나하나 다찾아야 하기때문에 엄청 느리고 비효율
	Node* GetNode(int index) //몇번째 인지 찾기
	{
		Node* node = _head->next;
		if (node == _tail) { return nullptr; }

		for (int i = 0; i < index; i++)
		{
			if (node == _tail->prev) { return nullptr; }

			node = node->next;
		}
	}

	void Print()
	{
		Node* node = _head->next;
		while (node != _tail)
		{
			cout << node->data << " ";
			node = node->next;
		}
		cout << endl;
	}

	//		[node]<->[next_node][2][3]
	//[head]						[tail]
	//이방식은 좀 비효율적이니 더미를 이용한 방법을 쓴다.
	//		[dummy]<->[dummy]
	//[head]				[tail]
	Node* AddAtatHead(int data)
	{
		//		[dummy]<->[node]<->[next_node]<->[][]...[dummy]
		//		[head]									[tail]
		Node* node = new Node(data);
		Node* next_node = _head->next;

		node->next = next_node;
		next_node->prev = node;
		_head->next = node;
		node->prev = _head;

		return node;
	}

	Node* AddAtTail(int data)
	{
		//		[dummy][][][]...[prev_node]<->[node]<->[dummy]
		//		[head]									[tail]
		Node* node = new Node(data);
		Node* prev_node = _tail->prev;

		prev_node->next = node;
		node->prev = prev_node;
		node->next = _tail;
		_tail->prev = node;

		return node;
	}


	//사실상 이거 배우려고 한거임. 삽입 삭제

	void Insert(Node* pos_node, int data)
	{
		Node* node = new Node(data);
		Node* prev_node = pos_node->prev;

		prev_node->next = node;
		node->prev = prev_node;
		node->next = pos_node;
		pos_node->prev = node;
	}
	//						[node]
	//	[dummy]<->[prev_node]<->[next_node]<->[dummy]
	//	[head]									[tail]
	Node* Remove(Node* node)
	{
		Node* prev_node = node->prev;
		Node* next_node = node->next;
		prev_node->next = next_node;
		next_node->prev = prev_node;

		delete node;

		return next_node;
	}

private:
	Node* _head = nullptr;
	Node* _tail = nullptr;
};

