#pragma once
#include <assert.h>

template<typename T>
class Iterator
{
public:
	Iterator() : _ptr(nullptr) {}
	Iterator(T* ptr) : _ptr(ptr){}

	//������ ++it ++(++it) ��� �ڱ��ڽ��� ������ �ֱ� ������
	// & �������� �ִ´�.
	Iterator& operator++()
	{
		_ptr++; // �ø��� 
		return *this; //�ڱ��ڽ�
	}

	//������ it++
	Iterator operator++(int)
	{
		Iterator temp = *this; //�ڱ��ڽ��� �ӽ÷� �ְ�
		_ptr++; //�ø���
		return temp;
	}

	Iterator operator+(const int count)
	{
		Iterator temp = *this; //�ڱ��ڽ��� �ӽ÷� �ְ�
		temp._ptr+= count; //count ��ŭ ������
		return temp;
	}

	bool operator==(const Iterator& other)
	{
		return _ptr == other._ptr;
	}
	bool operator!=(const Iterator& other)
	{
		return _ptr != other._ptr;
	}

	T& operator*() //�����ؾ��ϴϱ� &
	{
		return *_ptr;
	}
public:
	T* _ptr = nullptr;
};

template<typename T>
class Vector
{
public:

	using iterator = Iterator<T>;

	iterator begin() { return iterator(&_buffer[0]); }
	iterator end() { return begin() + _size; }

	//explicit �Ű������� �Լ�� �ٸ� ���ڰ� ��) ���� �Ǵ� �Ǽ� ���� ���°��� ����
	//explicit Vector(int capacity = 100) : _capacity(capacity)
	//{
	//	//_buffer = new T[capacity];
	//}
	explicit Vector()
	{

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

	void resize(int size)
	{
		reserve(size);
		_size = size;
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
	T* _buffer = nullptr;
	int		_size = 0;
	int		_capacity = 0;
};

