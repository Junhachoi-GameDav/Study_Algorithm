#pragma once
#include "Item.h" //좋은 방법은 아니다.
//item의 모든 요소가 복사되기 때문에

enum 
{
	MAX_SLOT = 100
};
class Inventory
{
public:
	Inventory();
	~Inventory();

	bool AddItem(Item* item); //인벤토리 안에서 일단 만들기로함 
	bool RemoveItem(Item* item);
	Item* GetItemAtSlot(int slot);

	void Clear();

	// c++에선 아무데나 static 함수를 넣을수 있다는것 기억하는가
	// static은 여러버전으로 만들수 있으니 잘 활용할것
	static Inventory* GetInventory();

private:
	int FindEmptySlot();
	int FindItemSlot(Item* item);

private:
	Item* _items[MAX_SLOT];
	int _itmesCount = 0;

	static Inventory* s_inventory;
};