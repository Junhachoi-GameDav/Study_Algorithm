#pragma once
#include "Vector.h"

// ui 뒤로가기나 했던것을 다시 순서대로 되돌리는것에서 많이씀
//뜬 팝업창 닫기 , 설정 뒤로가기 , ctrl + z 등등

template <typename T>
class Stack
{
public:

	void push(const T& value)
	{
		_container.push_back(value);
	}

	void pop()
	{
		_container.pop_back();
	}

	T& top()
	{
		return _container.back();
	}


	bool empty() { return size() > 0; }
	int size() { return _container.size(); }

private:
	Vector<T> _container;
};

