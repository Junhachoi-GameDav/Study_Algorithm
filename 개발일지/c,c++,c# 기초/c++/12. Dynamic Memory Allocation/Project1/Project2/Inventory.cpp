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

//�� ����� ������ ȿ������ ����� �ƴϴϱ� ����
bool Inventory::AddItem(Item* item)
{
	if (item == nullptr) { return false; }
	//���� ��ġ�� �� �������� Ư�� ���������� �̰� ���� �����̴�.

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

//���� ������ ����̶�� �Ѵ�.
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
