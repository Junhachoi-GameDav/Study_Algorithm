#pragma once

// item

// Weapon
// Armor
// Consumable

enum ItemRarity
{
	IR_Normal,
	IR_Rare,
	IR_Unique,
	IR_None,
};

// ******************************
//				item
// ******************************

//부모 클라스로 사용하겠다면 공식적으로 가상함수로 만들어야한다.
class Item
{
public:
	Item() {};
	virtual ~Item() {};
	//이거 면접 단골 질문이라고 한다.
	// 부모클라스 소멸자에 virtual 안붙히면 어떤일이 일어나는지..

protected:
	int _itemId = 0;
	int _itemCound = 0;

	ItemRarity _rarity = IR_Normal;
};

// ******************************
//				weapon
// ******************************

class Weapon : public Item
{
public:
	Weapon() {};
	virtual ~Weapon() {};

	void SetDamage(int damage) { _damage = damage; }
	int GetDamage() { return _damage; }

private:
	int _damage = 0;
};

// ******************************
//				armor
// ******************************

class Armor : Item
{
public:
	Armor() {};
	virtual ~Armor() {};

	void SetDamage(int defence) { _defence = defence; }
	int GetDamage() { return _defence; }

private:
	int _defence = 0;
};
