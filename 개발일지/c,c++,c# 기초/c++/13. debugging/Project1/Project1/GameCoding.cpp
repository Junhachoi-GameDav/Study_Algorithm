#include <iostream>
using namespace std;


// Null ũ���� (95%)
#pragma region null ũ����

class Player
{
public:
	int _hp;
};

Player* FindPlayer(int id)
{
	//todo

	return nullptr;
}

void Test(Player* p)
{
	if (p == nullptr) //����������쿡 �̷� ���ǹ��� ���� ����ó�� �ִ´�.
	{
		return;
	}

	p->_hp = 10;
}

#pragma endregion

//���� �����÷ο� (0.001%) ���� �ѹ��Ͼ
#pragma region ���� �����÷ο�(����÷ο�)

//
//int main() {
//
//	//Player* player = new Player();
//
//
//	short hp = 30000; //�޸𸮸� �ʰ��ϸ� ������ �ٽ� ���ư���.
//
//	while (true) {
//		hp++;
//	}
//	return 0;
//}

#pragma endregion

//�޸� �� (0.1%) ����

// �޸� ����
//- �ɽ���
//- ���� �����÷ο�	= �迭 �ʰ��ϰų� �׷���
//- Use-After-Free


int main() {

	//Player* player = new Player();


	return 0;
}