#include <iostream>
using namespace std;
#include <vector>
#include <queue>

#pragma region 함수 포인터
//
//void Print()
//{
//	cout << " Hello World " << endl;
//}
//
//int Add(int a, int b)
//{
//	return a + b;
//}
//
////이렇게 하는 이유(함수포인터를 사용하는 이유
//
////행동 자체를 인자로 넘기고 싶을때 -> 일일히 함수를 만들필요없이 간단한 함수들은 곧바로 만들수 있기 때문
////나중에 람다식등을 이용하면 굉장히 편하기 때문에 쓴다.
//// 예)
//using FuncPtrType = int(*)(int a, int b);
//
//int DoSomething(int a, int b, FuncPtrType func)
//{
//	return func(a, b);
//}
//
//
//// 콜백 함수
//// ui 나 키보드입력 등 바로 바꿔야하는 동작등에 사용한다.
//// 만약 함수포인터가 없다면 일일히 다만들어야게겠지만 그렇지 않다~~!!!
//
//class Item
//{
//public:
//
//public:
//	int _itemId = 0;
//	int _rarity = 0;
//	int _ownerId = 0;
//};
//
//// 특정 아이템을 찾는다고 할때 함수를 하나하나 만들면 힘들다. 그러나..
//using ItemSeletorType = bool(*)(Item* item);
//
//Item* FindItem(Item items[], int itemCount, ItemSeletorType seletor)
//{
//	for (int i = 0; i < itemCount; i++)
//	{
//		Item* item = &items[i];
//		//if (item->_rarity == 1) { return item; }
//		if (seletor(item)) { return item; }
//	}
//
//	return nullptr;
//}
//
//bool IsRare(Item* item)
//{
//	return item->_rarity == 1;
//}
//
////맴버함수 포인터 용 클라스
//class Test
//{
//public:
//	void PrintTest() {}
//};

#pragma endregion

#pragma region 함수 객체

// 함수 객체를 사용하는 이유
// 함수포인터의 단점
// - 시그니쳐가 안맞으면 사용 못함
// - 상태(바인딩)를 가딜수 없음

class Functor
{
public:
	void operator() () //오버로딩 할수 있다.
	{
		cout << "Functor Test" << endl;
		cout << _value << endl;
	}
	void operator() (int n)
	{
		cout << "Functor Test" << endl;
		_value += n;
		cout << _value << endl;
	}
public:
	int _value = 0;
};


struct AddStruct
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};

//using FuncType = int(*)(int, int); 인트 포인터로 지정되어있다.
template<typename T> 
int DoSomething(int a, int b, T func)
{
	return func(a, b);
}

// vector에 greater<//> 도 저렇게 템플릿으로 만든것이다. 
// operator()() 이것으로 처리(로직)등을 만들고 템플릿으로 함수를 임의로 정의해놓고 사용하는것이 
// 함수 객체이다.( 그래서 함수 포인터를 사용할 일이 크데없다. 상위호환)

// 이것으로 특정부모클라스를 만든뒤 거기에 모든행동을 넣고(virtual 소멸자 필수)
// 자식 클라스에서 행동 로직을 짤때 함수 객체로 짠후 
// 실행할때 부모 클라스를 인자로 넣으면 일일히 클라스를 넣을 필요없이 부모클라스 하나만 넣으면 됨

#pragma endregion

//
//int main() {
//	//이런식으로 동작한다는 것이지 이런 문법은 잘 안쓴다.
//	//using Datatype = int;
//	//using FuncType = void(); //함수 타입
//	//FuncType* ptr = &Print; // 주소값을 넘겨줄수있음 포인터라서
//
//	//ptr();
//
//	//함수 포인터 (정적/전역)
//	//void(*FuncPtrType)(); // 옛날방식 
//	//using FuncPtrType = void(*)();
//	//FuncPtrType ptr = &Print;
//
//
//	//DoSomething(10, 20, &Add);
//	//DoSomething(10, 20, [](int a, int b) {return a - b; }); //일명 함수라고 해서 곧바로 안에 함수를 만듬
//
//
//	//Item items[10];
//	//items[3]._rarity = 1;// true
//
//	//FindItem(items, 10, &IsRare);
//
//
//
//	//맴버 함수 포인터 (정적/ 전역(static) 함수랑 다르다)
//	//활용을 많이 안한다고 한다. 그래도 알고는 있어야함. 엔젠간 씀...
//	//함수를 지연 호출할수있다는 장점이 있어서 서버에서 많이씀
//	/*using MemFuncPtrType = void(Test::*)();
//	MemFuncPtrType funcPtr = &Test::PrintTest;
//
//	Test t;
//	(t.*funcPtr)();*/
//
//	//Test* t2 = &t;
//	//t2->PrintTest();
//	//(t2->*funcPtr)();
//
//
//	//함수포인터는 많이쓰긴 하지만 바인딩(동적으로 데이터 바꾼것으로 동작하는것)이 안된다는 단점이있음
//	//이때 쓰는것이 함수 객체임
//
//
//	//Functor func;
//	//func._value = 10;
//
//	//func();
//
//	AddStruct func;
//
//	DoSomething(10, 20, func);
//}