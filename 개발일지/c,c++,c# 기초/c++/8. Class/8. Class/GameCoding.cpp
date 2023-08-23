/*
#include <iostream>
//#include "Player.h"
using namespace std;


// c#과 다르게 c++ 은 구조체와 클라스가 별차이 없다.

//클래스 == 설계도
class Knight
{
public:
	//초기값을 설정하는등에 일을 한다.
	// 안 만들시 컴파일러가 자동으로 만들어준다. 하지만 (기타든 모든)생성자를 만들시
	// 컴파가 안 만들어 준다. 
	//기본 생성자 (constuctor) //입장
	Knight()
	{
		m_hp = 0;
		m_attack = 0;
		m_defence = 0;
		cout << "knight()" << endl;
	}

	//복사 생성자
	Knight(const Knight& other)
	{
		this->m_hp = other.m_hp;
		this->m_attack = other.m_attack;
		this->m_defence = other.m_defence;
	}

	//기타(일반) 생성자
	Knight(int hp, int attack, int defence)
	{
		m_hp = hp;
		m_attack = attack;
		m_defence = defence;
		
		this->m_hp = hp;
		this->m_attack = attack;
		this->m_defence = defence;

		cout << "knight()" << endl;
	}

	//소멸자 (destructor) //퇴장 마지막에 실행됨
	//메모리관리 삭제 등의 일을 한다.
	~Knight()
	{
		cout << "~knight()" << endl;
	}

	//맴버 함수
	void Attack() { cout << "Attack" << endl; }
	void Die() { cout << "Die" << endl; }
	void HealMe(int value)
	{ 
		m_hp += 10;
	}

public:
	//맴버 변수
	int m_hp;
	int m_attack;
	int m_defence;
};

//클라스 안에 있는 변수들은 메모리(스택)영역에 들어가지만 함수는 코드 영역에 들어가기때문에(전역함수가 아니라서)
//결국 변수부분만 메모리를 써서 함수가 아무리많아도 변수가 적으면 용략이 적다고 할수있다.
//전역함수일때는 포인터로 원본에 접근했지만 클라스안에 함수가 있으면 어차피 내부안에서 건들기 때문에 포인터를 쓰지않아도 된것이다.
//보통은 헤더파일 만들고 보기좋게 관리한다.


int main() {
	Knight k1(100, 10 ,1); //기타 생성자

	Knight k2(k1); //복사 생성자 값만 복사해서 다른것에 넣을떄

	//Player k1; //생성자

	k1.m_hp = 100;

	k1.Attack();
	k1.Die();

	k1.HealMe(10);
}
*/