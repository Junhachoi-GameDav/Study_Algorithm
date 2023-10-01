#include "Inventory.h"
#include "Item.h"

Inventory* Inventory::s_inventory = nullptr;

Inventory::Inventory()
{
	for (int i = 0; i < MAX_SLOT; i++)
	{
		_items[i] = nullptr;
	}
}

Inventory::~Inventory()
{

}

//이 방식은 쉽지만 효율적인 방식은 아니니까 참고
bool Inventory::AddItem(Item* item)
{
	if (item == nullptr) { return false; }
	//안전 장치는 꼭 마련하자 특히 서버에서는 이게 거의 공식이다.

	int emptySlot = FindEmptySlot();
	if (emptySlot < 0) { return false; }

	_items[emptySlot] = item;
	_itmesCount++;
	return true;
}

bool Inventory::RemoveItem(Item* item)
{
	if (item == nullptr)
		return false;

	int slot = FindItemSlot(item);
	if (slot < 0)
		return false;

	_items[slot] = nullptr;
	_itmesCount--;
	return true;
}

Item* Inventory::GetItemAtSlot(int slot)
{
	if (slot < 0 || slot >= MAX_SLOT)
		return nullptr;

	return _items[slot];
}

void Inventory::Clear()
{
	for (int i = 0; i < MAX_SLOT; i++)
	{
		if (_items[i])
		{ 
			delete _items[i];
			_items[i] = nullptr;
		}
	}
}

Inventory* Inventory::GetInventory()
{
	if (s_inventory == nullptr)
		s_inventory = new Inventory();

	return s_inventory;
}

//조금 무식한 방법이라고 한다.
int Inventory::FindEmptySlot()
{
	for (int i = 0; i < MAX_SLOT; i++)
	{
		if (_items[i] == nullptr) { return i; }
	}
	return -1;
}

int Inventory::FindItemSlot(Item* item)
{
	for (int i = 0; i < MAX_SLOT; i++)
	{
		if (_items[i] == item) { return i; }
	}
	return -1;
}
