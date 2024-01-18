#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

class Pet
{

};

class Knight
{
public:
	Knight() {};

	~Knight()
	{
		if (_pet) { delete _pet; }
	}

	//복사 생성자
	Knight(const Knight& knight)
	{

	}

	//복사 대입 연산자
	void operator=(const Knight& knight)
	{
		_hp = knight._hp;
		if (knight._pet)
			_pet = new Pet(*knight._pet); // 둘다 똑같은펫을 가리키면 하나가 소멸할때 못찾아서 에러남 
	}

	//이동 생성자
	Knight(Knight&& knight)
	{
		_hp = knight._hp;
		_pet = knight._pet;
		knight._pet = nullptr;
	}

	//이동 대입 연산자
	void operator=(Knight&& knight) //상대방의 자료를 다꺼내감
	{
		_hp = knight._hp;
		_pet = knight._pet; //복사가 아니라서 이렇게 써도 무방
		knight._pet = nullptr;
	}

public:
	int _hp = 0;
	Pet* _pet = nullptr;
};

void TestKnight_Copy(Knight knight)
{
	knight._hp = 100; //원본에 아무런 영향이 없음 복사된거라.
}

//원본을 넘겨줄테니... 건드려도됨
void TestKnight_LValue(Knight& knight)
{
	knight._hp = 100; //원본을 수정함
}

//원본을 넘겨줄테니...건드릴 순 없어
void TestKnight_ConstLValue(const Knight& knight)
{
	//knight._hp = 100;
}

//&&를 두개 찍으면 참조의 참조? 가 아니라 오른값 참조라는 새로운 문법이다..!!
//원본을 넘겨줄테니...더 이상 원본을 활용하지 않을 테니 맘대로 해
void TestKnight_RValueRef(Knight&& knight)
{
	knight._hp = 100; //수정가능 + 원본 이제 안씀
}
//
//int main() {
//	//c++11  rvalue_ref 오른값 참조
//
//	// l-value : 단일식을 넘어서 계속 지속되는 개체
//	// r-value : l-value가 아닌 나머지
//
//	int a = 3;
//	a = 10;
//	a = 5;  //a  :  l-value (왼값)
//	//나머지 3, 10, 5 가 오른값이다.
//
//
//	Knight k1;
//	k1._pet = new Pet();
//
//	Knight k2;
//
//	//k2 = static_cast<Knight&&>(k1); //k1을 더이상 사용하지 않을거니까 다 꺼내 써라 //위에는 빈 껍데기가 됨
//	k2 = move(k1); //둘다 똑같음 말그대로 이동이라는 느낌이긴 하지만 정확히는 rvalue_cast 라고 봐야한다.
//
//	//Knight k2 = k1; //복사 생성자가 개입
//	//Knight k2;
//	//k2 = k1; // 복사 대입 연산자가 개입
//
//	//TestKnight_Copy(k1);
//	// 임시객체(단일식이아닌) knight()를 넣으면
//	//TestKnight_LValue(Knight()); //const 가 없으면 왼쪽값만 받는다.
//	//TestKnight_ConstLValue(Knight());
//
//	//TestKnight_RValueRef(k1); //이러면 위에 원본은 사용중이거나 사용할거라 오류를 띄움 그러나..~~!!
//	//TestKnight_RValueRef(static_cast<Knight&&>(k1)); //이렇게 &&오른값으로 캐스팅 해버리면 됨..
//
//
//	//그래서 이걸 언제 쓰는가
//
//	//vector에서 배열을 다른 배열로 복사해서 붙여넣는건 효율이 안좋다.
//	// 작으면 큰 차이가 없지만 배열이나 함수가 엄청 그면 복사가 매우 힘들것이다. 그때 이동하는것
//	// 또는 소유권 이전 등 말그대로 이동해야 효율적일때 쓴다.
//	// 솔직히 게임같은거를 만들때는 많이 안쓴다. 하지만 라이브러리나 스크립트 엔지니어와 같이 아주 깊히 있는 코딩을 할때 많이 쓴다고한다.
//}