#include <iostream>
using namespace std;

// struct vs class

//c#������ �ΰ��� ���̰� �ſ�ũ��. 
// struct�� ������ ���� Ÿ������ �����ϰ� class�� ������ ���� Ÿ������ ������ 
// 
// 
//c++ �� �ΰ��� ���� ���̰� ����. ���������� ���̸� �ִ�
//struct = public �̶� class = prevaite ���� - �ȿ� ������ ������ �⺻���� �̷��� ��.
// public �� ��� ������ �Ⱦ struct�� ����ϴ� ����鵵 �ִµ� �ſ� ������ �����̶�� �Ѵ�.
//���� struct�� �������� �����͸� ��Ƽ� �����ϴ� �뵵�� ����ϰ�
//class�� ��ü���� �뵵�� ����Ѵ�.



// static
// �ۿ��� ��������ó�� �޸� ��򰡿��� ������ �ȴ�.
// ���̻� marine Ŭ�󽺿� ������� �ʰ� ���� �ۿ� �����Եȴ�.
class Marine
{
public:
	void TakeDamage(int damage)
	{
		hp -= damage;
	}

	//�̷��� ���� Ư�� Ŭ�󽺿� ���� ����������. �� �� �Լ��ȿ��� ������ ������ �����Ҽ�����.
	//�׳����� �Լ��� �ǹ��� ���̴�.
	static void SetAttack(int value)
	{
		attack = value; //������ ���� static�� �ǵ帱�� �ִ�.
	}


public:
	int hp;
	static int attack; // ����ƽ���� �����ϸ� ������ ���ð��̶�� ������ ���̱⶧���� ������ �ȵȴ�. �ؿ��ٰ� �ϸ� �ȴ�.
	// ������ �����⶧���� �׷��� ����.
};

int Marine::attack = 6; //���� ��� ������ ���ݷ��� 6�̴�.
//�̰� ���� ���ô� �ƴϴ� ���ʿ� �̷� states�� ���� ���� �����ϴϱ� ������� ���� ��Ŵ�.



//���� id�� ������ �����ϰ� ������ ���� ������ ����ϸ� �������ϴϱ� �ȿ� static������ �����.
class Player
{
public:
	Player()
	{
		id = s_idgenerator++;
	};
public:
	int id;
	static int s_idgenerator;
};

int Player::s_idgenerator = 1;

// ���������� static�� �����ϸ� ��������ó��(��¥ ���������� �ƴ�) �ǹ���



// �̱���
// 1���� �����ϰ� ��� ����ϴ� �� 

class UserManager
{
public:
	static UserManager* GetInstance() //������ static ������ �����Ѵ�.
	{
		static UserManager um;
		return &um;
	}

	//���� ������ ���~
public:
	void AddUser() { _userCount++; }
	int GetUserCount() { return _userCount; }
public:
	int _userCount = 0;
};


//���͸����� ���~!!
//#define GET_MANAGER(UserManager::GetInstance()) // �̷��� ���ϼ� �ִ�.

int main() {
	/*Player player1;
	Player player2;
	Player player3;*/
	// �ø����� count �ؼ� ���� �ø�


	UserManager::GetInstance()->AddUser(); //�̷������� ��� cpp���Ͽ����� �ҷ��ͼ� ��밡��
	//GET_MANAGER->AddUser(); �̷��� ���ϼ� �ִ�.
}