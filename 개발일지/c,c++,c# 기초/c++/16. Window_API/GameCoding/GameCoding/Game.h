#pragma once
class Game
{
public:
	Game();
	~Game();
public:
	void Init(HWND hWnd);
	void Update();
	void Render();

private:
	HWND _hwnd = {};
	HDC _hdc = {};
};

