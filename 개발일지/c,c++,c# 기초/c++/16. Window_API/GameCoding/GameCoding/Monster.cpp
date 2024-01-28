#include "pch.h"
#include "Monster.h"
#include "InputManager.h"

Monster::Monster() : Object(ObjectType::Monster)
{

}

Monster::~Monster()
{
}

void Monster::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 10;

	_pos = Pos{ 400,300 };

	_lookPos = Pos{ 400, 70 };
	_lookDir = _lookPos - _pos;
	_lookDir.Normalize();
}

void Monster::Update()
{
	
}

void Monster::Render(HDC hdc)
{
	Utils::DrowCircle(hdc, _pos, 100);

	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();
	

	//frontDir
	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldpen = (HPEN)::SelectObject(hdc, pen);

	Utils::DrowLine(hdc, _pos, _lookPos);
	
	::SelectObject(hdc, oldpen);
	::DeleteObject(pen);

}
