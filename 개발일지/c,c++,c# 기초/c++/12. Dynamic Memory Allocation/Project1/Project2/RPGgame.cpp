#include <iostream>
#include "Item.h"
#include "Inventory.h"
using namespace std;

Item* DropItem() {

	if (rand() % 2 == 0) {
		Weapon* weapon = new Weapon();
		return weapon;
	}
	else {
		Armor* armor = new Armor();
		return armor;
	}
}

int main() {
	srand((unsigned)time(0));

	//몬스터 처치로 아이템 드랍
	for (int i = 0; i < 100; i++)
	{
		Item* item = DropItem();
		item->PrintInfo();

		if (Inventory::GetInventory()->AddItem(item))
		{
			cout << "Add item to inven" << endl;
		}
		else
		{
			cout << "Failed to add item" << endl;
			delete item;
		}
	}

	//pk당해서 아이템 드랍
	for (int i = 0; i < 20; i++)
	{
		int rand_index = rand() % MAX_SLOT;
		Item* item = Inventory::GetInventory()->GetItemAtSlot(rand_index);
		if (item && Inventory::GetInventory()->RemoveItem(item))
		{
			cout << "Remove the item" << endl;
		}
	}
}