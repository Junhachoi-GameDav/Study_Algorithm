#include <iostream>
using namespace std;

// 이거 면접 질문 필수 요소이다.
//객체지향 (OOP)의 3 대 요소
// - 상속성 << inheritance
// - 은닉성 << data hiding (또는 캡슐화 encapsulation)
// - 다향성 << ploymorphism ( poly + morphism ) 다양 + 형체

//is-a vs has-a
//나이트는 플레이어다? 예스 is-a
//나이트는 플레이어를 가지고있다? no is-a(x) has-a


/* 상속
class Player
{
public:
	void move() { };
	void attack() { };
	void die() { };
public:
	int _hp;
	int _attack;
	int _defence;
};

class Knight : public Player
{
	int _dddd;
};
class Acher : public Player
{

};


void Fight(Player* k1, Player* k2)
{

}
*/

/*
 은닉(캡슐화)
 사용자가 몰라도 되는것등을 숨기거나 건들면 안되는것을 숨기는 역할
 (보안)접근 지정자 라고한다.
 public , private , protected
class Car 
{
	
public://공개(모두 사용가능)
	void Move(){}

private://비공개 ( 자신만 사용가능)
	void Engine(){}

protected://본인과 상속받은 클라스는 사용가능하다 란뜻
	void Test(){}
};


 상속 접근 지정자 = 자식한테 재산을 어떻게 물려줄지 결정
 public = 부모것을 모두 쓰겠다. 대부분 이것만 쓴다.
 protected = 자손만 물려주겠다. (public -> protected)
 private = 나까지만 꿀빤다. (public, protected -> private) 자식에 자식은 못씀
class SuperCar : private Car
{
public:
	void test()
	{
		Test();
	}
};

class UltraSuperCar : public SuperCar
{
public:
	void test()
	{
		Test(); 못씀
	}
};
class Knight
{
public:
	void SetHp(int _hp)
	{
		_hp = 40;
	}

	int GetHp()
	{ 
		return _hp;
	}

private:
	int _hp =100;
};

*/

//다형
// 가끔 면접에서 질문하는 내용이라한다.
//오버로딩(overloading) = 함수 이름을 재사용
//오버라이딩(overriding) = 재정의


//추상 클라스 = 순수 가상함수가 하나라도 있으면 추상클라스가 됨. 직접적으로 쓰진 않고 간접으로 쓰겠다는 얘기임
class Player 
{
public:
	//virtual void Move() { cout << " moving" << endl; }

	virtual void Move() = 0; //이것을 순수 가상함수라고 함 -- 빈 가상함수를 만들고 상속된 클라스에서 만들겠다는 뜻
	//virtual void Move() = abstract; // 이거는 위에랑 똑같음 옛날 버전

public:
	int _hp;
};

class Knight : public Player
{
public:
	virtual void Move() override { cout << " moving" << endl; }
	// 위에 virtual이 붙으면 사실상 여기에 virtual이 생략되어있다고 볼수있다. 헷갈리니까 그냥 둘다 써주면 좋다.
	// 실수로 부모에 virtual 없으면 overriding으로 검사할수 있다. c#과 다르게 함수 뒤에 붙는다.

	//추상 클라스를 상속받게 되면 반드시 가상함수를 만들어야 에러가 안난다.

};

// 바인딩(Binding) = 묶는다.
// - 정적 바인딩 (static binding = 컴파일 시점 결정) 일반적인 함수
// - 동적 바인딩 (dynamic binding = 실행 시점 결정)
void MovePlayer(Player* player)
{
	player->Move();
}

int main() {

	/*상속
	Knight k1;

	Acher a1;
	//Player p1 = k1; 이러면 데이터가 부모 클라스보다 모자라서 논리오류가 날것임
	//Player* p1 = &k1;
	//Knight* p2 = (Knight*)p1; 이게 위에 fight 함수 내용이라 볼수 있음

	Fight(&k1, &a1);
	*/

	/*은닉
	Knight k1;

	//k1._hp =100; 이렇게 하면 매우우 좋지않다.독단적인 코드라서 오늘만 산다 라는 코드임
	//get set 함수를 만들고 관리하면 굳굳
	k1.SetHp(100);
	*/

	//다형
	Knight k1;

	//k1.Move();
	MovePlayer(&k1);
	//virtual을 붙히면 메모리상에 다른 가상의 메모리 값(vftabale [주소1 | 주소2 | 주소3... ])을 가지게 되고 
	// 동적 바인딩이 일어나서 마지막에 결정된 값으로 결정된다.
	//그래서 사실상 메모리를 더잡고 있기 때문에 조금더 느리지만 크게 차이도 안나고 쓰면 이득될게 많아서 
	//안쓰면 손해
}