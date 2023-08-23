/*
#include <iostream>
//#include "Player.h"
using namespace std;


// c#�� �ٸ��� c++ �� ����ü�� Ŭ�󽺰� ������ ����.

//Ŭ���� == ���赵
class Knight
{
public:
	//�ʱⰪ�� �����ϴµ ���� �Ѵ�.
	// �� ����� �����Ϸ��� �ڵ����� ������ش�. ������ (��Ÿ�� ���)�����ڸ� �����
	// ���İ� �� ����� �ش�. 
	//�⺻ ������ (constuctor) //����
	Knight()
	{
		m_hp = 0;
		m_attack = 0;
		m_defence = 0;
		cout << "knight()" << endl;
	}

	//���� ������
	Knight(const Knight& other)
	{
		this->m_hp = other.m_hp;
		this->m_attack = other.m_attack;
		this->m_defence = other.m_defence;
	}

	//��Ÿ(�Ϲ�) ������
	Knight(int hp, int attack, int defence)
	{
		m_hp = hp;
		m_attack = attack;
		m_defence = defence;
		
		this->m_hp = hp;
		this->m_attack = attack;
		this->m_defence = defence;

		cout << "knight()" << endl;
	}

	//�Ҹ��� (destructor) //���� �������� �����
	//�޸𸮰��� ���� ���� ���� �Ѵ�.
	~Knight()
	{
		cout << "~knight()" << endl;
	}

	//�ɹ� �Լ�
	void Attack() { cout << "Attack" << endl; }
	void Die() { cout << "Die" << endl; }
	void HealMe(int value)
	{ 
		m_hp += 10;
	}

public:
	//�ɹ� ����
	int m_hp;
	int m_attack;
	int m_defence;
};

//Ŭ�� �ȿ� �ִ� �������� �޸�(����)������ ������ �Լ��� �ڵ� ������ ���⶧����(�����Լ��� �ƴ϶�)
//�ᱹ �����κи� �޸𸮸� �Ἥ �Լ��� �ƹ������Ƶ� ������ ������ �뷫�� ���ٰ� �Ҽ��ִ�.
//�����Լ��϶��� �����ͷ� ������ ���������� Ŭ�󽺾ȿ� �Լ��� ������ ������ ���ξȿ��� �ǵ�� ������ �����͸� �����ʾƵ� �Ȱ��̴�.
//������ ������� ����� �������� �����Ѵ�.


int main() {
	Knight k1(100, 10 ,1); //��Ÿ ������

	Knight k2(k1); //���� ������ ���� �����ؼ� �ٸ��Ϳ� ������

	//Player k1; //������

	k1.m_hp = 100;

	k1.Attack();
	k1.Die();

	k1.HealMe(10);
}
*/