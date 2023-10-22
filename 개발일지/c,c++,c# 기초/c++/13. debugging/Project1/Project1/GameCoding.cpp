#include <iostream>
using namespace std;


// Null 크래쉬 (95%)
#pragma region null 크러쉬

class Player
{
public:
	int _hp;
};

Player* FindPlayer(int id)
{
	//todo

	return nullptr;
}

void Test(Player* p)
{
	if (p == nullptr) //서버같은경우에 이런 조건문을 거의 공식처럼 넣는다.
	{
		return;
	}

	p->_hp = 10;
}

#pragma endregion

//정수 오버플로우 (0.001%) 거의 한번일어남
#pragma region 정수 오버플로우(언더플로우)

//
//int main() {
//
//	//Player* player = new Player();
//
//
//	short hp = 30000; //메모리를 초과하면 음수로 다시 돌아간다.
//
//	while (true) {
//		hp++;
//	}
//	return 0;
//}

#pragma endregion

//메모리 릭 (0.1%) 가끔

// 메모리 오염
//- 케스팅
//- 버퍼 오버플로우	= 배열 초과하거나 그런거
//- Use-After-Free


int main() {

	//Player* player = new Player();


	return 0;
}