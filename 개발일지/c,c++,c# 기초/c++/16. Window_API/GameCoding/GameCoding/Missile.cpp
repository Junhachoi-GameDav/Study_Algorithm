#include "pch.h"
#include "Missile.h"
#include"TimeManager.h"

Missile::Missile() : Object(ObjectType::Projectile)
{

}

Missile::~Missile()
{
}

void Missile::Init()
{
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void Missile::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_pos.y -= deltaTime * _stat.speed;

}

void Missile::Render(HDC hdc)
{
	Utils::DrowCircle(hdc, _pos, 25);
}
