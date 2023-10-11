#pragma once
#include "Enums.h"

// item

// Weapon
// Armor
// Consumable

// ******************************
//				item
// ******************************

//부모 클라스로 사용하겠다면 공식적으로 가상함수로 만들어야한다.
class Item
{
protected:
	//Item();
	Item(ItemType itemType);
public:
	virtual ~Item();
	//이거 면접 단골 질문이라고 한다.
	// 부모클라스 소멸자에 virtual 안붙히면 어떤일이 일어나는지..


public:
	// 가상함수가 아니라면 포인터 변수에 따라 정적 함수라고 할수있다.
	virtual void PrintInfo();
	ItemType GetItemType() { return _itemType; }

protected:
	int _itemId = 0;
	int _itemCound = 0;

	ItemRarity _rarity = IR_Normal;
	ItemType _itemType = IT_None;
};

// ******************************
//				weapon
// ******************************

class Weapon : public Item
{
public:
	Weapon();
	virtual ~Weapon();

	virtual void PrintInfo() override;
	//이런식으로 가상함수를 만들면 cpp 파일에서 타입에 맞춰서
	//item:: printinfo() 가 실행될거임

	void SetDamage(int damage) { _damage = damage; }
	int GetDamage() { return _damage; }

private:
	int _damage = 0;
};

// ******************************
//				armor
// ******************************

class Armor : public Item
{
public:
	Armor();
	virtual ~Armor();

	virtual void PrintInfo() override;

	void SetDefence(int defence) { _defence = defence; }
	int GetDefence() { return _defence; }

private:
	int _defence = 0;
};
