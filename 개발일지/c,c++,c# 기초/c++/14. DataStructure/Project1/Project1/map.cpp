// ����� Ʈ���� ������� ���� Ű�� ��� ���� ���� �Լ�
// vector �� list �� map�� ���� ���� ���ٰ� �Ѵ�.
// map �� set �� ���� ��Ʈ�ε� map���� �˸� �ȴ�.
// pair = pair<first, second> p; �ΰ��� �ϳ��� ������ ���ٴ� �����

#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <map>

//�÷��̾ �ִ� ����
class Player
{
public:
	Player() : _id(0) {}
	Player(int id) : _id(id) {}

	int _id;
};

//pair ���δ� �׳� �̷� ������
template<typename T, typename U>
struct Pair
{
	T first;
	U second;
};

template<typename T, typename U>
auto MakePair(T first, U second)
{
	return pair<T, U>(first, second);
}


// C++ vector	= C# List		�̰�
// C++ list		= C# LinkedList �̰�(�̰͵� ���� ������)
// C++ map		= ���� (dictionary�� �����)
// C++ hash_map	= C# Dictionary �̴�.
// hash_map�� ���� �̸� ������ unordered_map �̴�.

/*
int main() {
	vector<Player*> v;
	v.push_back(new Player(100));
	v.push_back(new Player(200));
	v.push_back(new Player(500));
	v.push_back(new Player(300));
	v.push_back(new Player(400));
	// �÷��̾ �ִ´� �����Ҷ� ���� �����ϱⰡ ��ƴ�
	// *�����ͷ� ������ 8��Ʈ�� �������ϱ� ���� �̷��� �Ѵ�. ��� ����<int>�� ���� �����ϱ�
	//����Ž���� �����Ͱ� ���� �Ǿ��־���ϴµ� �׷����ʴ�.


	//map (Ű, ���)
	map<int, Player*> m;

	// �߰�
	// ã��
	// ����
	// ��ȸ

	pair<int, Player*> p;

	//�߰�
	for (Player* p : v)
	{
		//int key = p->_id;
		//Player* data = p;
		//pair<int, Player*>(key, data)
		//make_pair(key, data); //���� ����ó�� ���ص� �� auto�� template�� �޺�
		m.insert(make_pair(p->_id, p));
	}

	//ã��
	auto it = m.find(300);
	//int key = (*it).first;
	//int key = it->first;
	//Player* player = (*it).second;
	//Player* player = it->second;
	if (it != m.end())
	{
		int key = it->first;
		Player* player = it->second;
		cout << "ã��";
	}
	else
	{
		cout << "����";
	}

	
	Player* p = m[100]; //100�� Ű�� ����� ������ �޶�� �� // ���� ���Ƽ� �̰� ���̾��ٰ���
	//�������� = m[1000]�� ���� ���� Ű���� �������� ���θ����...
	//c++���� ���� ����� ������ �ǵ�ġ���� Ű�� ������� �ִ�. ���� �̰� �̿��Ҽ��� ������...
	// �ٵ� �󸮾� TMap������ ������ ũ������ ��...
	// STL �Լ��� �𸮾� �Լ��� ����ѵ� �ٸ��͵� ���Ƽ� ������ ����ؾ��Ѵ�.


	//����
	//m.erase(it);
	m.erase(200);

	//��ȸ _���Ͱ� �� ����ϱ���. ���� ���ͷ� �迭������ �ϰ� map���� Ž���� ������
	for (auto it = m.begin(); it != m.end(); it++)
	{
		int key = it->first;
		Player* p = it->second;
	}
}
*/