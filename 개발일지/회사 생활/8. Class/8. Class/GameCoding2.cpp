#include <iostream>
using namespace std;

// �̰� ���� ���� �ʼ� ����̴�.
//��ü���� (OOP)�� 3 �� ���
// - ��Ӽ� << inheritance
// - ���м� << data hiding (�Ǵ� ĸ��ȭ encapsulation)
// - ���⼺ << ploymorphism ( poly + morphism ) �پ� + ��ü

//is-a vs has-a
//����Ʈ�� �÷��̾��? ���� is-a
//����Ʈ�� �÷��̾ �������ִ�? no is-a(x) has-a


/* ���
class Player
{
public:
	void move() { };
	void attack() { };
	void die() { };
public:
	int _hp;
	int _attack;
	int _defence;
};

class Knight : public Player
{
	int _dddd;
};
class Acher : public Player
{

};


void Fight(Player* k1, Player* k2)
{

}
*/

/*
 ����(ĸ��ȭ)
 ����ڰ� ���� �Ǵ°͵��� ����ų� �ǵ�� �ȵǴ°��� ����� ����
 (����)���� ������ ����Ѵ�.
 public , private , protected
class Car 
{
	
public://����(��� ��밡��)
	void Move(){}

private://����� ( �ڽŸ� ��밡��)
	void Engine(){}

protected://���ΰ� ��ӹ��� Ŭ�󽺴� ��밡���ϴ� ����
	void Test(){}
};


 ��� ���� ������ = �ڽ����� ����� ��� �������� ����
 public = �θ���� ��� ���ڴ�. ��κ� �̰͸� ����.
 protected = �ڼո� �����ְڴ�. (public -> protected)
 private = �������� �ܺ���. (public, protected -> private) �ڽĿ� �ڽ��� ����
class SuperCar : private Car
{
public:
	void test()
	{
		Test();
	}
};

class UltraSuperCar : public SuperCar
{
public:
	void test()
	{
		Test(); ����
	}
};
class Knight
{
public:
	void SetHp(int _hp)
	{
		_hp = 40;
	}

	int GetHp()
	{ 
		return _hp;
	}

private:
	int _hp =100;
};

*/

//����
// ���� �������� �����ϴ� �����̶��Ѵ�.
//�����ε�(overloading) = �Լ� �̸��� ����
//�������̵�(overriding) = ������


//�߻� Ŭ�� = ���� �����Լ��� �ϳ��� ������ �߻�Ŭ�󽺰� ��. ���������� ���� �ʰ� �������� ���ڴٴ� �����
class Player 
{
public:
	//virtual void Move() { cout << " moving" << endl; }

	virtual void Move() = 0; //�̰��� ���� �����Լ���� �� -- �� �����Լ��� ����� ��ӵ� Ŭ�󽺿��� ����ڴٴ� ��
	//virtual void Move() = abstract; // �̰Ŵ� ������ �Ȱ��� ���� ����

public:
	int _hp;
};

class Knight : public Player
{
public:
	virtual void Move() override { cout << " moving" << endl; }
	// ���� virtual�� ������ ��ǻ� ���⿡ virtual�� �����Ǿ��ִٰ� �����ִ�. �򰥸��ϱ� �׳� �Ѵ� ���ָ� ����.
	// �Ǽ��� �θ� virtual ������ overriding���� �˻��Ҽ� �ִ�. c#�� �ٸ��� �Լ� �ڿ� �ٴ´�.

	//�߻� Ŭ�󽺸� ��ӹް� �Ǹ� �ݵ�� �����Լ��� ������ ������ �ȳ���.

};

// ���ε�(Binding) = ���´�.
// - ���� ���ε� (static binding = ������ ���� ����) �Ϲ����� �Լ�
// - ���� ���ε� (dynamic binding = ���� ���� ����)
void MovePlayer(Player* player)
{
	player->Move();
}

int main() {

	/*���
	Knight k1;

	Acher a1;
	//Player p1 = k1; �̷��� �����Ͱ� �θ� Ŭ�󽺺��� ���ڶ� �������� ������
	//Player* p1 = &k1;
	//Knight* p2 = (Knight*)p1; �̰� ���� fight �Լ� �����̶� ���� ����

	Fight(&k1, &a1);
	*/

	/*����
	Knight k1;

	//k1._hp =100; �̷��� �ϸ� �ſ�� �����ʴ�.�������� �ڵ�� ���ø� ��� ��� �ڵ���
	//get set �Լ��� ����� �����ϸ� ����
	k1.SetHp(100);
	*/

	//����
	Knight k1;

	//k1.Move();
	MovePlayer(&k1);
	//virtual�� ������ �޸𸮻� �ٸ� ������ �޸� ��(vftabale [�ּ�1 | �ּ�2 | �ּ�3... ])�� ������ �ǰ� 
	// ���� ���ε��� �Ͼ�� �������� ������ ������ �����ȴ�.
	//�׷��� ��ǻ� �޸𸮸� ����� �ֱ� ������ ���ݴ� �������� ũ�� ���̵� �ȳ��� ���� �̵�ɰ� ���Ƽ� 
	//�Ⱦ��� ����
}