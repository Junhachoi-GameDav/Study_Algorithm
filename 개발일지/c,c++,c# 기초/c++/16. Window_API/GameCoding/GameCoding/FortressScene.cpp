#include "pch.h"
#include "FortressScene.h"
#include "UIManager.h"
#include "Player.h"
#include "LineMesh.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"

FortressScene::FortressScene()
{
}

FortressScene::~FortressScene()
{
}

void FortressScene::Init()
{
	GET_SINGLE(UIManager)->Init();
	
	
	{
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPlayerType(PlayerType::MissileTank);
		player->SetPlayerId(0);
		player->SetPlayerTurn(true);

		GET_SINGLE(ObjectManager)->Add(player);

		player->SetPos(Vector{ 100,400 });
	}
	
	{
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPlayerType(PlayerType::CanonTank);
		player->SetPlayerId(1);
		player->SetPlayerTurn(false);

		GET_SINGLE(ObjectManager)->Add(player);

		player->SetPos(Vector{ 700,400 });
	}

}

void FortressScene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (auto* obj : objects)
	{
		obj->Update();
	}

}

void FortressScene::Render(HDC hdc)
{
	GET_SINGLE(UIManager)->Render(hdc);

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (auto* obj : objects)
	{
		obj->Render(hdc);
	}
}
