#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>

// hash_map = ���� ���ְ� ���� ����
// �޸𸮸� �ȾƼ� (cpu)������ ��ڴ�. �̷� ����

// �޸𸮰� �ſ� ũ�ٴ� �����Ͽ� �� �޸𸮿� �ø��� Ű���� �ٷ� ã�´ٴ� ����
// Ű�� �˸� ������ ã���� �ִ�. O(1)
// �׷��� �޸𸮴� �����ϴ�...


// hash��� �̶�?
// ���� 
// id = qwer7654 : pw = 1234
// pw -> hash(1234) = sfas878s78DFASD@_sdfa~~~~.... �̷�����
// �ܹ��� �˰����̴�. �� ������ �˰� hash�˰����� �˸� ������ �� �� �ڵ尡 �����ִµ�
// �� ���ڵ带 �ȴٰ��ؼ� ������ �˼��� ����...

// �����Ʈ���� �ؽ����̶� �Ѵ� �ո����� �����̴ϱ� �׳� �˾Ƽ� �ϰ������ ����
// �뷮�� ������ rbt �̰� ���� ã������� hash ����

/*
int main() {

	//hash_map
	unordered_map<int, int> um;


	// map �̶� ������ ����ϴ�.
	// ���ʿ� STL�� �ִ��Լ��� iterator ���п� �������̽��� ����ϴ�.
	// 
	//�߰�
	//ã��
	//����
	//��ȸ


	//�߰�
	um.insert(make_pair(10, 100));
	um[20] = 200;

	//ã��
	auto find_it = um.find(10);
	if (find_it != um.end())
	{
		cout << "ã��";
	}
	else
	{
		cout << "����";
	}

	//����
	um.erase(10);
	//um.erase(find_it);

	//��ȸ
	for (auto it = um.begin(); it != um.end(); it++)
	{
		int key = it->first;
		int value = it->second;
	}
}
*/