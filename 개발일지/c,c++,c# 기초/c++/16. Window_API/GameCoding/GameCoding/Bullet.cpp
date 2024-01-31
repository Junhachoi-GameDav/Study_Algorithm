#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "FortressScene.h"
#include "UIManager.h"

Bullet::Bullet() : Object(ObjectType::Projectile)
{

}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
}

void Bullet::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	//wind
	float windPercent = GET_SINGLE(UIManager)->GetWindPercent();
	_speed.x = 10 * deltaTime * windPercent;

	//gravity
	_speed.y += 1000 * deltaTime; //y가 뒤집혀있으니까 +해준다.

	//이동
	_pos += _speed * deltaTime;

	//충돌
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		if (object->GetObjectType() != ObjectType::Player)
			continue;

		if (object == _owner)
			continue;

		Vector dir = _pos - object->GetPos();
		if (dir.Length() < _radius + object->GetRadius())
		{
			FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
			if (scene)
				scene->ChangePlayerTure();

			GET_SINGLE(ObjectManager)->Remove(this);
			return;
		}
	}

	//소멸
	if (_pos.y > GWinSizeY * 1.5f || _pos.y < -GWinSizeY * 1.5f)
	{
		FortressScene* scene =dynamic_cast<FortressScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		if (scene)
			scene->ChangePlayerTure();

		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void Bullet::Render(HDC hdc)
{
	Utils::DrowCircle(hdc, _pos, static_cast<int32>(_radius));
}
