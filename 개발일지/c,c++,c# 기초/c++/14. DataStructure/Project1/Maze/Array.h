#pragma once
#include <assert.h>

class Array
{
	using T = int;

public:

	//explicit 매개변수나 함수등에 다른 숫자가 예) 정수 또는 실수 등이 들어가는것을 방지
	explicit Array(int capacity = 100) : _capacity(capacity)
	{
		_buffer = new T[capacity];
	}

	~Array()
	{
		delete[] _buffer;
	}

	void push_back(const T& data)
	{
		//TODO
		if (_size == _capacity) { return; }

		_buffer[_size] = data;
		_size++;
	}

	//배열 []을 넣을 떄 그냥 넣는것이 아니라 이렇게 함수로 만들어서 
	// 조건등을 넣을수가있음
	T& operator[](int index)
	{
		// todo
		assert(index >= 0 && index < _size); //조건에 안맞으면 크래쉬를 내는 함수이다.
		return _buffer[index];
	}

	int size() { return _size; }
	int capacity() { return _capacity; }

private:
	T*		_buffer = nullptr;
	int		_size = 0;
	int		_capacity = 0;
};

