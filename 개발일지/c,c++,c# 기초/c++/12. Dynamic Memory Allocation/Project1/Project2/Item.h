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

//�θ� Ŭ�󽺷� ����ϰڴٸ� ���������� �����Լ��� �������Ѵ�.
class Item
{
public:
	Item() {};
	virtual ~Item() {};
	//�̰� ���� �ܰ� �����̶�� �Ѵ�.
	// �θ�Ŭ�� �Ҹ��ڿ� virtual �Ⱥ����� ����� �Ͼ����..

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
