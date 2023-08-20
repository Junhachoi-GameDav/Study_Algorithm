#include <iostream>
using namespace std;

struct StateInfo
{
	int hp;
	int attack;
	int defence;
};

//값(복사) 전달 방식 = 기존의 방식들
void PrintByCopy(StateInfo player)
{
	cout << "----------" << endl;
	cout << "HP : " << player.hp << endl;
	cout << "ATT : " << player.attack << endl;
	cout << "DEF : " << player.defence << endl;
	cout << "----------" << endl;
}

//주소를 전달하는 방식 = 포인터
void PrintByPointer(StateInfo* player)
{
	cout << "----------" << endl;
	cout << "HP : " << player->hp << endl;
	cout << "ATT : " << player->attack << endl;
	cout << "DEF : " << player->defence << endl;
	cout << "----------" << endl;
}

//참조 전달 방식
void PrintByRef(const StateInfo& player) //매개변수에 &를 붙이면 주소가아니라 참조표시이다.
{
	cout << "----------" << endl;
	cout << "HP : " << player.hp << endl;
	cout << "ATT : " << player.attack << endl;
	cout << "DEF : " << player.defence << endl;
	cout << "----------" << endl;
}

//참조방식 응용
// #define IN
//인터페이스가 값을 읽기만 한다는 의미입니다.
//매개 변수가 값으로 전달되는 경우 함수가 작업을 수행할 로컬 변수를 가지므로 변수를 const로 전달하지 않아도 됩니다. 
//복사를 방지하려면 참조에 의한 전달이 선호되므로 변경을 방지하기 위해 const를 사용하는 것이 좋습니다.

// #define OUT
//매개변수가 out으로 표시되면 함수가 값을 읽을 필요가 없으며 매개변수 값이 중요하지 않음을 의미합니다. 
//실제로 표시된 매개변수는 여러 값을 출력하는 데 필요합니다. 
//이러한 매개변수는 포인터, 참조 및 구조여야 합니다.

// 이런 것도 있다 정도로 알자 정석은 const 이다.
//#define OUT
//void PrintByRef(OUT StateInfo& player) //매개변수에 &를 붙이면 주소가아니라 참조표시이다.
//{
//	cout << "----------" << endl;
//	cout << "HP : " << player.hp << endl;
//	cout << "ATT : " << player.attack << endl;
//	cout << "DEF : " << player.defence << endl;
//	cout << "----------" << endl;
//}

int main()
{
	StateInfo player = { 100, 10, 1 };
	PrintByCopy(player);

	//포인터를 사용하는 가장 큰이유
	//1. 원본을 건드리고싶을때(원격으로)
	//2. 복사비용 아낄때
	PrintByPointer(&player);


	//StateInfo* ptr = &player;
	//참조란 포인터처럼 주소를 가리키는 형태이다.
	//즉 ref를 건들면 *player도 건든다라는 느낌 말그대로 참조
	//StateInfo& ref = player;

	//ref.hp = 10; //원본수정은 된다. 하지만 포인터처럼 주소를 타고가서 원본을 건드는게 아니다.
	//즉 내부 원리는 포인터처럼 주소를 받았지만 사용하는 것은 복사된 변수 ref이고 원본값의 별명 같은거다...
	// 
	//즉 어떤 값의 =====닉네임====== 같은거다.

	//참조를 사용하는 이유는 =
	//복사방식은 안에있는 값들을 모두 복사한다.. 그렇기에 포인터를 사용하게 되는거지만
	//참조방식은 주소값만 복사한다.!!!!! 그러고 원본을 건드는 거라서 
	//두 장점을 모두 가져갈수있다.
	PrintByRef(player);


	//그러나 
	StateInfo* ptr = nullptr; //포인터는 nullptr 로 없다는 표시를 할수있다.
	//즉 원본에 없다는 표시를 할수있는 방법이 딱히 없다. 다른것은
	//그리고 무조건 값이 있어야 별명을 지을수있다. 물체가 없는데 별명을 어떻게 지음?!
	// 
	//그리고 포인터는 매개변수에 &가 붙어서 알기 쉽지만 
	//참조방식은 복사방식이랑 비슷해보여서 원본을 수정해버리는 일이 자주생길수 있다... (이게 최대단점) 그래서이름을 따로 명시해주면 좋다.
	//또는 규칙을 만들면 좋다. 값을 절대 바꿀수 없게 const를 붙히는 식
	//const StateInfo& player 이런 방식을 엄청 자주 쓴다고한다.

	//PrintByRef(OUT player);
}