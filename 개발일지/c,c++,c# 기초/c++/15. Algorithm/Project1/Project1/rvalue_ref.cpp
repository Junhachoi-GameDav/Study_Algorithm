#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

class Pet
{

};

class Knight
{
public:
	Knight() {};

	~Knight()
	{
		if (_pet) { delete _pet; }
	}

	//���� ������
	Knight(const Knight& knight)
	{

	}

	//���� ���� ������
	void operator=(const Knight& knight)
	{
		_hp = knight._hp;
		if (knight._pet)
			_pet = new Pet(*knight._pet); // �Ѵ� �Ȱ������� ����Ű�� �ϳ��� �Ҹ��Ҷ� ��ã�Ƽ� ������ 
	}

	//�̵� ������
	Knight(Knight&& knight)
	{
		_hp = knight._hp;
		_pet = knight._pet;
		knight._pet = nullptr;
	}

	//�̵� ���� ������
	void operator=(Knight&& knight) //������ �ڷḦ �ٲ�����
	{
		_hp = knight._hp;
		_pet = knight._pet; //���簡 �ƴ϶� �̷��� �ᵵ ����
		knight._pet = nullptr;
	}

public:
	int _hp = 0;
	Pet* _pet = nullptr;
};

void TestKnight_Copy(Knight knight)
{
	knight._hp = 100; //������ �ƹ��� ������ ���� ����ȰŶ�.
}

//������ �Ѱ����״�... �ǵ������
void TestKnight_LValue(Knight& knight)
{
	knight._hp = 100; //������ ������
}

//������ �Ѱ����״�...�ǵ帱 �� ����
void TestKnight_ConstLValue(const Knight& knight)
{
	//knight._hp = 100;
}

//&&�� �ΰ� ������ ������ ����? �� �ƴ϶� ������ ������� ���ο� �����̴�..!!
//������ �Ѱ����״�...�� �̻� ������ Ȱ������ ���� �״� ����� ��
void TestKnight_RValueRef(Knight&& knight)
{
	knight._hp = 100; //�������� + ���� ���� �Ⱦ�
}
//
//int main() {
//	//c++11  rvalue_ref ������ ����
//
//	// l-value : ���Ͻ��� �Ѿ ��� ���ӵǴ� ��ü
//	// r-value : l-value�� �ƴ� ������
//
//	int a = 3;
//	a = 10;
//	a = 5;  //a  :  l-value (�ް�)
//	//������ 3, 10, 5 �� �������̴�.
//
//
//	Knight k1;
//	k1._pet = new Pet();
//
//	Knight k2;
//
//	//k2 = static_cast<Knight&&>(k1); //k1�� ���̻� ������� �����Ŵϱ� �� ���� ��� //������ �� �����Ⱑ ��
//	k2 = move(k1); //�Ѵ� �Ȱ��� ���״�� �̵��̶�� �����̱� ������ ��Ȯ���� rvalue_cast ��� �����Ѵ�.
//
//	//Knight k2 = k1; //���� �����ڰ� ����
//	//Knight k2;
//	//k2 = k1; // ���� ���� �����ڰ� ����
//
//	//TestKnight_Copy(k1);
//	// �ӽð�ü(���Ͻ��̾ƴ�) knight()�� ������
//	//TestKnight_LValue(Knight()); //const �� ������ ���ʰ��� �޴´�.
//	//TestKnight_ConstLValue(Knight());
//
//	//TestKnight_RValueRef(k1); //�̷��� ���� ������ ������̰ų� ����ҰŶ� ������ ��� �׷���..~~!!
//	//TestKnight_RValueRef(static_cast<Knight&&>(k1)); //�̷��� &&���������� ĳ���� �ع����� ��..
//
//
//	//�׷��� �̰� ���� ���°�
//
//	//vector���� �迭�� �ٸ� �迭�� �����ؼ� �ٿ��ִ°� ȿ���� ������.
//	// ������ ū ���̰� ������ �迭�̳� �Լ��� ��û �׸� ���簡 �ſ� ������̴�. �׶� �̵��ϴ°�
//	// �Ǵ� ������ ���� �� ���״�� �̵��ؾ� ȿ�����϶� ����.
//	// ������ ���Ӱ����Ÿ� ���鶧�� ���� �Ⱦ���. ������ ���̺귯���� ��ũ��Ʈ �����Ͼ�� ���� ���� ���� �ִ� �ڵ��� �Ҷ� ���� ���ٰ��Ѵ�.
//}