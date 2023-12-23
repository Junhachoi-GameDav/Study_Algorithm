#include <iostream>
using namespace std;

// �Լ�		���ø�
// Ŭ��	���ø�

//C# ������ ���׸����� �Ҹ�

//�ظ��ϸ� ������Ͽ� ������. cpp�� ������ ������ ��û ����������.


#pragma region �Լ� ���ø�

// �̷������� �̸��� ���س��� ��Ʈ�� ��� char����� ������ �ڵ����� ��ȯ(����)��
// �������� ���°� �ƴ϶� �����Ϸ��� �Լ��� ���� ����°���
// printint() �� printfloat()�� ���� ���� �ȸ��� �����Ϸ��� ���� �����ϴ°���
template<typename T>

void Print(T a)
{
	cout << a << endl;
};

//�� �ѹ��� �ϴ°��� �ƴϴ�. ������ ���� �ȴ�.
template<typename T1, typename T2>
void Print(T1 a, T2 b)
{
	cout << a << " " << b << endl;
};


// ���� ��Ʈ������ ���� ���� �ʹٰų� �Ҷ� �̷��� ��ĭ�� �ְ� ���� ����� �ȴ�.
template<>
void Print(int a)
{
	cout << a << endl;
}

#pragma endregion

#pragma region Ŭ�� ���ø�
template<typename TC = int, int SIZE =100>
//�̷������� �ʱⰪ�� ������ ���� ���� �� typename�� ������ �ִ°� �ƴϴ�.
class RandomBox
{
public:
	TC GetRandomData()
	{
		int index = rand() % SIZE;
		return data[index];
	}

public:
	TC data[SIZE];
};

#pragma endregion

// ���ø�
// Ư��ȭ
//
//int main() {
//	Print(1);
//	Print(3.14f);
//	Print("���ڿ�~");
//
//	Print(1, "���ڿ�");
//
//	//�̷������� �������� �����Ҽ��� �ְ� ���ϸ� �ڵ����� �����Ǵ°���
//	Print<int>(1);
//	Print<float>(3.14f);
//	Print<const char*>("���ڿ�~");
//
//	Print<int, const char*>(1, "���ڿ�");
//
//	// ��ǻ� ������ Ŭ�󽺴�. = �ϳ��� Ŭ�󽺰� �ƴ϶� �ΰ��� �������
//	RandomBox<int, 100> rb1;
//	RandomBox<float, 200> rb2;
//}