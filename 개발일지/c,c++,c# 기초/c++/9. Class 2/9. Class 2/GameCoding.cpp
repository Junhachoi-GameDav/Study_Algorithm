
#include <iostream>
using namespace std;


// �ɹ� ���� �ʱ�ȭ
// �����ڿ� �Ҹ���


class Player
{
public:
	Player() 
	{
		cout << "Player()" << endl;
	};
	~Player()
	{
		cout << "~Player()" << endl;
	};
};


class Inventory
{
public:
	Inventory()
	{
		cout << "Inventory()" << endl;
	}
	Inventory(int a) //�̷��� ���������
	{
		_a = a;
		cout << "Inventory(int)" << endl;
	}
	~Inventory()
	{
		cout << "~Inventory()" << endl;
	}
public:
	int _a = 0;
};


class Knight : public Player
{
public:
	//Knight() : Knight(0)  �����ڳ����� ȣ���Ҽ��� �ִ�.
	Knight() : _hp(0) , _inventory(100) , _hpRef(_hp) , _hpConst(_hp)
		//������ �ȿ� �ִ°ͺ��� �̷��� ���� �δ°� ������ ȿ�����鿡�� ����.
	/*
	��ó�� ����
	Player()
	_inventory = Inventory()
	*/
	{
		//_hp = 0;
		//_inventory = Inventory(100); �̷��� �ȿ������� ��ó�� �������� �ι��̻� ���� �ϰų� �����Ⱚ�� �������� �ִ�. 
		cout << "Knight()" << endl;
	};
	~Knight() 
	{
		cout << "~Knight()" << endl;
	};

public:
	//int _hp = 100; // �Ǵ� ����ٰ� �ʱ�ȭ ���൵ �ȴ�.
	// ���⿡ �ʱ�ȭ�� �����ϸ� ��� �����ڿ� ȣ��ɼ��ֱ⶧���� �����ڰ� ������ ����� �ϴ°� ȿ�����̴�.
	int _hp;


	//�ٸ� ���� ������ const ���� ������ ȣ������� ������ ������ �ȳ���.
	int& _hpRef;
	const int _hpConst;



	Inventory _inventory;
};


int main() {

	//int value
	// ��Ʈ���� ������ {} �ȿ� �ֵ� �ۿ� ���� ���ɻ� �ƹ��� ���̰� ����. �׳� �ȿ��� ���ų� ��ü���� ���ų� ���� 
	for (int i = 0; i < 10; i++)
	{
		int value = i;
		cout << value << endl;
	}

	// ������ �����ڴ� {} �ȿ��־����� ������ } ���� �Ҹ��ڸ� �����ϱ� ������ �ٽ� {}�ȿ� �Ȱ��� �����ڰ� ����Ǵ°� �ƴ϶�
	// ���ο� �����ڸ� �����ϴ� �Ͱ� ����. 
	// �̰��� ���� ���̸� ������ �ϴ°��̴�.
	for (int i = 0; i < 10; i++)
	{
		Knight k1;//����
		cout << k1._hp << endl;
	}//�Ҹ� 10�� �ݺ�


	Knight k2;//����

	for (int i = 0; i < 10; i++)
	{
		cout << k2._hp << endl;
	}

}	//k2 �Ҹ� (�ѹ���)