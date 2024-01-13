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
			//_hp �� ���������� ��ǻ� this->_hp �� �����ϴ°��̴�.'
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
//	//���� ���
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
//	//���� = �͸� �Լ� �Ǵ� ��ü
//	// [] () {} ���� ��Ʈ�� �׷��ְ� ����
//	// [] �Լ� () �Ű����� { ������ }
//
//	[/*ĸ�ĸ��*/](/*����*/)
//	{
//		//���빰
//	};
//
//	find_if(v.begin(), v.end(), [](Item& item) { return item._rarity == Rarity::Unique; });
//
//	auto is_unique_lambda = [=](Item& item) { return item._rarity == Rarity::Unique; };
//	find_if(v.begin(), v.end(),  is_unique_lambda);
//
//	//�䷱������ �ܹ߼� �Լ����� �ſ� ����
//
//	[](Item& item) -> int
//	{ 
//		return item._rarity == Rarity::Unique; // bool �������� �Ű����� ���� �������ָ� ������ ���´�.
//	};
//
//	//���� []�� �ΰ����� �������� �ִµ� (�̰��� ĸ�ĸ���� ��)
//	// [=] ������
//	// [&] �������
//	// �ϳ��� ������ �ϰ�ʹ�.
//	// [testcopy] ���� _�ƹ��͵� �Ⱥ����� �����̸������
//	// [&testref] ����
//
//	// �ڼ��� ������ ���ǿ���
//
//	//�������� ������ ��� ���� ���� ã���ֱ⶧���� ������ �ɼ��ִ�. �װͿ� �����ؾ���
//	// �׷��� ��δ� ����or������ �������� �ʴ´�.
//}