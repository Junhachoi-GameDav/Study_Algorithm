// 이진 탐색 
// 배열 10개가 있다고 가정할때 특정 수를 찾을려면 모두 순회하면서 찾아야할까? ㄴㄴ

// 찾을수 = 8
// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 
// 여기서 중간지점을 집은후 8은 5보다 크니까 1~5는 날린다. 다시 반을 접고 ..접고 하는것이
// 이진 탐색이다. O(logN)

#include <iostream>
using namespace std;
#include <vector>
#include "BinarySearchTree.h"


vector<int> numbers;

//이진탐색은 배열특화하서 리스트에서는 못만든다.
// 배열은 연결되어있는데 리스트는 아니라서. 또 리스트는 임의 접근이 안되서
// 또한 수가 나열되어있어야하는 한계가 있따.
void BinarySearch(int n)
{
	int left = 0; //시작 배열 [0]
	int right = numbers.size() - 1; // 끝 배열

	while (left <= right)
	{
		cout << "탐색범위 : " << left << "~" << right << '\n';

		int mid = (left + right) / 2;

		if (n < numbers[mid])
		{
			cout << n << "<" << numbers[mid] << '\n';
			right = mid - 1; //오른쪽 범위지점 재설정
		}
		else if (n > numbers[mid])
		{
			cout << n << ">" << numbers[mid] << '\n';
			left = mid + 1; //왼쪽 범위지점 재설정
		}
		else //같다
		{
			cout << "찾음!" << '\n';
			break;
		}
	}
}

//이진 탐색			-> O(logN), 데이터 추가삭제 어려움
//이진 탐색 트리	-> 대소비교만함 (트리의 균형이 안맞음) 깊이가 짧아야 빠른데 깊이가 하나만 겁나 늘어남
//레드 블랙 트리	->
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