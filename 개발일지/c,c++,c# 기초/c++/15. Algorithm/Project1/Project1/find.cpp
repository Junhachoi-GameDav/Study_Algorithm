#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

/*
int main() {

	// STL 함수들이 몇백개가 있지만 그중에 10개정도만 쓴다.


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
		cout << "못찾음";
	}
	else {
		cout << "찾음";
	}

	//#2
	//특정하게 찾고싶다.
	// find_if

	//생성자를 넣으면됨( 클라스나 struct에 함수를 넣어서 특정한것을 찾음

	//람다식이랑 쓰면 엄청 좋다 (일단 나중에)
	struct Test
	{
		bool operator()(int n)
		{
			return n % 11 == 0;
		}
	};
	auto it = find_if(v.begin(), v.end(), Test());


	//#3
	// 홀수의 개수를 찾고싶다? (카운트)
	// count_if

	struct IsOdd
	{
		bool operator()(int n)
		{
			return n % 2 != 0;
		}
	};

	int a = count_if(v.begin(), v.end(), IsOdd());

	// 모든 데이터가 홀수인가?
	bool b1 = all_of(v.begin(), v.end(), IsOdd());
	// 홀수인 데이터가 하나라도 있는가?
	bool b1 = any_of(v.begin(), v.end(), IsOdd());
	// 모든 데이터가 홀수가 아닌가?
	bool b1 = none_of(v.begin(), v.end(), IsOdd());


	//#4
	// 모든 숫자들에 3을 곱하라
	// for_each

	struct MutiplyBy3
	{
		void operator()(int& n)
		{
			n *= 3;
		}
	};

	for_each(v.begin(), v.end(), MutiplyBy3()); //활용 빈도가 높다.

	//#5
	// 홀수인 데이터 모두 삭제
	// remove_if 이게좀 특이함

	// 기존의 백터를 그대로 쓰기때문에 날려버린 데이터에 남겨야할 데이터를 덮어씌움
	//예) 
	// - 1 2 3 4 5 6
	// - 2 4 6  (1 3 5)는 삭제
	// - 2 4 6 4 5 6
	
	//그래서 뒷부분을 삭제해주면 되는데 it가 마지막 수정 부분을 리턴함 즉

	auto it = remove_if(v.begin(), v.end(), IsOdd());
	v.erase(it, v.end());
	//v.erase(remove_if(v.begin(), v.end(), IsOdd()), v.end()); // 한 세트처럼 사용

}
*/