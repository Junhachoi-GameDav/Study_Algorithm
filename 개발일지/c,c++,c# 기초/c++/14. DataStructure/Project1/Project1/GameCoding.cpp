#include <iostream>
using namespace std;

class Node
{
public:
	Node(int data) : data(data) {}

public:
	int data;
	void* next = nullptr;
};
//
//int main() {
//
//}