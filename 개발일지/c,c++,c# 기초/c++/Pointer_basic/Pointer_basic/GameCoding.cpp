#include <iostream>
using namespace std;

void Swap(int* a, int* b) //�ŰԺ����� �������̴ϱ� �ּҰ��� �޾ƾߵɰ���.
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//����
void Print(int* ptr, int count) // int &number[10] 
{

}



struct  StateInfo
{
	int hp;
	int attack;
	int defence;
};

StateInfo CreatePlayer() //�̰� �����ؼ� ������ �����̴�. �̷� ������ �������� ���߿� �޸𸮸� ���� ��� ������ �ִ�. 
{
	StateInfo info;

	cout << "�÷��̾� ����" << endl;

	info.hp = 100;
	info.attack = 10;
	info.defence = 1;

	return info;
}

/*
//�̷��� �ϸ� ũ������ �ȳ����� ����� �۵��� ���Ѵ�. 
StateInfo* CreatePlayer2()// �����ʹ� �ּҰ��� �޴°Ŵ�. 
{
	StateInfo info;  //�̷��� �ȿ����� ��ȿ�� �����̰� �̰� ȣ���Ҷ� ���ÿ��� �������ų� ����Ѱ��� �޴´�.

	cout << "�÷��̾� ����" << endl;

	info.hp = 100;
	info.attack = 10;
	info.defence = 1;

	return &info; //�װ� ��ȯ�ؼ� �ƹ��͵� ���°���
}
*/

void CreateMonster(StateInfo* info) 
{
	cout << "���� ����" << endl;

	info->hp = 40;
	info->attack = 8;
	info->defence = 1;
}

void Battle(StateInfo* player, StateInfo* monster)
{
	while (true)
	{
		int damage = player->attack - monster->defence;
		if (damage < 0) { damage = 0; }
		monster->hp -= damage;

		if (monster->hp < 0) { monster->hp = 0; }

		cout << "������ HP : " << monster->hp << endl;

		if (monster->hp == 0) { return; }


		damage = monster->attack - player->defence;
		if (damage < 0) { damage = 0; }
		player->hp -= damage;

		cout << "�÷��̾��� HP : " << player->hp << endl;

		player->hp -= damage;
		if (player->hp < 0) { player->hp = 0; }

		if (player->hp == 0) { return; }
	}
}

int main() {

	/*
	// Ÿ�� * �̸� =~~;
	//�����ʹ� �ּҰ��� ��� �ٱ��� ��� �����ϸ�ȴ�.
	// 64��Ʈ �ü�� ������ ���� ������ �ڷ����� ��� 8����Ʈ�̴�. �տ� �����ֵ�������...
	// &�� �ּ��̰� *�� �ּҰ��� ���� �ٱ����̴�. �� hp�� �̼Ҹ� ����ִٴ� ��
	// ��ǻ� (int*) ptr�̶�� �ǹ̴�. �� ��Ʈ���� ������ ��� �ڷ����̰�.

	// �ּ� ���� Ÿ�� ���� -> ������ �ִ°�?
	
	//int* ptr = &hp;

	//�������ε� �����ִ�. �����͸� ����Ű�� �������̴�. �� �ٱ����� �ٱ���.
	//��ǻ� (int*)* pptr �̴�. ��Ʈ���� �������� ������
	// �ּ� -> �ּ� -> int   ���ı���� ���� ����.
	
	//int** pptr;


	//�������� ���� ���� ��ü�� �����Ҽ� �ֱ⶧���� �޸𸮸� �Ƴ����� �ִ�. 
	// ���� ������ �����ϴ°��� �ƴ϶� �����ϴ� ���̱⿡ ���û󿡼��� �����޸𸮴� �״�� ������ �ִ�.
	//�� ��� ���縸 �ϴ°��̴�. �̶� �����͸� ����ϸ� �ϳ��� �޸𸮷θ� ������ �̷�����ϱ� �޸� ���ϰ� ���ϴ�.

	//void* ptr = nullptr; //�ּҰ��� 0���� �Ѷ�

	//�̷��� �ϸ� 
	//int a = 10; int b = 20;

	//Swap(&a, &b); //�ּҸ� ����.

	// �̰��� ��������� �Ѵ�. �ּҸ� ��� ���� �ƴ϶� ���� �ּҷ� �����̵��϶�� �ǹ�
	//// *ptr �� �ּҸ� Ÿ�� �̵��϶�� �ǹ�

	//cout << a << endl;
	//cout << b << endl;

	//������ ������
	// - �ּ� ������ (&)
	// - ��� ������ (+-)
	// - ���� ������ (*)
	// - ���� ��� ������ (->)

	//int* ptr = &hp;
	//ptr += 1; // hp�� ���� 1�� �������� ������ ������ ptr�� ���� �޸� �ּҸ� ����Ų��. �� int �� 4����Ʈ�ϱ� 104�� ��.
	// ���̷��� �Ǿ��ִ°� �ϸ� �迭�� ���� �����϶�� �׷���

	//int number[10] = { 1,2,3,4,5,6 };

	//int* ptr = &number[0];
	//int* ptr = number; �̰͵� �ȴ�. c++���� �迭�� �̸��� ���� &number[0]�� ����.

	//*(ptr + 3) = 666; // index 4 ��° �� 666���� �ٲ�

	//ptr[3] �������� �̰Ŷ�� �������ִ°�



	// �����ʹ� ����ü�� Ŭ�󽺵� ����ų�� �ִ�.

	//StateInfo monster;
	//monster.hp = 100;
	//monster.attack = 10;
	//monster.defence = 1;

	//StateInfo* ptr = &monster;

	//(*ptr).hp;
	//ptr->hp;    //�Ѵ� �Ȱ���.

	//.�� �Ϲ��Լ� ������ �������� ->�� �����ͷ� �Ǿ��ִ� �Լ��϶� ����
	*/

	//����ü�� Ȱ���ؼ� ����
	StateInfo player;
	player = CreatePlayer();

	//�����͸� Ȱ���� ����
	StateInfo monster;
	CreateMonster(&monster);

	Battle(&player, &monster);
}