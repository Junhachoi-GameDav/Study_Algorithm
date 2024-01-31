#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"
#include "UIManager.h"
#include "Bullet.h"

Player::Player() : Object(ObjectType::Player)
{

}

Player::~Player()
{

}

void Player::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;
}

void Player::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_playerTurn == false) { return; }
	
	UpdateFireAngle();

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= _stat.speed * deltaTime;
		_dir = Dir::Left;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += _stat.speed * deltaTime;
		_dir = Dir::Right;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		//clamp 특정 범위 까지만 반환함 = 0 ~ 75
		_fireAngle = ::clamp(_fireAngle + 50 * deltaTime, 0.f, 75.f);

	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_fireAngle = ::clamp(_fireAngle - 50 * deltaTime, 0.f, 75.f);
	}


	//포
	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{
		
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{
		
	}


	if (GET_SINGLE(InputManager)->GetButton(KeyType::SpaceBar))
	{
		float percent = GET_SINGLE(UIManager)->GetPowerPercent();
		percent = min(100, percent + 100 * deltaTime);
		GET_SINGLE(UIManager)->SetPowerPercent(percent);
	}

	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::SpaceBar))
	{
		//
		_playerTurn = false;
		float percent = GET_SINGLE(UIManager)->GetPowerPercent();
		float speed = 10.f * percent;
		float angle = GET_SINGLE(UIManager)->GetBarrelAngle();

		Bullet* bullet = GET_SINGLE(ObjectManager)->CreateObject<Bullet>();
		bullet->SetOwner(this);
		bullet->SetPos(_pos);
		bullet->SetSpeed(Vector{speed * ::cos(angle * PI / 180), -1 * speed * ::sin(angle * PI /180)});
		GET_SINGLE(ObjectManager)->Add(bullet);
	}
}

void Player::Render(HDC hdc)
{
	if (_dir == Dir::Left)
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh)
		{
			mesh->Render(hdc, _pos, 0.5f, 0.5f);
		}
	}
	else
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
		if (mesh)
		{
			mesh->Render(hdc, _pos, -0.5f, 0.5f);
		}
	}

	//Utils::DrowCircle(hdc, _pos, 50);


	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldpen = (HPEN)::SelectObject(hdc, pen);

	//포신만 빨강으로
	//Utils::DrowLine(hdc, _pos, GetFirePos());
	::SelectObject(hdc, oldpen);
	::DeleteObject(pen);
}

wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::CanonTank)
		return L"CanonTank";

	return L"MissileTank";
}

void Player::UpdateFireAngle()
{
	if (_dir == Dir::Left)
	{
		GET_SINGLE(UIManager)->SetPlayerAngle(180);
		GET_SINGLE(UIManager)->SetBarrelAngle(180 - _fireAngle);
	}
	else
	{
		GET_SINGLE(UIManager)->SetPlayerAngle(0);
		GET_SINGLE(UIManager)->SetBarrelAngle(_fireAngle);
	}
}
