#include <iostream>
using namespace std;

void Swap(int* a, int* b) //매게변수가 포인터이니까 주소값을 받아야될것임.
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//응용
void Print(int* ptr, int count) // int &number[10] 
{

}



struct  StateInfo
{
	int hp;
	int attack;
	int defence;
};

StateInfo CreatePlayer() //이건 복사해서 나가는 형식이다. 이런 형식이 많아지면 나중에 메모리를 많이 잡아 먹을수 있다. 
{
	StateInfo info;

	cout << "플레이어 생성" << endl;

	info.hp = 100;
	info.attack = 10;
	info.defence = 1;

	return info;
}

/*
//이렇게 하면 크래쉬는 안나지만 제대로 작동은 안한다. 
StateInfo* CreatePlayer2()// 포인터는 주소값만 받는거다. 
{
	StateInfo info;  //이러면 안에서만 유효한 변수이고 이걸 호출할때 스택에서 없어지거나 어뚱한값을 받는다.

	cout << "플레이어 생성" << endl;

	info.hp = 100;
	info.attack = 10;
	info.defence = 1;

	return &info; //그걸 반환해서 아무것도 없는거임
}
*/

void CreateMonster(StateInfo* info) 
{
	cout << "몬스터 생성" << endl;

	info->hp = 40;
	info->attack = 8;
	info->defence = 1;
}

void Battle(StateInfo* player, StateInfo* monster)
{
	while (true)
	{
		int damage = player->attack - monster->defence;
		if (damage < 0) { damage = 0; }
		monster->hp -= damage;

		if (monster->hp < 0) { monster->hp = 0; }

		cout << "몬스터의 HP : " << monster->hp << endl;

		if (monster->hp == 0) { return; }


		damage = monster->attack - player->defence;
		if (damage < 0) { damage = 0; }
		player->hp -= damage;

		cout << "플레이어의 HP : " << player->hp << endl;

		player->hp -= damage;
		if (player->hp < 0) { player->hp = 0; }

		if (player->hp == 0) { return; }
	}
}

int main() {

	/*
	// 타입 * 이름 =~~;
	//포인터는 주소값을 담는 바구니 라고 생각하면된다.
	// 64비트 운영체제 기준을 따라 포인터 자료형은 모두 8바이트이다. 앞에 뭐가있든지간에...
	// &는 주소이고 *는 주소값을 담은 바구니이다. 즉 hp의 ㅜ소를 담고있다는 뜻
	// 사실상 (int*) ptr이라는 의미다. 즉 인트형의 포인터 라는 자료형이것.

	// 주소 값을 타고 가면 -> 무엇이 있는가?
	
	//int* ptr = &hp;

	//이중으로도 쓸수있다. 포인터를 가르키는 포인터이다. 즉 바구니의 바구니.
	//사실상 (int*)* pptr 이다. 인트형의 포인터의 포인터
	// 주소 -> 주소 -> int   양파까듯이 들어가면 쉽다.
	
	//int** pptr;


	//포인터의 장점 원본 자체를 수정할수 있기때문에 메모리를 아낄수가 있다. 
	// 원래 변수를 수정하는것이 아니라 복사하는 것이기에 스택상에서는 변수메모리는 그대로 가지고 있다.
	//즉 계속 복사만 하는것이다. 이때 포인터를 사용하면 하나의 메모리로만 수정이 이루어지니까 메모리 부하가 덜하다.

	//void* ptr = nullptr; //주소값을 0으로 둘때

	//이렇게 하면 
	//int a = 10; int b = 20;

	//Swap(&a, &b); //주소를 받음.

	// 이것을 역참조라고 한다. 주소를 담는 것이 아니라 담은 주소로 순간이동하라는 의미
	//// *ptr 은 주소를 타고 이동하라는 의미

	//cout << a << endl;
	//cout << b << endl;

	//포인터 연사자
	// - 주소 연산자 (&)
	// - 산술 연산자 (+-)
	// - 간접 연산자 (*)
	// - 간접 멤버 연산자 (->)

	//int* ptr = &hp;
	//ptr += 1; // hp에 정수 1이 더해질것 같지만 포인터 ptr의 다음 메모리 주소를 가리킨다. 즉 int 는 4바이트니까 104가 됨.
	// 왜이렇게 되어있는가 하면 배열을 쓸때 유용하라고 그런것

	//int number[10] = { 1,2,3,4,5,6 };

	//int* ptr = &number[0];
	//int* ptr = number; 이것도 된다. c++에선 배열의 이름만 쓰면 &number[0]로 본다.

	//*(ptr + 3) = 666; // index 4 번째 가 666으로 바뀜

	//ptr[3] 위에꺼가 이거라고 볼수도있는것



	// 포인터는 구조체나 클라스도 가르킬수 있다.

	//StateInfo monster;
	//monster.hp = 100;
	//monster.attack = 10;
	//monster.defence = 1;

	//StateInfo* ptr = &monster;

	//(*ptr).hp;
	//ptr->hp;    //둘다 똑같다.

	//.은 일반함수 였을때 쓰여지고 ->은 포인터로 되어있는 함수일때 사용됨
	*/

	//구조체를 활용해서 생성
	StateInfo player;
	player = CreatePlayer();

	//포인터를 활용한 생성
	StateInfo monster;
	CreateMonster(&monster);

	Battle(&player, &monster);
}