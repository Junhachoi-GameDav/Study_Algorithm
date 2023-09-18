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
			//�̷��Ը� ���� ���� �˼���� �ſ� ������ �Լ�������
			// ���ǹ��� type�� �����ؼ� �����ϰ� �ٲ� ���.
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