
#include <iostream>
using namespace std;

#pragma region  동적 할당

//
////스택
////메모리
////힙
//
//class Monster {
//public:
//	Monster() { cout << "Monster" << endl; }
//	~Monster() { cout << "~Monster" << endl; }
//
//public:
//	int _hp = 0;
//};
//
//class Player {
//public:
//	Monster* _target;
//};
//
////이렇게 함수를 만든뒤
//Player* FindPlayer(int id) {
//	//todo
//
//	return nullptr;
//}
//
//int main() {
//	//malloc + free
//	// c언어 에서 온 함수이다. 1000 byte 를 힙에 할당하라고 운영체제에게 명령
//	// c언어 에서 온 것이라 이외의 특별한 기능이 없다 (생성자 밑 소멸자를 처리해 주지 않는다.)그래서 c++에서 바뀌어서 나온것이 밑에
//	// new + delete
//
//	//void* ptr = malloc(1000);
//
//	//Monster* m = (Monster*)ptr;
//	//m->_hp = 100; // 이런식
//
//	//스택은 용량이 적고 위험한 구역이다. 그래서 안전하고 넓은 힙영역을 사용한다.
//	// 하지만 힙의 단점은 모두 설정을 해주어야한다. 큰 힘에는 큰 대가가 따른다...
//
//	//free(ptr); //이걸로 1000byte 이제 안쓰겠다고 선언
//
//
//	//c++에서는 new + delete 방식만 쓰면 된다.
//	//Monster* m1 = new Monster[5](); //동적(힙에) 할당하라고 명령 
//
//	//m1->_hp = 100;
//
//	//delete[](m1); //배열일때 delete도 배열로 없애줘야함
//	////그런데 배열포인터는 사용할일이 거의 없다고한다.
//	////c#은 GC가 자동으로 추적하여 delete가 된다.. 편한 대신에 이것이 중간중간 수거하는 비용을 쓰기위해 게임이 느려지는 것이다.
//
//
//	////delete를 했는데 다시 선언한 상황일때 / 크래쉬? / 그냥된다?
//	//m1->_hp = 200; // 오류는 안나지만 될때도 있고 안될떄도 있다. (케바케임)
//
//	//왜 되는가= 일종의 휴지통이라고 보면된다. 진짜로 삭제하는게 아니고 임시로 휴지통에 넣었다가 나중에 한꺼번에 삭제하는것이다.
//	//왜냐하면 운영체제한테 가서 계속 받았다가 삭제했다가하면 느리기 때문에.. 
//	//이 역시도 아예 삭제할 수 있는 함수가 따로 존재한다. 
//
//	//여기서 문제가 될수있는것은 안쓰겠다고 선언했고 거기에 다른 변수를 밀어 넣었으면 엉뚱한 값을 사용하게 되는것이다.
//	// 이것을 막는 방법중에 하나
//
//
//	//Monster* m1 = new Monster();
//
//	//m1->_hp = 100;
//
//	//delete m1;
//
//	//m1 = nullptr; // 이런식으로 중간에 값을 0이나 nullptr 로 비워놓고 다시 값을 선언한다.
//
//	//m1->_hp = 200;
//
//
//	//# 케이스 2
//	/*Monster* m1 = new Monster();
//	m1->_hp = 100;
//
//	Player* player = new Player();
//	player->_target = m1;
//
//	delete m1;
//	m1 = nullptr;*/
//
//	// 이렇게 m1 뿐만 아니라 player 에서 monster를 할당 했을때에는 m1을 0로 바꾸어도 player떄문에 문제가 생긴다.
//
//	//메모리 오염과 관련된 버그는 찾기가 매매매매우우우우 어렵고 현직자들도 매우 조심하는 것이다. 
//	//하나 잘못해서 몇년간 한 작업이 날라갈수도 있다..
//	//그러니 처음부터 조심스럽게 섬세하게 코드를 짜야 한다.
//	//이걸 해결할 방법중 하나는 위에 함수 하나를 만들어서 player가 null이면 nullptr을 반환하는 함수를 만드는것이다.
//
//	Monster* m1 = new Monster();
//	m1->_hp = 100;
//
//	Player* player = FindPlayer(0);
//	if (player != nullptr)// 이런식으로
//	{
//
//	}
//
//	player->_target = m1;
//
//	delete m1;
//	m1 = nullptr;
//}
#pragma endregion

#pragma region 동적할당
//class Player
//{
//public:
//};
//class Knight : public Player
//{
//public:
//	int hp;
//	int defence;
//};
//
//class Dog
//{
//public:
//	int age;
//	int size;
//};
//
//int main() {
//	// c 스타일 캐스팅
//
//#pragma region basic casting
//	//값 타입 변환
//	// 특징) 의미를 유지하기 위해서 원본 객체와 다른 비트열 재구성
//	{
//		int a = 12345;
//		float b = (float)a;
//		//이것이 c 스타일 캐스팅이다. 근데 안쓰는것이 좋다.
//		// 케바케로 의미가 달라질 수가 있기 때문이다.
//		// 특히 소수점 float 를 정수로 바꿀때 근사값을 정하느것이지 사실은 다른 값이다.
//	}
//
//	//참조 타입 변환 - 위에랑 의미가 완전히 달라짐
//	{
//		int a = 12345;
//		float b = (float&)a;
//	}
//
//	//안전한 변환(casting) (변환시 100% 동일 한것)
//	{
//		int a = 12345;
//		__int64 b = (__int64)a; // 더큰 바구니일 뿐
//	}
//	//불안전한 변환(casting)
//	{
//		int a = 12345;
//		short c = (short)a; //작은 바구니에 담으면 당연히 데이터가 잘릴수있다.
//	}
//
//	// 암시적 (써놓으면 당연히 명시적)
//	{
//		int a = 12345;
//		float b = a; //이런식으로 안써넣는것 (생략) 컴파일러가 자동으로 casting
//	}
//#pragma endregion
//
//	//중요한 것은 포인터의 캐스팅~!
//
//	Knight* k = new Knight();
//	//Dog* dog = (Dog*)k;
//
//	//만약 
//	Dog* dog = (Dog*)k; //나이트를 도그로 변환?
//	dog->age = 10; //이러면 오류도 안나서 진짜 찾기 어렵다...
//	//엉뚱한 곳에 메모리를 적는 현상이 일어난다. 
//	//만약 나이트보다 개가 더 용량이 크면 초과한 부분은 이상한곳에 메모리를 적고 있을 가능성이 크다.
//
//	//포인터의 캐스팅은 메모리가 바뀌진 않고 주소를 타고갔을때 무엇이 있는지를 간주하는게 바뀌는 것이다.
//}
#pragma endregion


#pragma region vartual 소멸자
//
//class Player
//{
//public:
//	Player()
//	{
//		cout << "Player()" << endl;
//
//	}
//
//	virtual ~Player()
//	{
//		cout << "~Player()" << endl;
//
//	}
//
//};
//
//class Pet
//{
//
//};
//
//class Archer : public Player
//{
//public:
//	Archer()//생성자에서 펫 생성
//	{
//		_pet = new Pet();
//		cout << "Archer()" << endl;
//	}
//
//	virtual ~Archer()
//	{
//		cout << "~Archer()" << endl;
//		delete _pet;
//	}
//private:
//	Pet* _pet;
//
//};
//
//int main()
//{
//	//Archer* archer = new Archer();
//	Player* player = new Archer(); //이러면 아쳐의 소멸자가 누락됨 //메모리가 결국 고갈될것임
//	//부모&자식 소멸자에 virtual을 붙히면 예방가능 
//	// 가상함수이면 재정의가 되어 모든 자식클라스를 거쳐가기때문에 소멸자도 실행된다.
//
//	delete player;
//}

#pragma endregion


#pragma region 얕은 복사 & 깊은 복사
//
//class Pet
//{
//public:
//	Pet()
//	{
//		cout << "Pet()" << endl;
//	}
//	~Pet()
//	{
//		cout << "~Pet()" << endl;
//	}
//
//	Pet(const Pet& pet) { cout << "Pet(const Pet&)" << endl; }
//};
//
//class Knight
//{
//public:
//	Knight()
//	{
//		_pet = new Pet();
//	}
//	~Knight()
//	{
//		delete _pet;
//	}
//	Knight(const Knight& k)
//	{
//		_hp = k._hp;
//		//_pet = k._pet; //얕은 복사
//		_pet = new Pet(*(k._pet)); //새로 동적할당 한후 위에 Pet(const Pet&)참조값을 받으니까
//		//포인터로 형변환
//	}
//
//public:
//	int _hp = 100;
//	Pet* _pet;
//};
//
//
//int main()
//{
//	Knight k1;
//	k1._hp = 200;
//
//
//	Knight k2 = k1; //값이 복사됨 200 컴파일러가 생성자로 개입해서 넣은거임
//	// 이러면 k1의 값 hp와 pet* 이 복사되어 k2도 같은 pet포인터를 가리킴
//	//이건 얕은 복사 방식임
//
//
//	return 0;
//}
#pragma endregion

#pragma region 캐스팅 4총사
//면접에 자주나옴
//static_cast (중요도)****
//dynamic_cast *****
//const_cast
//reinterpret_cast


class Player {
public:
	virtual ~Player() {};
};
class Knight : public Player {

};

class Dog
{

};
int main() {
	//static_cast  : 타입 원칙에 비춰볼때 상식적인 캐스팅만 허용해준다.
	// 1) int <-> float
	// 2) Player* -> Knight*

	int hp = 100;
	int maxHp = 200;

	//둘다 같음
	float ratio = (float)hp / static_cast<float>(maxHp); //0~1

	Knight* k = new Knight();
	Player* p = k; // 나이트는 플레이어다. 자동

	//Knight* k2 = (Knight*)p;

	//단점 : 안전하진 않다.


	//dynamic_cast : 상속 관계에서의 안전한 변환
	// 다향성 코드가 있어야 함 - 하나라도(virtual)이 있어야함
	// 가상함수에 내용을 불러오는 것이기 때문임
	// RTTI (Runtime Type Information)
	// 캐스팅이 안되면 null =0 으로 밀어서 오류를 방지한다.
	Knight* k2 = dynamic_cast<Knight*>(p); // C# as 문법이 이거랑 같다.
	if (k2 != nullptr)
	{
		//기사였네?
	}

	//단점 : 조금 느리다. 매프레임마다 쓰진 말아야 한다.


	//const_cast : const된 변수를 const안하고 싶을때 사용... 아예 안쓴다.
	const char* name = "junha";
	char* name2 = const_cast<char*>(name); //그냥 const를 지우면 되는데 굳이...


	//reinterpret_cast : 포인터 -> 전혀 관계없는 다른 타입으로 변환
	//위험하고, 강력한 형태, 거의 안씀
	// re-interpret 다시 생각하다

	//Dog* dog = (Dog*)k; 
	Dog* dog = reinterpret_cast<Dog*>(k); //위랑 같다. 

	__int64 address = reinterpret_cast<__int64>(k);

	return 0;
}

#pragma endregion
