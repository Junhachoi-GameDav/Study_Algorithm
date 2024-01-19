#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <windows.h>

//동적 계획법 (dynamic programming)
// 인공지능에서 많이 사용하는 알고리즘이라고 한다. 
// 했던 작업들이나 중복되는것을 막기위해 한번실행한것을 미리 캐싱하여(마치 오브젝트 풀링 같은 느낌임)
// 연산 속도를 동적으로 관리하는것이다.
// 엄청 복잡할것 같았지만 생각보다 쉽다... 알고리즘이 비슷비슷한것들이 많아서 그런듯



// 캐싱을 하는 방법을 메모이제이션(memoization) 이라고 한다.
//int cache[50][50];
//
//int Combination(int n, int r)
//{
//	//기저 사례
//	if (r == 0 || n == r)
//	{
//		return 1;
//	}
//
//	//이미 답을 구한적 있으면 바로 반환
//	int& ret = cache[n][r];
//	if (ret != -1)
//		return ret;
//
//	return ret = Combination(n - 1, r - 1) + Combination(n - 1, r);
//}


//test 예시
// 강화시 1+ 2+ 3+ 랜덤한 3개의 강화가 가능함
// 
// 9+ 까지의 경우의수 
int N = 9;
int cache[100] = { -1 };
int Enchant(int num)
{
	// 기저사례
	if (num > N)
		return 0;
	if (num == N)
		return 1;


	// 캐시
	int& ret = cache[num];
	if (ret != -1)
		return ret;

	// 적용
	return ret = Enchant(num + 1) + Enchant(num + 2) + Enchant(num + 3);
}


int main() {

	//memset(cache, -1, sizeof(cache)); // -1로 전부 밀어 넣겠다는 뜻

	//__int64 start = GetTickCount64(); //시간

	//int lotto = Combination(45, 6);

	//__int64 end = GetTickCount64();

	//cout << end - start << "ms";

	int ret = Enchant(0);
	cout << ret;

}