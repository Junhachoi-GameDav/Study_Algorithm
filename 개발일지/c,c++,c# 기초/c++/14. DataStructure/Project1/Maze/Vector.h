#pragma once
#include <assert.h>

class Vector
{
	using T = Pos;

public:

	//explicit 매개변수나 함수등에 다른 숫자가 예) 정수 또는 실수 등이 들어가는것을 방지
	explicit Vector(int capacity = 100) : _capacity(capacity)
	{
		_buffer = new T[capacity];
	}

	~Vector()
	{
		delete[] _buffer;
	}

	void clear() //데이터 다 없애는 함수
	{
		//todo
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = new T[_capacity];
		}

		_size = 0;
	}


	//이게 핵심이다. 동적배열 =배열은 옮길수가 없으니까 이런식으로 크기를 늘려서 옮기는것
	void push_back(const T& data)
	{
		//TODO
		if (_size == _capacity)
		{ 
			//증설 작업
			int new_capacity = static_cast<int>(_capacity * 1.5);
			if (new_capacity == _capacity) { new_capacity++; }

			reserve(new_capacity);
		}

		_buffer[_size] = data;
		_size++;
	}

	void pop_back() //뒤에있던것을 꺼내는 함수
	{
		//todo
		_size--;
	}

	T& back()
	{
		return _buffer[_size - 1]; //마지막 데이터 꺼내기
	}

	void reserve(int capacity)
	{
		if (_capacity >= capacity) { return; }

		_capacity = capacity;

		T* new_data = new T[_capacity]; //더큰 배열로 다시 만들기

		//데이터 복사 붙여넣기
		for (int i = 0; i < _size; i++)
		{
			new_data[i] = _buffer[i];
		}

		if (_buffer) { delete[] _buffer; } //원래 사용한 공간 삭제
		//초기화
		_buffer = new_data;
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

