#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>

// hash_map = 살을 내주고 뼈를 취함
// 메모리를 팔아서 (cpu)성능을 얻겠다. 이런 느낌

// 메모리가 매우 크다는 가정하에 다 메모리에 올리고 키값만 바로 찾는다는 느낌
// 키를 알면 빠르게 찾을수 있다. O(1)
// 그러나 메모리는 유한하다...


// hash기법 이란?
// 보안 
// id = qwer7654 : pw = 1234
// pw -> hash(1234) = sfas878s78DFASD@_sdfa~~~~.... 이런거임
// 단방향 알고리즘이다. 즉 원본을 알고 hash알고리즘을 알면 무조건 저 긴 코드가 나와주는데
// 저 긴코드를 안다고해서 원본을 알수는 없다...

// 레드블랙트리랑 해쉬맵이랑 둘다 합리적인 선택이니까 그냥 알아서 하고싶은거 쓰셈
// 용량이 적으면 rbt 이고 빨리 찾고싶은면 hash ㄱㄱ

/*
int main() {

	//hash_map
	unordered_map<int, int> um;


	// map 이랑 굉장히 비슷하다.
	// 애초에 STL에 있는함수는 iterator 덕분에 인터페이스가 비슷하다.
	// 
	//추가
	//찾기
	//삭제
	//순회


	//추가
	um.insert(make_pair(10, 100));
	um[20] = 200;

	//찾기
	auto find_it = um.find(10);
	if (find_it != um.end())
	{
		cout << "찾음";
	}
	else
	{
		cout << "없음";
	}

	//삭제
	um.erase(10);
	//um.erase(find_it);

	//순회
	for (auto it = um.begin(); it != um.end(); it++)
	{
		int key = it->first;
		int value = it->second;
	}
}
*/