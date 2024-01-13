#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

enum class ItemType
{
	Nnon,
	Aamor,
	Weapon,
	Jewelry,
	Consumable
};

enum class Rarity
{
	Common,
	Rare,
	Unique
};

class Item
{
public:
	Item() {}
	Item(int itemId, Rarity rarity, ItemType type) : _itemId(itemId), _rarity(rarity), _type(type) {}

public:
	int _itemId = 0;
	Rarity _rarity = Rarity::Common;
	ItemType _type = ItemType::Nnon;
};

class Knight
{
public:
	auto MakeResetHpJob()
	{
		auto job = [=]()
		{
			//_hp 를 복사하지만 사실상 this->_hp 를 복사하는것이다.'
			_hp = 200;
		};
		return job;
	}
public:
	int _hp = 100;
};

//
//int main() {
//
//	//lambda
//	vector<Item> v;
//	v.push_back(Item(1, Rarity::Common, ItemType::Weapon));
//	v.push_back(Item(2, Rarity::Rare, ItemType::Aamor));
//	v.push_back(Item(3, Rarity::Unique, ItemType::Consumable));
//	v.push_back(Item(4, Rarity::Common, ItemType::Jewelry));
//
//
//
//	//기존 방식
//	struct IsUniqueItem
//	{
//		bool operator()(Item& item)
//		{
//			return item._rarity == Rarity::Unique;
//		}
//	};
//
//	//find_if(v.begin(), v.end(), IsUniqueItem());
//
//
//	//람다 = 익명 함수 또는 객체
//	// [] () {} 삼종 세트를 그려주고 시작
//	// [] 함수 () 매개변수 { 구현부 }
//
//	[/*캡쳐모드*/](/*인자*/)
//	{
//		//내용물
//	};
//
//	find_if(v.begin(), v.end(), [](Item& item) { return item._rarity == Rarity::Unique; });
//
//	auto is_unique_lambda = [=](Item& item) { return item._rarity == Rarity::Unique; };
//	find_if(v.begin(), v.end(),  is_unique_lambda);
//
//	//요런식으로 단발성 함수에선 매우 좋다
//
//	[](Item& item) -> int
//	{ 
//		return item._rarity == Rarity::Unique; // bool 값이지만 매개변수 옆에 설정해주면 딴값이 나온다.
//	};
//
//	//또한 []에 두가지를 넣을수가 있는데 (이것을 캡쳐모드라고 함)
//	// [=] 복사방식
//	// [&] 참조방식
//	// 하나의 변수만 하고싶다.
//	// [testcopy] 복사 _아무것도 안붙히고 변수이름쓰면됨
//	// [&testref] 참조
//
//	// 자세한 설명은 강의에서
//
//	//참조값이 날라갔을 경우 없는 값을 찾고있기때문에 문제가 될수있다. 그것에 유념해야함
//	// 그래서 모두다 복사or참조는 권장하지 않는다.
//}