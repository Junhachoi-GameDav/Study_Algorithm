// ���� Ž�� 
// �迭 10���� �ִٰ� �����Ҷ� Ư�� ���� ã������ ��� ��ȸ�ϸ鼭 ã�ƾ��ұ�? ����

// ã���� = 8
// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 
// ���⼭ �߰������� ������ 8�� 5���� ũ�ϱ� 1~5�� ������. �ٽ� ���� ���� ..���� �ϴ°���
// ���� Ž���̴�. O(logN)

#include <iostream>
using namespace std;
#include <vector>
#include "BinarySearchTree.h"


vector<int> numbers;

//����Ž���� �迭Ưȭ�ϼ� ����Ʈ������ �������.
// �迭�� ����Ǿ��ִµ� ����Ʈ�� �ƴ϶�. �� ����Ʈ�� ���� ������ �ȵǼ�
// ���� ���� �����Ǿ��־���ϴ� �Ѱ谡 �ֵ�.
void BinarySearch(int n)
{
	int left = 0; //���� �迭 [0]
	int right = numbers.size() - 1; // �� �迭

	while (left <= right)
	{
		cout << "Ž������ : " << left << "~" << right << '\n';

		int mid = (left + right) / 2;

		if (n < numbers[mid])
		{
			cout << n << "<" << numbers[mid] << '\n';
			right = mid - 1; //������ �������� �缳��
		}
		else if (n > numbers[mid])
		{
			cout << n << ">" << numbers[mid] << '\n';
			left = mid + 1; //���� �������� �缳��
		}
		else //����
		{
			cout << "ã��!" << '\n';
			break;
		}
	}
}

//���� Ž��			-> O(logN), ������ �߰����� �����
//���� Ž�� Ʈ��	-> ��Һ񱳸��� (Ʈ���� ������ �ȸ���) ���̰� ª�ƾ� ������ ���̰� �ϳ��� �̳� �þ
//���� �� Ʈ��	->
//
//int main() {
//
//	/*numbers = { 1, 8, 15, 23, 32, 44, 56, 63, 81, 91 };
//	BinarySearch(81);*/
//
//	BinarySearchTree bst;
//	
//	bst.insert(20);
//	bst.insert(30);
//	bst.insert(10);
//
//	bst.insert(25);
//	bst.insert(26);
//	bst.insert(40);
//	bst.insert(50);
//
//	bst.Delete(26);
//
//	bst.Print();
//}