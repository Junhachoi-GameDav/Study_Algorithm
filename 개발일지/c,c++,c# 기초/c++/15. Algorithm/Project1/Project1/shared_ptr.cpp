#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <algorithm>

//스마트 포인터는 3가지가 있다.
// - shared_ptr  99퍼 얘를 제일 많이씀
// - weak_ptr
// - unique_ptr
// 
//
//class ObjectManager
//{
//	//이런식으로 매니저 클라스를 전역(싱글톤)으로 만들고 
//	// 해쉬맵등으로 관리
//	Knight* GetObject(int id)
//	{
//		return nullptr;
//	}
//
//	unordered_map<int, Knight*> um;
//
//};

class Knight
{
public:
	~Knight() {};

	void Attack()
	{
		if (_target.expired() == false) //날라갔는지 아닌지 확인
			//_target->_hp -= _damage;
			shared_ptr<Knight> spr = _target.lock();// 이러면 카운트에 영향은 안주며서 포인터로 들고있는상황이됨
			//일종의 캐스팅 같은거 + 생 포인터 같은건데 생포인터보단 안전함 (대신 느리고 귀찮고 복잡해짐)
	}

public:
	int _hp = 100;
	int _damage = 10;


	//포인터로 관리하기보다 id를 만들어서 그것을 매니저에서 관리하게하는것도 방법임
	// 생포인터를 사용하는것은 사실 지양 해야함. 오류가 많이남 너무 옛날 방식임 그래서 스마트 포인터를 사용해야함
	//Knight* _target = nullptr;
	//int _targetId = 0;

	//shared_ptr<Knight> _target = nullptr; // 쉐어드 포인터를 사용하면 전부 이걸로 관리해야함 섞어쓰면 나중에 힘들어짐
	weak_ptr<Knight> _target; // 사이클 ㅁ문제를 보충하는 정도로 쓰지 독립적이게 쓸순 없다.(하루살이 weak)
	// weak 카운드가 따로 있어서 str 카운터에 영향을 주지않는다. 그래서 이걸로 센후에 위에 다시 캐스팅해서 숫자 세고 delete 하는것이다.
};

class RefCountBlock
{
public:
	//int _refCount = 1;
	atomic<int> _refCount = 1; //쓰레드 세이프하게 하려면 그냥 int는 안된다. 그러나 c++ shard_ptr은 이미 atomic으로 되어있어서 안전하다.
};

//atomic 을 사용하면 일반 int보다 계산이 느리다. 그래서 언리얼에선 본인만의 shared_ptr을 만들어서 사용한다.
//표준은 느리기 떄문에 그래서 사실 표준 shared_ptr을 안쓴다.

template<typename T>
class SharedPtr
{
public:
	SharedPtr(){}

	SharedPtr(T* ptr) : _ptr(ptr) 
	{
		if (ptr)//포인터가 있다면
		{
			_block = new RefCountBlock();
			cout << " ref count : " << _block->_refCount << '\n';
		}
	}

	//복사 생성자
	SharedPtr(const SharedPtr& other) : _ptr(other._ptr), _block(other._block)
	{
		if (_ptr)
		{
			_block->_refCount++;
		}
	}

	void operator=(const SharedPtr& other)
	{
		_ptr = other._ptr;
		_block = other._block;

		if (_ptr)
		{
			_block->_refCount++;
		}
	}


	~SharedPtr()
	{
		if (_ptr)
		{
			_block->_refCount--;

			if (_block->_refCount == 0) //아무도 사용하지 않는다
			{
				delete _ptr;
				delete _block;
			}
		}
	}

public:
	T* _ptr = nullptr;
	//int refCount = 1; //얼마나 사용하고있는지 개수
	RefCountBlock* _block = nullptr;
};

void Test(shared_ptr<Knight>& k) // 참조를 안붙히면 복사가 되서 count가 되지만 참조를 붙히면 수를 세지 않는다.
{
	//이런식으로 함수 매개변수에 스마트포인터 참조로 사용할수도있다. 그러나 위에 _target에 참조를 하는건 생포인터를 사용하는거랑
	//다를바가 없어서 위에는 사용하지마라.
	//k->_damage; //이런식으로 포인터랑 똑같히 사용할 수있다.
}

////일단 이건 스마트 포인터는 아니고 알면 좋은 팁정도?~
////래퍼라는 함수를 만든후 나이트를 여기에 넣어서 관리하다가 
//// 래퍼가 없어지면 알아서 나이트도 delete 시킴
//template<typename T>
//class Wrapper
//{
//public:
//	Wrapper(T* ptr) : _ptr(ptr) { }
//	~Wrapper()
//	{
//		if (_ptr)
//			delete _ptr;
//	}
//public:
//	T* _ptr;
//};
//
//int main() {
//	//Knight* knight = new Knight();
//	//Wrapper<Knight> w(new Knight());
//
//	//Knight* k1 = new Knight();
//	//Knight* k2 = new Knight();
//	//shared_ptr<Knight> k1(new Knight()); //래퍼함수에서 한것처럼 관리함
//	//shared_ptr<Knight> k2(new Knight());
//
//	//shared_ptr<Knight> k3;
//	//k3 = k1; //복사 이건 knight를 복사하는게 아니라 shaed_ptr을 복사하는거다.
//
//
//	//k1->_target = k2;
//
//	//delete k2;  //이러면 오류가남
//	//k1->Attack(); // k2를 찾을수가 없어서
//
//
//
//	shared_ptr<Knight> k1(new Knight());
//	shared_ptr<Knight> k2(new Knight());
//
//	//k1->_target = k2; //이제 지워져도 오류가 나진 않겠지... 그러나
//	// c#처럼 gc에서 관리하는 느낌이라고 보면된다. 아무도 사용하지 않을때 지워지는것이라
//	// 원할때 지울수 없다는 단점이 있다.
//
//	// 또한 억까인 상황이 있는데 바로 이거다.
//	k1->_target = k2;
//	k2->_target = k1;
//	//이런식으로 서로 물고있으면 메모리 릭이 일어남 언젠간
//	//방법은 그냥 하나를 null로 밀어주는 수밖에 없음
//	//k1->_target = nullptr; // count--;
//	//생각보다 찾기는 쉽다고한다. 그냥 사이클만 풀어주면 되니까
//
//	//이것을 해결해주는 방법이 있는데 바로 weak_ptr가 그러하다.
//
//
//	// unique_ptr 이것도한 단순하다.
//	// 복사 생성자 복사 대입연사자를 다 막아놓은 거랑 같다. 그것 외에는 일반 포인터랑 똑같음
//	unique_ptr<Knight> k(new Knight());
//
//	unique_ptr<Knight> k22 = move(k);
//	// 그러나 이동을 하면 사용가능함
//	// 근데 효율도 그렇고 쓸모가 없어서 거의 안쓴다.
//}