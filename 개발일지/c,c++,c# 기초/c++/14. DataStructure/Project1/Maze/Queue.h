#pragma once
#include "Vector.h"


//front 꺼내야할 데이터 위치
//서버 대기열 같은거로 엄청 많이쓴다.
template <typename T>
class Queue
{
public:
	Queue()
	{
		_container.resize(100);
	}

	void push(const T& value)
	{
		//다 찼는지 체크
		if (_size == _container.size())
		{
			//증설작업 같은거
		}

		_container[_back] = value;
		_back = (_back + 1) % _container.size(); //나머지연산으로 마지막에서 처음으로 리셋
		_size++;
	}

	void pop()
	{
		_front = (_front + 1) % _container.size();
		_size--;
	}

	T& front()
	{
		return _container[_front];
	}

	bool empty() { return _size == 0; }
	int size() { return _size; }

private:
	Vector<T> _container;

	int _front = 0;
	int _back = 0;
	int _size = 0;
};

