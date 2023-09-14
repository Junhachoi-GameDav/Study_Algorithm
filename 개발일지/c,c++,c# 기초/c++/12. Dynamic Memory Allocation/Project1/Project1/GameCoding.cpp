#include <iostream>
using namespace std;


//스택
//메모리
//힙

class Monster {
public:
	Monster() { cout << "Monster" << endl; }
	~Monster() { cout << "~Monster" << endl; }

public:
	int _hp = 0;
};

class Player {
public:
	Monster* _target;
};

//이렇게 함수를 만든뒤
Player* FindPlayer(int id) {
	//todo

	return nullptr;
}

int main() {
	//malloc + free
	// c언어 에서 온 함수이다. 1000 byte 를 힙에 할당하라고 운영체제에게 명령
	// c언어 에서 온 것이라 이외의 특별한 기능이 없다 (생성자 밑 소멸자를 처리해 주지 않는다.)그래서 c++에서 바뀌어서 나온것이 밑에
	// new + delete

	//void* ptr = malloc(1000);

	//Monster* m = (Monster*)ptr;
	//m->_hp = 100; // 이런식

	//스택은 용량이 적고 위험한 구역이다. 그래서 안전하고 넓은 힙영역을 사용한다.
	// 하지만 힙의 단점은 모두 설정을 해주어야한다. 큰 힘에는 큰 대가가 따른다...

	//free(ptr); //이걸로 1000byte 이제 안쓰겠다고 선언


	//c++에서는 new + delete 방식만 쓰면 된다.
	//Monster* m1 = new Monster[5](); //동적(힙에) 할당하라고 명령 

	//m1->_hp = 100;

	//delete[](m1); //배열일때 delete도 배열로 없애줘야함
	////그런데 배열포인터는 사용할일이 거의 없다고한다.
	////c#은 GC가 자동으로 추적하여 delete가 된다.. 편한 대신에 이것이 중간중간 수거하는 비용을 쓰기위해 게임이 느려지는 것이다.


	////delete를 했는데 다시 선언한 상황일때 / 크래쉬? / 그냥된다?
	//m1->_hp = 200; // 오류는 안나지만 될때도 있고 안될떄도 있다. (케바케임)

	//왜 되는가= 일종의 휴지통이라고 보면된다. 진짜로 삭제하는게 아니고 임시로 휴지통에 넣었다가 나중에 한꺼번에 삭제하는것이다.
	//왜냐하면 운영체제한테 가서 계속 받았다가 삭제했다가하면 느리기 때문에.. 
	//이 역시도 아예 삭제할 수 있는 함수가 따로 존재한다. 

	//여기서 문제가 될수있는것은 안쓰겠다고 선언했고 거기에 다른 변수를 밀어 넣었으면 엉뚱한 값을 사용하게 되는것이다.
	// 이것을 막는 방법중에 하나


	//Monster* m1 = new Monster();

	//m1->_hp = 100;

	//delete m1;

	//m1 = nullptr; // 이런식으로 중간에 값을 0이나 nullptr 로 비워놓고 다시 값을 선언한다.

	//m1->_hp = 200;


	//# 케이스 2
	/*Monster* m1 = new Monster();
	m1->_hp = 100;

	Player* player = new Player();
	player->_target = m1;

	delete m1;
	m1 = nullptr;*/

	// 이렇게 m1 뿐만 아니라 player 에서 monster를 할당 했을때에는 m1을 0로 바꾸어도 player떄문에 문제가 생긴다.

	//메모리 오염과 관련된 버그는 찾기가 매매매매우우우우 어렵고 현직자들도 매우 조심하는 것이다. 
	//하나 잘못해서 몇년간 한 작업이 날라갈수도 있다..
	//그러니 처음부터 조심스럽게 섬세하게 코드를 짜야 한다.
	//이걸 해결할 방법중 하나는 위에 함수 하나를 만들어서 player가 null이면 nullptr을 반환하는 함수를 만드는것이다.

	Monster* m1 = new Monster();
	m1->_hp = 100;

	Player* player = FindPlayer(0);
	if (player != nullptr)// 이런식으로
	{

	}

	player->_target = m1;

	delete m1;
	m1 = nullptr;
}