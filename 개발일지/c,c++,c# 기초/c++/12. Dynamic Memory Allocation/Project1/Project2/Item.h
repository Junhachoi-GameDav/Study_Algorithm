#pragma once
#include "Enums.h"

// item

// Weapon
// Armor
// Consumable

// ******************************
//				item
// ******************************

//�θ� Ŭ�󽺷� ����ϰڴٸ� ���������� �����Լ��� �������Ѵ�.
class Item
{
protected:
	//Item();
	Item(ItemType itemType);
public:
	virtual ~Item();
	//�̰� ���� �ܰ� �����̶�� �Ѵ�.
	// �θ�Ŭ�� �Ҹ��ڿ� virtual �Ⱥ����� ����� �Ͼ����..


public:
	// �����Լ��� �ƴ϶�� ������ ������ ���� ���� �Լ���� �Ҽ��ִ�.
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
	//�̷������� �����Լ��� ����� cpp ���Ͽ��� Ÿ�Կ� ���缭
	//item:: printinfo() �� ����ɰ���

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
