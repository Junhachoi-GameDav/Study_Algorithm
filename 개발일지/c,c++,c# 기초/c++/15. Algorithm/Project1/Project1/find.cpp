#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

/*
int main() {

	// STL �Լ����� ��鰳�� ������ ���߿� 10�������� ����.


	// find
	// find_if		<<
	// count_if		<<
	// all_of
	// ant_of
	// none_of		<<
	// for_each		<<
	// remove
	// remove_if	<<

	// find
	//#1
	vector<int> v{1, 2, 3, 4, 5};

	int fint_int = 50;
	auto it = find(v.begin(), v.end(), fint_int);
	if (it == v.end())
	{
		cout << "��ã��";
	}
	else {
		cout << "ã��";
	}

	//#2
	//Ư���ϰ� ã��ʹ�.
	// find_if

	//�����ڸ� �������( Ŭ�󽺳� struct�� �Լ��� �־ Ư���Ѱ��� ã��

	//���ٽ��̶� ���� ��û ���� (�ϴ� ���߿�)
	struct Test
	{
		bool operator()(int n)
		{
			return n % 11 == 0;
		}
	};
	auto it = find_if(v.begin(), v.end(), Test());


	//#3
	// Ȧ���� ������ ã��ʹ�? (ī��Ʈ)
	// count_if

	struct IsOdd
	{
		bool operator()(int n)
		{
			return n % 2 != 0;
		}
	};

	int a = count_if(v.begin(), v.end(), IsOdd());

	// ��� �����Ͱ� Ȧ���ΰ�?
	bool b1 = all_of(v.begin(), v.end(), IsOdd());
	// Ȧ���� �����Ͱ� �ϳ��� �ִ°�?
	bool b1 = any_of(v.begin(), v.end(), IsOdd());
	// ��� �����Ͱ� Ȧ���� �ƴѰ�?
	bool b1 = none_of(v.begin(), v.end(), IsOdd());


	//#4
	// ��� ���ڵ鿡 3�� ���϶�
	// for_each

	struct MutiplyBy3
	{
		void operator()(int& n)
		{
			n *= 3;
		}
	};

	for_each(v.begin(), v.end(), MutiplyBy3()); //Ȱ�� �󵵰� ����.

	//#5
	// Ȧ���� ������ ��� ����
	// remove_if �̰��� Ư����

	// ������ ���͸� �״�� ���⶧���� �������� �����Ϳ� ���ܾ��� �����͸� �����
	//��) 
	// - 1 2 3 4 5 6
	// - 2 4 6  (1 3 5)�� ����
	// - 2 4 6 4 5 6
	
	//�׷��� �޺κ��� �������ָ� �Ǵµ� it�� ������ ���� �κ��� ������ ��

	auto it = remove_if(v.begin(), v.end(), IsOdd());
	v.erase(it, v.end());
	//v.erase(remove_if(v.begin(), v.end(), IsOdd()), v.end()); // �� ��Ʈó�� ���

}
*/