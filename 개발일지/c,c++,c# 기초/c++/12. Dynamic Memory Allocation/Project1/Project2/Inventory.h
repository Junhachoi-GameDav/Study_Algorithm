#pragma once
#include "Item.h" //���� ����� �ƴϴ�.
//item�� ��� ��Ұ� ����Ǳ� ������

enum 
{
	MAX_SLOT = 100
};
class Inventory
{
public:
	Inventory();
	~Inventory();

	bool AddItem(Item* item); //�κ��丮 �ȿ��� �ϴ� �������� 
	bool RemoveItem(Item* item);
	Item* GetItemAtSlot(int slot);

	void Clear();

	// c++���� �ƹ����� static �Լ��� ������ �ִٴ°� ����ϴ°�
	// static�� ������������ ����� ������ �� Ȱ���Ұ�
	static Inventory* GetInventory();

private:
	int FindEmptySlot();
	int FindItemSlot(Item* item);

private:
	Item* _items[MAX_SLOT];
	int _itmesCount = 0;

	static Inventory* s_inventory;
};