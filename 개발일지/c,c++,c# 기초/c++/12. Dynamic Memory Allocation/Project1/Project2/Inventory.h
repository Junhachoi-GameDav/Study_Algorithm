#pragma once
//#include "Item.h" //���� ����� �ƴϴ�.
//item�� ��� ��Ұ� ����Ǳ� ������

enum 
{
	MAX_SLOT = 100
};

class Item; //�̰��� ���漱���̶�� �Ѵ�.
// �������� ������ ������ �̸������ؼ� �������� �ѱ��
//cpp ���Ͽ��� include "Item.h" �ϴ°��̴�.
//�� �̷� �ൿ�� �ϴ°�? -> �κ��丮 �Լ��� ����ϴ� ��� �Լ���
//include "Item.h"�� �����ؾ��Ѵ�. �׷��� �뷮 �����̴�.
//cpp���� �������� �ڵ带 ����ϴϱ� item�� ����� cpp���Ͽ���
// include�ϴ� ���̴�.~~~~!!!!!


//�׷��� �ظ��ϸ� ����� ��������� �������� �ʴ°��� �ٶ���


class Inventory
{
public:
	Inventory();
	~Inventory();

	bool AddItem(Item* item); //�κ��丮 �ȿ��� �ϴ� �������� 
	bool RemoveItem(Item* item);
	Item* GetItemAtSlot(int slot);//������ Ÿ������ ����־����

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