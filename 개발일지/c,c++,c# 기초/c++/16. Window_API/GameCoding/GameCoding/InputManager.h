#pragma once

enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar = VK_SPACE,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',

	Q = 'Q',
	E = 'E'
};

enum class KeyState
{
	NONE,
	PRESS,
	DOWN,
	UP,

	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::END)
};

class InputManager
{
	DECLARE_SINGLE(InputManager);

public:
	void Init(HWND hwnd);
	void Update();

	// ������ ���� ��
	bool GetButton(KeyType key) { return GetState(key) == KeyState::PRESS; }

	// �� ó�� ������ ��
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::DOWN; }

	// �� ó�� �����ٰ� �� ��
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::UP; }

	POINT GetMousePos() { return _mousePos; }

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }

private:
	HWND _hwnd = 0;
	vector<KeyState> _states;
	POINT _mousePos;
	//vector<
};

