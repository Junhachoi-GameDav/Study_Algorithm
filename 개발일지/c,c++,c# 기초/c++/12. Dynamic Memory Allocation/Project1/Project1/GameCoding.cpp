
#include <iostream>
using namespace std;

#pragma region  ���� �Ҵ�

//
////����
////�޸�
////��
//
//class Monster {
//public:
//	Monster() { cout << "Monster" << endl; }
//	~Monster() { cout << "~Monster" << endl; }
//
//public:
//	int _hp = 0;
//};
//
//class Player {
//public:
//	Monster* _target;
//};
//
////�̷��� �Լ��� �����
//Player* FindPlayer(int id) {
//	//todo
//
//	return nullptr;
//}
//
//int main() {
//	//malloc + free
//	// c��� ���� �� �Լ��̴�. 1000 byte �� ���� �Ҵ��϶�� �ü������ ���
//	// c��� ���� �� ���̶� �̿��� Ư���� ����� ���� (������ �� �Ҹ��ڸ� ó���� ���� �ʴ´�.)�׷��� c++���� �ٲ� ���°��� �ؿ�
//	// new + delete
//
//	//void* ptr = malloc(1000);
//
//	//Monster* m = (Monster*)ptr;
//	//m->_hp = 100; // �̷���
//
//	//������ �뷮�� ���� ������ �����̴�. �׷��� �����ϰ� ���� �������� ����Ѵ�.
//	// ������ ���� ������ ��� ������ ���־���Ѵ�. ū ������ ū �밡�� ������...
//
//	//free(ptr); //�̰ɷ� 1000byte ���� �Ⱦ��ڴٰ� ����
//
//
//	//c++������ new + delete ��ĸ� ���� �ȴ�.
//	//Monster* m1 = new Monster[5](); //����(����) �Ҵ��϶�� ��� 
//
//	//m1->_hp = 100;
//
//	//delete[](m1); //�迭�϶� delete�� �迭�� ���������
//	////�׷��� �迭�����ʹ� ��������� ���� ���ٰ��Ѵ�.
//	////c#�� GC�� �ڵ����� �����Ͽ� delete�� �ȴ�.. ���� ��ſ� �̰��� �߰��߰� �����ϴ� ����� �������� ������ �������� ���̴�.
//
//
//	////delete�� �ߴµ� �ٽ� ������ ��Ȳ�϶� / ũ����? / �׳ɵȴ�?
//	//m1->_hp = 200; // ������ �ȳ����� �ɶ��� �ְ� �ȵɋ��� �ִ�. (�ɹ�����)
//
//	//�� �Ǵ°�= ������ �������̶�� ����ȴ�. ��¥�� �����ϴ°� �ƴϰ� �ӽ÷� �����뿡 �־��ٰ� ���߿� �Ѳ����� �����ϴ°��̴�.
//	//�ֳ��ϸ� �ü������ ���� ��� �޾Ҵٰ� �����ߴٰ��ϸ� ������ ������.. 
//	//�� ���õ� �ƿ� ������ �� �ִ� �Լ��� ���� �����Ѵ�. 
//
//	//���⼭ ������ �ɼ��ִ°��� �Ⱦ��ڴٰ� �����߰� �ű⿡ �ٸ� ������ �о� �־����� ������ ���� ����ϰ� �Ǵ°��̴�.
//	// �̰��� ���� ����߿� �ϳ�
//
//
//	//Monster* m1 = new Monster();
//
//	//m1->_hp = 100;
//
//	//delete m1;
//
//	//m1 = nullptr; // �̷������� �߰��� ���� 0�̳� nullptr �� ������� �ٽ� ���� �����Ѵ�.
//
//	//m1->_hp = 200;
//
//
//	//# ���̽� 2
//	/*Monster* m1 = new Monster();
//	m1->_hp = 100;
//
//	Player* player = new Player();
//	player->_target = m1;
//
//	delete m1;
//	m1 = nullptr;*/
//
//	// �̷��� m1 �Ӹ� �ƴ϶� player ���� monster�� �Ҵ� ���������� m1�� 0�� �ٲپ player������ ������ �����.
//
//	//�޸� ������ ���õ� ���״� ã�Ⱑ �ŸŸŸſ���� ��ư� �����ڵ鵵 �ſ� �����ϴ� ���̴�. 
//	//�ϳ� �߸��ؼ� ��Ⱓ �� �۾��� ���󰥼��� �ִ�..
//	//�׷��� ó������ ���ɽ����� �����ϰ� �ڵ带 ¥�� �Ѵ�.
//	//�̰� �ذ��� ����� �ϳ��� ���� �Լ� �ϳ��� ���� player�� null�̸� nullptr�� ��ȯ�ϴ� �Լ��� ����°��̴�.
//
//	Monster* m1 = new Monster();
//	m1->_hp = 100;
//
//	Player* player = FindPlayer(0);
//	if (player != nullptr)// �̷�������
//	{
//
//	}
//
//	player->_target = m1;
//
//	delete m1;
//	m1 = nullptr;
//}
#pragma endregion

#pragma region �����Ҵ�
//class Player
//{
//public:
//};
//class Knight : public Player
//{
//public:
//	int hp;
//	int defence;
//};
//
//class Dog
//{
//public:
//	int age;
//	int size;
//};
//
//int main() {
//	// c ��Ÿ�� ĳ����
//
//#pragma region basic casting
//	//�� Ÿ�� ��ȯ
//	// Ư¡) �ǹ̸� �����ϱ� ���ؼ� ���� ��ü�� �ٸ� ��Ʈ�� �籸��
//	{
//		int a = 12345;
//		float b = (float)a;
//		//�̰��� c ��Ÿ�� ĳ�����̴�. �ٵ� �Ⱦ��°��� ����.
//		// �ɹ��ɷ� �ǹ̰� �޶��� ���� �ֱ� �����̴�.
//		// Ư�� �Ҽ��� float �� ������ �ٲܶ� �ٻ簪�� ���ϴ������� ����� �ٸ� ���̴�.
//	}
//
//	//���� Ÿ�� ��ȯ - ������ �ǹ̰� ������ �޶���
//	{
//		int a = 12345;
//		float b = (float&)a;
//	}
//
//	//������ ��ȯ(casting) (��ȯ�� 100% ���� �Ѱ�)
//	{
//		int a = 12345;
//		__int64 b = (__int64)a; // ��ū �ٱ����� ��
//	}
//	//�Ҿ����� ��ȯ(casting)
//	{
//		int a = 12345;
//		short c = (short)a; //���� �ٱ��Ͽ� ������ �翬�� �����Ͱ� �߸����ִ�.
//	}
//
//	// �Ͻ��� (������� �翬�� �����)
//	{
//		int a = 12345;
//		float b = a; //�̷������� �Ƚ�ִ°� (����) �����Ϸ��� �ڵ����� casting
//	}
//#pragma endregion
//
//	//�߿��� ���� �������� ĳ����~!
//
//	Knight* k = new Knight();
//	//Dog* dog = (Dog*)k;
//
//	//���� 
//	Dog* dog = (Dog*)k; //����Ʈ�� ���׷� ��ȯ?
//	dog->age = 10; //�̷��� ������ �ȳ��� ��¥ ã�� ��ƴ�...
//	//������ ���� �޸𸮸� ���� ������ �Ͼ��. 
//	//���� ����Ʈ���� ���� �� �뷮�� ũ�� �ʰ��� �κ��� �̻��Ѱ��� �޸𸮸� ���� ���� ���ɼ��� ũ��.
//
//	//�������� ĳ������ �޸𸮰� �ٲ��� �ʰ� �ּҸ� Ÿ������ ������ �ִ����� �����ϴ°� �ٲ�� ���̴�.
//}
#pragma endregion


#pragma region vartual �Ҹ���
//
//class Player
//{
//public:
//	Player()
//	{
//		cout << "Player()" << endl;
//
//	}
//
//	virtual ~Player()
//	{
//		cout << "~Player()" << endl;
//
//	}
//
//};
//
//class Pet
//{
//
//};
//
//class Archer : public Player
//{
//public:
//	Archer()//�����ڿ��� �� ����
//	{
//		_pet = new Pet();
//		cout << "Archer()" << endl;
//	}
//
//	virtual ~Archer()
//	{
//		cout << "~Archer()" << endl;
//		delete _pet;
//	}
//private:
//	Pet* _pet;
//
//};
//
//int main()
//{
//	//Archer* archer = new Archer();
//	Player* player = new Archer(); //�̷��� ������ �Ҹ��ڰ� ������ //�޸𸮰� �ᱹ ���ɰ���
//	//�θ�&�ڽ� �Ҹ��ڿ� virtual�� ������ ���氡�� 
//	// �����Լ��̸� �����ǰ� �Ǿ� ��� �ڽ�Ŭ�󽺸� ���İ��⶧���� �Ҹ��ڵ� ����ȴ�.
//
//	delete player;
//}

#pragma endregion


#pragma region ���� ���� & ���� ����
//
//class Pet
//{
//public:
//	Pet()
//	{
//		cout << "Pet()" << endl;
//	}
//	~Pet()
//	{
//		cout << "~Pet()" << endl;
//	}
//
//	Pet(const Pet& pet) { cout << "Pet(const Pet&)" << endl; }
//};
//
//class Knight
//{
//public:
//	Knight()
//	{
//		_pet = new Pet();
//	}
//	~Knight()
//	{
//		delete _pet;
//	}
//	Knight(const Knight& k)
//	{
//		_hp = k._hp;
//		//_pet = k._pet; //���� ����
//		_pet = new Pet(*(k._pet)); //���� �����Ҵ� ���� ���� Pet(const Pet&)�������� �����ϱ�
//		//�����ͷ� ����ȯ
//	}
//
//public:
//	int _hp = 100;
//	Pet* _pet;
//};
//
//
//int main()
//{
//	Knight k1;
//	k1._hp = 200;
//
//
//	Knight k2 = k1; //���� ����� 200 �����Ϸ��� �����ڷ� �����ؼ� ��������
//	// �̷��� k1�� �� hp�� pet* �� ����Ǿ� k2�� ���� pet�����͸� ����Ŵ
//	//�̰� ���� ���� �����
//
//
//	return 0;
//}
#pragma endregion

#pragma region ĳ���� 4�ѻ�
//������ ���ֳ���
//static_cast (�߿䵵)****
//dynamic_cast *****
//const_cast
//reinterpret_cast


class Player {
public:
	virtual ~Player() {};
};
class Knight : public Player {

};

class Dog
{

};
int main() {
	//static_cast  : Ÿ�� ��Ģ�� ���纼�� ������� ĳ���ø� ������ش�.
	// 1) int <-> float
	// 2) Player* -> Knight*

	int hp = 100;
	int maxHp = 200;

	//�Ѵ� ����
	float ratio = (float)hp / static_cast<float>(maxHp); //0~1

	Knight* k = new Knight();
	Player* p = k; // ����Ʈ�� �÷��̾��. �ڵ�

	//Knight* k2 = (Knight*)p;

	//���� : �������� �ʴ�.


	//dynamic_cast : ��� ���迡���� ������ ��ȯ
	// ���⼺ �ڵ尡 �־�� �� - �ϳ���(virtual)�� �־����
	// �����Լ��� ������ �ҷ����� ���̱� ������
	// RTTI (Runtime Type Information)
	// ĳ������ �ȵǸ� null =0 ���� �о ������ �����Ѵ�.
	Knight* k2 = dynamic_cast<Knight*>(p); // C# as ������ �̰Ŷ� ����.
	if (k2 != nullptr)
	{
		//��翴��?
	}

	//���� : ���� ������. �������Ӹ��� ���� ���ƾ� �Ѵ�.


	//const_cast : const�� ������ const���ϰ� ������ ���... �ƿ� �Ⱦ���.
	const char* name = "junha";
	char* name2 = const_cast<char*>(name); //�׳� const�� ����� �Ǵµ� ����...


	//reinterpret_cast : ������ -> ���� ������� �ٸ� Ÿ������ ��ȯ
	//�����ϰ�, ������ ����, ���� �Ⱦ�
	// re-interpret �ٽ� �����ϴ�

	//Dog* dog = (Dog*)k; 
	Dog* dog = reinterpret_cast<Dog*>(k); //���� ����. 

	__int64 address = reinterpret_cast<__int64>(k);

	return 0;
}

#pragma endregion
