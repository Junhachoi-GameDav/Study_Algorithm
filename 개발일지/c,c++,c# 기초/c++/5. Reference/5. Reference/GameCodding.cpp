#include <iostream>
using namespace std;

struct StateInfo
{
	int hp;
	int attack;
	int defence;
};

//��(����) ���� ��� = ������ ��ĵ�
void PrintByCopy(StateInfo player)
{
	cout << "----------" << endl;
	cout << "HP : " << player.hp << endl;
	cout << "ATT : " << player.attack << endl;
	cout << "DEF : " << player.defence << endl;
	cout << "----------" << endl;
}

//�ּҸ� �����ϴ� ��� = ������
void PrintByPointer(StateInfo* player)
{
	cout << "----------" << endl;
	cout << "HP : " << player->hp << endl;
	cout << "ATT : " << player->attack << endl;
	cout << "DEF : " << player->defence << endl;
	cout << "----------" << endl;
}

//���� ���� ���
void PrintByRef(const StateInfo& player) //�Ű������� &�� ���̸� �ּҰ��ƴ϶� ����ǥ���̴�.
{
	cout << "----------" << endl;
	cout << "HP : " << player.hp << endl;
	cout << "ATT : " << player.attack << endl;
	cout << "DEF : " << player.defence << endl;
	cout << "----------" << endl;
}

//������� ����
// #define IN
//�������̽��� ���� �б⸸ �Ѵٴ� �ǹ��Դϴ�.
//�Ű� ������ ������ ���޵Ǵ� ��� �Լ��� �۾��� ������ ���� ������ �����Ƿ� ������ const�� �������� �ʾƵ� �˴ϴ�. 
//���縦 �����Ϸ��� ������ ���� ������ ��ȣ�ǹǷ� ������ �����ϱ� ���� const�� ����ϴ� ���� �����ϴ�.

// #define OUT
//�Ű������� out���� ǥ�õǸ� �Լ��� ���� ���� �ʿ䰡 ������ �Ű����� ���� �߿����� ������ �ǹ��մϴ�. 
//������ ǥ�õ� �Ű������� ���� ���� ����ϴ� �� �ʿ��մϴ�. 
//�̷��� �Ű������� ������, ���� �� �������� �մϴ�.

// �̷� �͵� �ִ� ������ ���� ������ const �̴�.
//#define OUT
//void PrintByRef(OUT StateInfo& player) //�Ű������� &�� ���̸� �ּҰ��ƴ϶� ����ǥ���̴�.
//{
//	cout << "----------" << endl;
//	cout << "HP : " << player.hp << endl;
//	cout << "ATT : " << player.attack << endl;
//	cout << "DEF : " << player.defence << endl;
//	cout << "----------" << endl;
//}

int main()
{
	StateInfo player = { 100, 10, 1 };
	PrintByCopy(player);

	//�����͸� ����ϴ� ���� ū����
	//1. ������ �ǵ帮�������(��������)
	//2. ������ �Ƴ���
	PrintByPointer(&player);


	//StateInfo* ptr = &player;
	//������ ������ó�� �ּҸ� ����Ű�� �����̴�.
	//�� ref�� �ǵ�� *player�� �ǵ�ٶ�� ���� ���״�� ����
	//StateInfo& ref = player;

	//ref.hp = 10; //���������� �ȴ�. ������ ������ó�� �ּҸ� Ÿ���� ������ �ǵ�°� �ƴϴ�.
	//�� ���� ������ ������ó�� �ּҸ� �޾����� ����ϴ� ���� ����� ���� ref�̰� �������� ���� �����Ŵ�...
	// 
	//�� � ���� =====�г���====== �����Ŵ�.

	//������ ����ϴ� ������ =
	//�������� �ȿ��ִ� ������ ��� �����Ѵ�.. �׷��⿡ �����͸� ����ϰ� �Ǵ°�����
	//��������� �ּҰ��� �����Ѵ�.!!!!! �׷��� ������ �ǵ�� �Ŷ� 
	//�� ������ ��� ���������ִ�.
	PrintByRef(player);


	//�׷��� 
	StateInfo* ptr = nullptr; //�����ʹ� nullptr �� ���ٴ� ǥ�ø� �Ҽ��ִ�.
	//�� ������ ���ٴ� ǥ�ø� �Ҽ��ִ� ����� ���� ����. �ٸ�����
	//�׸��� ������ ���� �־�� ������ �������ִ�. ��ü�� ���µ� ������ ��� ����?!
	// 
	//�׸��� �����ʹ� �Ű������� &�� �پ �˱� ������ 
	//��������� �������̶� ����غ����� ������ �����ع����� ���� ���ֻ���� �ִ�... (�̰� �ִ����) �׷����̸��� ���� ������ָ� ����.
	//�Ǵ� ��Ģ�� ����� ����. ���� ���� �ٲܼ� ���� const�� ������ ��
	//const StateInfo& player �̷� ����� ��û ���� ���ٰ��Ѵ�.

	//PrintByRef(OUT player);
}