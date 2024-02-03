#pragma once
#include "Scene.h"
class FortressScene : public Scene
{
public:
	FortressScene();
	virtual ~FortressScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual	void Render(HDC hdc) override;

	void ChangePlayerTure();

private:
	int32 _playerTurn = 1;// chage_p_t 함수땜시 1로 설정 
	float _sumTime = 0.f;
};

