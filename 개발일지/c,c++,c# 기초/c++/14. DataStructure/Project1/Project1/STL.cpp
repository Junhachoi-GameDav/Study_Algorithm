//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include "Vector.h"
#include <list>
#include <queue>
using namespace std;


//자료구조 또는 컨테이너라고 하며 stl과 같이 특정 헤더나 간단한 계산등을 미리 만들어 놓은 것이 stl이다.


void Test(vector<int> &v) //이렇게 하면 사실상 복사를 하는거다. test함수를 실행할때마다 복사될것임
{
	//& 참조값으로 넣으면 복사가 되지않고 한번만 쓰니까 이렇게 ㄱㄱ
	// vector는 보통 참조나 포인터를 대부분 사용하고 일반을 잘 안쓴다.
}

int main() {
	//vector
	{
		//vector<int> v{1, 2, 3, 4, 5};
		//stl 중에 제일 많이 쓰는 함수
		//size(resize) vector의 실제 데이터 크기
		//capacity (reserve) vector에서 할당된 공간 크기

		// 삽입/삭제
		// 시작 - O(N)
		// 중간 - O(N)
		// 끝	- O(1)
		// push_back(), front(), back()


		//v.push_back(10);	//o(1)

		//int a = v.front();	//o(1)
		//int b = v.back();	//o(1)

		//v.push_front() ?? 
		//이건 없다- 이유 = stl은 오래걸리거나 사용할필요없는등은 함수를 만들어 놓지 않는다.
		// 직접 만들어야 한다는 소리

		// 추가
		// 삭제
		// 순회
		// 검색

		//v.clear(); //전체삭제를 할경우 =정확히는 안에 데이터를 모두 pop_back() 즉 다 날린다고 보면됨
		//size = 줄어듬(실제크기니까
		//capacity = 안줄어듬 (공간은 그대로 있음)
		//capacity는 늘어나는것만 고려했지(이사비용때문에) 줄어드는것은 고려하지 않는다.
		// 굳이 줄일려면 빈 백터를 만들어서 swap()하면 되지만 그럴 필요가 전혀 없다. 아무도 이렇게 안함

	}
	
	//iterator
	{
		// iterator = 이터레이터 = 반복자 포인터
		// vector 뿐만 아니라 리스트 등등 stl에서 공통으로 들고있는 녀셕이다.
		//vector<int> v{1, 2, 3, 4, 5};

		//int* ptr = &v[0];	//1의 주소값 가르키는 ptr
		//int* ptrEnd = &v[4] + 1;

		//int value = *ptr;	//ptr이 가리키는 값 = 1

		//ptr++;		//다음 데이터
		//ptr += 2;	//다다음 데이터

		//일반 포인터랑 완전 똑같은데 쓰는이유는 다른 stl안에다 공통으로 있기때문에 앞에 이름만
		//바꿔도 그대로 쓸수있다.
		
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

		//좀더 좋음 코드. for문에 index가 아닌 iterator기반으로 만드는게 좋다
		//vector<int> v{1, 2, 3, 4, 5};

		//여기에 조건문넣어서 검색해도 되고
		//iterator를 밖으로 빼도 되고 알아서 하셈
		/*for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		{
			int data = *it;
			cout << data << endl;
		}*/

		//vector<int>::iterator it;
		//for (it = v.begin(); it != v.end(); it++)
		//{
		//	int data = *it;
		//	if (data == 3) { break; } //찾음
		//}
		//if (it != v.end()) //만약 끝까지 안돌았다.(찾았다)
		//{
		//	cout << "찾음" << endl;
		//	v.erase(it); //제거하는 함수 (iterator를 받는다. 제거후 한칸씩 밀려옴
		//}
		


		//vector<int> v{1, 2, 3, 4, 5};
		//
		//for (vector<int>::iterator it = v.begin(); it != v.end();)
		//{
		//	int value = *it;
		//	if (value % 2 == 0)
		//	{
		//		//v.erase(it); 그냥하면 오류가 난다. 인덱스 가 갱신이 안됐기 때문이다.
		//		// ** 순회하면서 제거하는 코드를 짤때 이런것들을 주의해야한다. **
		//		it = v.erase(it); 
		//	}
		//	else
		//	{
		//		// 위에 쓰면 갱신될때 생략되서 마지막 데이터를 삭제할때 인덱스 오류난다.
		//		it++;
		//	}
		//}
	}

	//만든 vector에서의 iterator
	{
		Vector<int> v;
		v.push_back(10);
		v.push_back(20);
		v.push_back(30);

		Vector<int>::iterator it;

		for (it = v.begin(); it != v.end(); it++)
		{
			int data = *it;
			cout << data << endl;
		}

		// it++;
		// v.begin();
		// v.end();
		// *it
		//이것들을 지원하게끔 만들어 주면 된다.
	}
}