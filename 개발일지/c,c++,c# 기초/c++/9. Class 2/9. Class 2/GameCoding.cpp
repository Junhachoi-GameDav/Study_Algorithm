
#include <iostream>
using namespace std;


// 맴버 변수 초기화
// 생성자와 소멸자


class Player
{
public:
	Player() 
	{
		cout << "Player()" << endl;
	};
	~Player()
	{
		cout << "~Player()" << endl;
	};
};


class Inventory
{
public:
	Inventory()
	{
		cout << "Inventory()" << endl;
	}
	Inventory(int a) //이렇게 만들었을시
	{
		_a = a;
		cout << "Inventory(int)" << endl;
	}
	~Inventory()
	{
		cout << "~Inventory()" << endl;
	}
public:
	int _a = 0;
};


class Knight : public Player
{
public:
	//Knight() : Knight(0)  생성자끼리도 호출할수도 있다.
	Knight() : _hp(0) , _inventory(100) , _hpRef(_hp) , _hpConst(_hp)
		//생성자 안에 넣는것보다 이렇게 옆에 두는게 순서와 효율측면에서 좋다.
	/*
	선처리 영역
	Player()
	_inventory = Inventory()
	*/
	{
		//_hp = 0;
		//_inventory = Inventory(100); 이렇게 안에넣으면 선처리 영역에서 두번이상 실행 하거나 쓰레기값을 넣을수가 있다. 
		cout << "Knight()" << endl;
	};
	~Knight() 
	{
		cout << "~Knight()" << endl;
	};

public:
	//int _hp = 100; // 또는 여기다가 초기화 해줘도 된다.
	// 여기에 초기화를 진행하면 모든 생성자에 호출될수있기때문에 생성자가 많으면 여기다 하는게 효율적이다.
	int _hp;


	//다만 참조 변수나 const 값은 위에서 호출해줘야 생성자 오류가 안난다.
	int& _hpRef;
	const int _hpConst;



	Inventory _inventory;
};


int main() {

	//int value
	// 인트같은 변수는 {} 안에 있든 밖에 놓든 성능상에 아무런 차이가 없다. 그냥 안에서 쓸거냐 전체에서 쓸거냐 정도 
	for (int i = 0; i < 10; i++)
	{
		int value = i;
		cout << value << endl;
	}

	// 하지만 생성자는 {} 안에넣었을때 마지막 } 에서 소멸자를 실행하기 때문에 다시 {}안에 똑같은 생성자가 실행되는게 아니라
	// 새로운 생성자를 실행하는 것과 같다. 
	// 이것이 성능 차이를 나오게 하는것이다.
	for (int i = 0; i < 10; i++)
	{
		Knight k1;//생성
		cout << k1._hp << endl;
	}//소멸 10번 반복


	Knight k2;//생성

	for (int i = 0; i < 10; i++)
	{
		cout << k2._hp << endl;
	}

}	//k2 소멸 (한번만)