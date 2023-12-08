#pragma once

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

	}
	~List()
	{

	}

	//		[node]<->[next_node][2][3]
	//[head]						[tail]
	Node* AddAtatHead(int data)
	{
		Node* node = new Node(data);

		if (_head == nullptr)
		{
			_head = node;
			_tail = node;
		}
		else
		{
			//순차적으로 하면된다. 그림을 먼저 그려놓고
			Node* next_node = _head;
			node->next = next_node;
			next_node->prev = node;
			_head = node;
		}
	}

private:
	Node* _head = nullptr;
	Node* _tail = nullptr;
};

