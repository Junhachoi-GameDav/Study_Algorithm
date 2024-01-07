#pragma once
#include <assert.h>

template<typename T>
class Iterator
{
public:
	Iterator() : _ptr(nullptr) {}
	Iterator(T* ptr) : _ptr(ptr){}

	//전위형 ++it ++(++it) 계속 자기자신을 넣을수 있기 때문에
	// & 참조값을 넣는다.
	Iterator& operator++()
	{
		_ptr++; // 늘리고 
		return *this; //자기자신
	}

	//후위형 it++
	Iterator operator++(int)
	{
		Iterator temp = *this; //자기자신을 임시로 넣고
		_ptr++; //늘리고
		return temp;
	}

	Iterator operator+(const int count)
	{
		Iterator temp = *this; //자기자신을 임시로 넣고
		temp._ptr+= count; //count 만큼 더해줌
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

	T& operator*() //참조해야하니까 &
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

	//explicit 매개변수나 함수등에 다른 숫자가 예) 정수 또는 실수 등이 들어가는것을 방지
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

	void resize(int size)
	{
		reserve(size);
		_size = size;
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
	T* _buffer = nullptr;
	int		_size = 0;
	int		_capacity = 0;
};

