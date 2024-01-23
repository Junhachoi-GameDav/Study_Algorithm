#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "Monster.h"
#include "Missile.h"
#include "ObjectManager.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
	player->SetPos(Pos{ 400,400 });
	GET_SINGLE(ObjectManager)->Add(player);
}

void GameScene::Update()
{

	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();//²ø¾î¿Â´Ù¸é
	for (Object* obj : objects)
	{
		obj->Update();
	}

}

void GameScene::Render(HDC hdc)
{
	const vector<Object*>& objects = GET_SINGLE(ObjectManager)->GetObjects();//²ø¾î¿Â´Ù¸é
	for (Object* obj : objects)
	{
		obj->Render(hdc);
	}
}
