//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
//#include "Vector.h"
#include <list>
//#include "List.h"
#include <queue>
using namespace std;


//�ڷᱸ�� �Ǵ� �����̳ʶ�� �ϸ� stl�� ���� Ư�� ����� ������ ������ �̸� ����� ���� ���� stl�̴�.

struct ItemInfo_test
{
	//�ſ� ����� ��
};

void Test(vector<int> &v) //�̷��� �ϸ� ��ǻ� ���縦 �ϴ°Ŵ�. test�Լ��� �����Ҷ����� ����ɰ���
{
	//& ���������� ������ ���簡 �����ʰ� �ѹ��� ���ϱ� �̷��� ����
	// vector�� ���� ������ �����͸� ��κ� ����ϰ� �Ϲ��� �� �Ⱦ���.
}


int main() {
	//vector
	{
		//vector<int> v{1, 2, 3, 4, 5};
		//stl �߿� ���� ���� ���� �Լ�
		//size(resize) vector�� ���� ������ ũ��
		//capacity (reserve) vector���� �Ҵ�� ���� ũ��

		// ����/����
		// ���� - O(N)
		// �߰� - O(N)
		// ��	- O(1)
		// push_back(), front(), back()


		//v.push_back(10);	//o(1)

		//int a = v.front();	//o(1)
		//int b = v.back();	//o(1)

		//v.push_front() ?? 
		//�̰� ����- ���� = stl�� �����ɸ��ų� ������ʿ���µ��� �Լ��� ����� ���� �ʴ´�.
		// ���� ������ �Ѵٴ� �Ҹ�

		// �߰�
		// ����
		// ��ȸ
		// �˻�

		//v.clear(); //��ü������ �Ұ�� =��Ȯ���� �ȿ� �����͸� ��� pop_back() �� �� �����ٰ� �����
		//size = �پ��(����ũ��ϱ�
		//capacity = ���پ�� (������ �״�� ����)
		//capacity�� �þ�°͸� �������(�̻��붧����) �پ��°��� ������� �ʴ´�.
		// ���� ���Ϸ��� �� ���͸� ���� swap()�ϸ� ������ �׷� �ʿ䰡 ���� ����. �ƹ��� �̷��� ����

	}
	
	//iterator
	{
		// iterator = ���ͷ����� = �ݺ��� ������
		// vector �Ӹ� �ƴ϶� ����Ʈ ��� stl���� �������� ����ִ� ����̴�.
		//vector<int> v{1, 2, 3, 4, 5};

		//int* ptr = &v[0];	//1�� �ּҰ� ����Ű�� ptr
		//int* ptrEnd = &v[4] + 1;

		//int value = *ptr;	//ptr�� ����Ű�� �� = 1

		//ptr++;		//���� ������
		//ptr += 2;	//�ٴ��� ������

		//�Ϲ� �����Ͷ� ���� �Ȱ����� ���������� �ٸ� stl�ȿ��� �������� �ֱ⶧���� �տ� �̸���
		//�ٲ㵵 �״�� �����ִ�.
		
		/*
		list<int> v{1, 2, 3, 4, 5};
		list<int>::iterator it = v.begin();
		list<int>::iterator itEnd = v.end();*/

		/*vector<int> v{1, 2, 3, 4, 5};
		vector<int>::iterator it = v.begin();
		vector<int>::iterator itEnd = v.end();

		while (it != itEnd)
		{
			cout << *it << endl;
			it++;
		}*/

		//���� ���� �ڵ�. for���� index�� �ƴ� iterator������� ����°� ����
		//vector<int> v{1, 2, 3, 4, 5};

		//���⿡ ���ǹ��־ �˻��ص� �ǰ�
		//iterator�� ������ ���� �ǰ� �˾Ƽ� �ϼ�
		/*for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		{
			int data = *it;
			cout << data << endl;
		}*/

		//vector<int>::iterator it;
		//for (it = v.begin(); it != v.end(); it++)
		//{
		//	int data = *it;
		//	if (data == 3) { break; } //ã��
		//}
		//if (it != v.end()) //���� ������ �ȵ��Ҵ�.(ã�Ҵ�)
		//{
		//	cout << "ã��" << endl;
		//	v.erase(it); //�����ϴ� �Լ� (iterator�� �޴´�. ������ ��ĭ�� �з���
		//}
		


		//vector<int> v{1, 2, 3, 4, 5};
		//
		//for (vector<int>::iterator it = v.begin(); it != v.end();)
		//{
		//	int value = *it;
		//	if (value % 2 == 0)
		//	{
		//		//v.erase(it); �׳��ϸ� ������ ����. �ε��� �� ������ �ȵƱ� �����̴�.
		//		// ** ��ȸ�ϸ鼭 �����ϴ� �ڵ带 ©�� �̷��͵��� �����ؾ��Ѵ�. **
		//		it = v.erase(it); 
		//	}
		//	else
		//	{
		//		// ���� ���� ���ŵɶ� �����Ǽ� ������ �����͸� �����Ҷ� �ε��� ��������.
		//		it++;
		//	}
		//}
	}

	//���� vector������ iterator
	{
		/*Vector<int> v;
		v.push_back(10);
		v.push_back(20);
		v.push_back(30);

		Vector<int>::iterator it;

		for (it = v.begin(); it != v.end(); it++)
		{
			int data = *it;
			cout << data << endl;
		}*/

		// it++;
		// v.begin();
		// v.end();
		// *it
		//�̰͵��� �����ϰԲ� ����� �ָ� �ȴ�.
	}

	//list
	{
		//size (capacity�� ���� ��ü�� ����)
		// - ����		O(1)
		// - �߰�		O(1) << �ּҰ� ����� �Ǿ��ִٸ� 
		// - ��			O(1)
		// front
		// back
		// push_front (1���� �迭�� �����µ� �����ִ�.
		// push_back
		// ���� ���� (���� ����) x

		//�̷л����� O(1)�̶� ������ ������ ��带 Ÿ���� ������ ���ʿ� ��뵵���̵��
		//������.

		//list<int> li;

		//li.insert(li.end(), 1); //����
		//li.insert(li.end(), 2); //����
		//list<int>::iterator it = li.insert(li.end(), 3); //����
		//li.insert(li.end(), 4); //����
		//li.insert(li.end(), 5); //����

		//li.erase(it);

		/*List<int> li;
		li.AddAtTail(10);
		li.AddAtTail(20);
		li.AddAtTail(30);*/

		//list<int>::iterator it;
		/*for (List<int>::iterator it = li.begin(); it != li.end();)
		{
			int value = *it;
			if (value % 2 == 0)
				it = li.erase(it);
			else
				it++;
		}*/
		/*List<int>::iterator it;
		for (it = li.begin(); it != li.end(); it++)
		{
			int value = *it;
			cout << value << '\n';
		}*/
	}

	//auto
	{
		// c++11 (mordern c++) ���� �߰��� ��� ���ٽĵ� ����
		// ���� c++20���� �������� 11�� ��ݺ��̿��ٰ� �Ѵ�.

		//�տ� �� ���� ���������� c#�� var ��������
		//int a = 1;
		//auto a = 1;
		//template�� �Ѹ��� �����
		//���콺�� ���� ��� �����Ϸ��� ����?�� �ڷ������� �ٲ�� ����

		//int& ref = a;
		//const int cst = a;
		
		// ���� : auto�� const, &���� �� ���� �߷��� �̋� �׳� �����ָ��
		//auto& ref2 = ref;
		//const auto cst2 = cst;

		
		// ����:
		//  - Ÿ������ �������� vector<int>::itera ~~ �̰� �ϳ��ϳ� �������� �ʿ����
		// ����:
		//	- �������� �������� ���� ������ ã�� ����
		
		//vector<int> v;
		//auto it = v.begin(); // �������� �������� ������ �� �ᵵ �ȴ�.
		//iterator�� �ſ�� std::map<int, int>::iterator it = ~~ �̷��ſ� ���� ��
		// template�̶� ���� ���Ǿ�����. &���� ���� �� �����°Ϳ� ��������
	}

	//ranged-based for��
	{

		vector<int> v{1, 2, 3, 4, 5};
		
		//�Ϲ����� for��
		for (int i = 0; i < v.size(); i++)
		{
			int data = v[i];
			cout << data << '\n';
		}

		//auto�� ���� ����
		for (auto it = v.begin(); it != v.end(); it++)
		{
			int data = *it;
			cout << data << '\n';
		}

		//�ű� ���� c# foreach ������
		for (int data : v)
		{
			cout << data << '\n';
		}

		//�ȿ� �����͸� ��ġ������� & �������� ������ �ȴ�.
		vector<ItemInfo_test> item_v;
		for (auto& data : item_v)//�������� ��� ��ȸ�Ҷ� 
		{
			//& ������ �� ������ ��� ���簡 �Ͼ�� �޸� ��������
			// �Ϲ� �ڷ��� �ƴϰ��� �Ϲ������� & ������ �����ٰ� ���� ��
			// ���������� ��� iterator�� begin() �� end() ����� ����̶�� ���� ����
		}

		// �ѹ� ��ȸ(��ĵ)�Ҷ��� �ʹ� ������ �ȿ� ������ �Լ��� �ٸ� �Լ��� �̵��ϴ�
		// ������ ¥�� �޸� �����̳� �ǵ�ġ���� ������ �ɼ������� ����ϰ� 
		// ������ ���������� ����ؾ��Ѵ�.

	}
}
