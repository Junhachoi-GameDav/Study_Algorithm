#include <iostream>
using namespace std;

class node
{
public:
	node(int data) : data(data) {}

public:
	int data;
	void* next = nullptr;
};
