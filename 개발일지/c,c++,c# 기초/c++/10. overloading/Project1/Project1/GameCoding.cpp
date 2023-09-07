//객체지향

//연산자 오버로딩
// - 맴버 연산자 함수 버전
//  a op b 왼쪽 기준으로 오퍼레이터
// 
// 
// - 전역 연산자 함수 버전
//  a op b 의 형태라면, a/b 모두를 연산자 함수의 피연사자로 사용
// 즉 모두 다 넣겠다는 뜻


//클라스 + 클라스를 하게 해주는등 연산을 다채롭게 하고싶을때 쓴다.
// 연산자를 커마 할때 사용하지만 생각보다 쓸일이 없다.



#include<iostream>
using namespace std;

class Pos
{
public:

	Pos()
	{

	}

	//생성자와 대입자 중 뭐가 발동될까
	//파라미터가 하나짜리 생성자한테 explicit를 붙여주는게 정신건강에 좋다. 이게 종종 면접에서 나온다.
	explicit Pos(int b)
	{
		x = b;
		y = b;
	}

	Pos operator+(const Pos& b)
	{
		Pos	pos;
		pos.x = x + b.x;
		pos.y = y + b.y;
		return pos;
	}
	int x = 0;
	int y = 0;

	Pos operator+(int n)
	{
		Pos pos;
		pos.x = x + n;
		pos.y = y + n;
		return pos;
	}

	// 다른 타입도 가능하다.
	bool operator==(const Pos& b)
	{
		return x == b.x && y == b.y;
	}
	
	//대입 연산자
	void operator=(int b)
	{
		x = b;
		y = b;
	}
	
	//디테일
	// b= c= a; 이런식으로 꼬치터럼 연달아서 대입하고 싶을시 
	//자신 참조를 리턴해도 되고 &빼고 복사를 해도 되고 여러가지 가능
	/*Pos& operator=(int b)
	{
		x = b;
		y = b;
		return *this;
	}*/
};

//이렇게 전역 연산자로 빼주고 파라미터에 원하는 연산을 쓰면 됨
Pos operator+ (int a, const Pos & b)
{
	Pos pos;
	pos.x = a + b.x;
	pos.y = a + b.y;
	return pos;
}


void TestPos(Pos a)
{
	
}



int main() {
	int a = 10;
	int b = 10;
	int c = a + b;

	Pos pos1;
	Pos pos2;

	//Pos pos3 = pos1 + pos2;
	//Pos pos3 = pos1 + 10; // 인트 + 클라스는 안된다. a op b이기 때문에 이럴땐 전역 연산자 함수 버전을 사용한다.
	//pos3 = pos1.operator+(pos2); 위에꺼랑 똑같다.

	Pos pos3 = 10 + pos1;

	//중요한 포인트
	//선언과 동시에 대입 할시 생성자가 발동 된다. 즉
	//Pos pos1(10); 이거다.. 대입이 아니다.
	// 이게 안되야 정상이다.
	//Pos pos1 = 10;
	//Pos pos2 = 20;

	Pos pos1(10);
	Pos pos2(20);

	//하지만 선언이후에 대입할시 대입자이다.
	pos1 = 10; //대입 연사자 덕에 가능
	pos2 = 20;

	//TestPos(10); // 원래는 pos클라스를 받으라고 해놨는데 정수가 받아지는 이유는 정수를 받는 생성자를 클라스안에 만들어놔서 이걸 
	//컴파일러가 오케이 하고 넘겨버린다. 이럼 ㅈ 된다. 이걸 막기위해 explicit를 붙여주는 것이다.
}