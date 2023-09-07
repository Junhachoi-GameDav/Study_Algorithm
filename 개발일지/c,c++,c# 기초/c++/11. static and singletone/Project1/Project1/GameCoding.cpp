#include <iostream>
using namespace std;

// struct vs class

//c#에서는 두개의 차이가 매우크다. 
// struct은 무조건 복사 타입으로 동작하고 class는 무조건 참조 타입으로 동작함 
// 
// 
//c++ 은 두개가 거의 차이가 없다. 접근지정자 차이만 있다
//struct = public 이랑 class = prevaite 차이 - 안에 변수만 썼을시 기본으로 이렇게 됨.
// public 을 계속 붙히기 싫어서 struct을 사용하는 사람들도 있는데 매우 안좋은 습관이라고 한다.
//보통 struct는 여러가지 데이터를 모아서 관리하는 용도로 사용하고
//class는 객체지향 용도로 사용한다.



// static
// 밖에서 전역변수처럼 메모리 어딘가에서 관리가 된다.
// 더이상 marine 클라스에 들어있지 않고 따로 밖에 빠지게된다.
class Marine
{
public:
	void TakeDamage(int damage)
	{
		hp -= damage;
	}

	//이러면 이제 특정 클라스와 전혀 무관해진다. 즉 이 함수안에서 마린의 변수를 수정할수없다.
	//그냥전역 함수가 되버린 것이다.
	static void SetAttack(int value)
	{
		attack = value; //하지만 같은 static은 건드릴수 있다.
	}


public:
	int hp;
	static int attack; // 스태틱으로 선언하면 앞으로 나올것이라고 예고한 것이기때문에 대입이 안된다. 밑에다가 하면 된다.
	// 밖으로 빠졌기때문에 그런것 같다.
};

int Marine::attack = 6; //이제 모든 마린의 공격력은 6이다.
//이게 좋은 예시는 아니다 에초에 이런 states는 따로 빼서 관리하니까 어거지로 예를 든거다.



//예시 id를 개수로 관리하고 싶은데 전역 변수를 사용하면 지저분하니까 안에 static변수로 만든다.
class Player
{
public:
	Player()
	{
		id = s_idgenerator++;
	};
public:
	int id;
	static int s_idgenerator;
};

int Player::s_idgenerator = 1;

// 지역변수도 static을 선언하면 전역변수처럼(진짜 전역번수는 아님) 되버림



// 싱글톤
// 1개만 존재하고 모두 사용하는 것 

class UserManager
{
public:
	static UserManager* GetInstance() //본인을 static 변수로 선언한다.
	{
		static UserManager um;
		return &um;
	}

	//그후 정보를 담고~
public:
	void AddUser() { _userCount++; }
	int GetUserCount() { return _userCount; }
public:
	int _userCount = 0;
};


//저것마저도 길다~!!
//#define GET_MANAGER(UserManager::GetInstance()) // 이렇게 줄일수 있다.

int main() {
	/*Player player1;
	Player player2;
	Player player3;*/
	// 늘릴수록 count 해서 수를 늘림


	UserManager::GetInstance()->AddUser(); //이런식으로 어느 cpp파일에서든 불러와서 사용가능
	//GET_MANAGER->AddUser(); 이렇게 줄일수 있다.
}