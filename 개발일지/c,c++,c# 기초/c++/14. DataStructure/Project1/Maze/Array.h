#pragma once
#include <assert.h>

class Array
{
	using T = int;

public:

	//explicit �Ű������� �Լ�� �ٸ� ���ڰ� ��) ���� �Ǵ� �Ǽ� ���� ���°��� ����
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

	//�迭 []�� ���� �� �׳� �ִ°��� �ƴ϶� �̷��� �Լ��� ���� 
	// ���ǵ��� ������������
	T& operator[](int index)
	{
		// todo
		assert(index >= 0 && index < _size); //���ǿ� �ȸ����� ũ������ ���� �Լ��̴�.
		return _buffer[index];
	}

	int size() { return _size; }
	int capacity() { return _capacity; }

private:
	T*		_buffer = nullptr;
	int		_size = 0;
	int		_capacity = 0;
};

