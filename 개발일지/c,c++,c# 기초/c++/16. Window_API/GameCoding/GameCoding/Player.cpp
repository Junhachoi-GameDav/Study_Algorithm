#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"

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
		//_pos.y -= _stat.speed * deltaTime;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		//_pos.y += _stat.speed * deltaTime;
	}


	//포
	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{
		
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{
		
	}


	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		
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
		return L"MissileTank";

	return L"CanonTank";
}
