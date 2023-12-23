#pragma once
#include <assert.h>

class Vector
{
	using T = Pos;

public:

	//explicit �Ű������� �Լ�� �ٸ� ���ڰ� ��) ���� �Ǵ� �Ǽ� ���� ���°��� ����
	explicit Vector(int capacity = 100) : _capacity(capacity)
	{
		_buffer = new T[capacity];
	}

	~Vector()
	{
		delete[] _buffer;
	}

	void clear() //������ �� ���ִ� �Լ�
	{
		//todo
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = new T[_capacity];
		}

		_size = 0;
	}


	//�̰� �ٽ��̴�. �����迭 =�迭�� �ű���� �����ϱ� �̷������� ũ�⸦ �÷��� �ű�°�
	void push_back(const T& data)
	{
		//TODO
		if (_size == _capacity)
		{ 
			//���� �۾�
			int new_capacity = static_cast<int>(_capacity * 1.5);
			if (new_capacity == _capacity) { new_capacity++; }

			reserve(new_capacity);
		}

		_buffer[_size] = data;
		_size++;
	}

	void pop_back() //�ڿ��ִ����� ������ �Լ�
	{
		//todo
		_size--;
	}

	T& back()
	{
		return _buffer[_size - 1]; //������ ������ ������
	}

	void reserve(int capacity)
	{
		if (_capacity >= capacity) { return; }

		_capacity = capacity;

		T* new_data = new T[_capacity]; //��ū �迭�� �ٽ� �����

		//������ ���� �ٿ��ֱ�
		for (int i = 0; i < _size; i++)
		{
			new_data[i] = _buffer[i];
		}

		if (_buffer) { delete[] _buffer; } //���� ����� ���� ����
		//�ʱ�ȭ
		_buffer = new_data;
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

