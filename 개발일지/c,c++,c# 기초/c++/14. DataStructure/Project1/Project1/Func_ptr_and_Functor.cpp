#include <iostream>
using namespace std;
#include <vector>
#include <queue>

#pragma region �Լ� ������
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
////�̷��� �ϴ� ����(�Լ������͸� ����ϴ� ����
//
////�ൿ ��ü�� ���ڷ� �ѱ�� ������ -> ������ �Լ��� �����ʿ���� ������ �Լ����� ��ٷ� ����� �ֱ� ����
////���߿� ���ٽĵ��� �̿��ϸ� ������ ���ϱ� ������ ����.
//// ��)
//using FuncPtrType = int(*)(int a, int b);
//
//int DoSomething(int a, int b, FuncPtrType func)
//{
//	return func(a, b);
//}
//
//
//// �ݹ� �Լ�
//// ui �� Ű�����Է� �� �ٷ� �ٲ���ϴ� ���۵ ����Ѵ�.
//// ���� �Լ������Ͱ� ���ٸ� ������ �ٸ����߰԰����� �׷��� �ʴ�~~!!!
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
//// Ư�� �������� ã�´ٰ� �Ҷ� �Լ��� �ϳ��ϳ� ����� �����. �׷���..
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
////�ɹ��Լ� ������ �� Ŭ��
//class Test
//{
//public:
//	void PrintTest() {}
//};

#pragma endregion

#pragma region �Լ� ��ü

// �Լ� ��ü�� ����ϴ� ����
// �Լ��������� ����
// - �ñ״��İ� �ȸ����� ��� ����
// - ����(���ε�)�� ������ ����

class Functor
{
public:
	void operator() () //�����ε� �Ҽ� �ִ�.
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

//using FuncType = int(*)(int, int); ��Ʈ �����ͷ� �����Ǿ��ִ�.
template<typename T> 
int DoSomething(int a, int b, T func)
{
	return func(a, b);
}

// vector�� greater<//> �� ������ ���ø����� ������̴�. 
// operator()() �̰����� ó��(����)���� ����� ���ø����� �Լ��� ���Ƿ� �����س��� ����ϴ°��� 
// �Լ� ��ü�̴�.( �׷��� �Լ� �����͸� ����� ���� ũ������. ����ȣȯ)

// �̰����� Ư���θ�Ŭ�󽺸� ����� �ű⿡ ����ൿ�� �ְ�(virtual �Ҹ��� �ʼ�)
// �ڽ� Ŭ�󽺿��� �ൿ ������ ©�� �Լ� ��ü�� §�� 
// �����Ҷ� �θ� Ŭ�󽺸� ���ڷ� ������ ������ Ŭ�󽺸� ���� �ʿ���� �θ�Ŭ�� �ϳ��� ������ ��

#pragma endregion

//
//int main() {
//	//�̷������� �����Ѵٴ� ������ �̷� ������ �� �Ⱦ���.
//	//using Datatype = int;
//	//using FuncType = void(); //�Լ� Ÿ��
//	//FuncType* ptr = &Print; // �ּҰ��� �Ѱ��ټ����� �����Ͷ�
//
//	//ptr();
//
//	//�Լ� ������ (����/����)
//	//void(*FuncPtrType)(); // ������� 
//	//using FuncPtrType = void(*)();
//	//FuncPtrType ptr = &Print;
//
//
//	//DoSomething(10, 20, &Add);
//	//DoSomething(10, 20, [](int a, int b) {return a - b; }); //�ϸ� �Լ���� �ؼ� ��ٷ� �ȿ� �Լ��� ����
//
//
//	//Item items[10];
//	//items[3]._rarity = 1;// true
//
//	//FindItem(items, 10, &IsRare);
//
//
//
//	//�ɹ� �Լ� ������ (����/ ����(static) �Լ��� �ٸ���)
//	//Ȱ���� ���� ���Ѵٰ� �Ѵ�. �׷��� �˰�� �־����. ������ ��...
//	//�Լ��� ���� ȣ���Ҽ��ִٴ� ������ �־ �������� ���̾�
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
//	//�Լ������ʹ� ���̾��� ������ ���ε�(�������� ������ �ٲ۰����� �����ϴ°�)�� �ȵȴٴ� ����������
//	//�̶� ���°��� �Լ� ��ü��
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