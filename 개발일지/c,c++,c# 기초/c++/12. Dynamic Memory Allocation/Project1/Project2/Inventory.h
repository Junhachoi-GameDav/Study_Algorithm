#pragma once
//#include "Item.h" //좋은 방법은 아니다.
//item의 모든 요소가 복사되기 때문에

enum 
{
	MAX_SLOT = 100
};

class Item; //이것을 전방선언이라고 한다.
// 실질적인 내용은 없지만 미리선언해서 오류없이 넘기고
//cpp 파일에서 include "Item.h" 하는것이다.
//왜 이런 행동을 하는가? -> 인벤토리 함수를 사용하는 모든 함수는
//include "Item.h"를 포함해야한다. 그러면 용량 낭비이다.
//cpp에서 실질적인 코드를 사용하니까 item을 사용할 cpp파일에만
// include하는 것이다.~~~~!!!!!


//그래서 왠만하면 헤더에 헤더파일을 포함하지 않는것이 바람직


class Inventory
{
public:
	Inventory();
	~Inventory();

	bool AddItem(Item* item); //인벤토리 안에서 일단 만들기로함 
	bool RemoveItem(Item* item);
	Item* GetItemAtSlot(int slot);//포인터 타입으로 들고있어야함

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