#include <iostream>
#include "Item.h"
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

	for (int i = 0; i < 100; i++)
	{
		Item* item = DropItem();
		item->PrintInfo();

		ItemType itemType = item->GetItemType();
		if (itemType == IT_Weapon)
		{
			//이렇게만 쓰면 뭔지 알수없어서 매우 위험한 함수였지만
			// 조건문과 type을 지정해서 안전하게 바꿔 줬다.
			Weapon* weapon = (Weapon*)item;
			weapon->GetDamage();
		}
		else if (itemType == IT_Armor)
		{
			Armor* armor = (Armor*)item;
			armor->GetDefence();
		}
	}
}