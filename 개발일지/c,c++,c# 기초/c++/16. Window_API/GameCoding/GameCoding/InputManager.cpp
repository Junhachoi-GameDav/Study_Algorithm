#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::NONE);
}

//문서에 나와있는데로 ㄱㄱ
void InputManager::Update()
{
	BYTE asciKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciKeys) == false) { return; }

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		//키가 눌려있으면 TRUE
		if (asciKeys[key] & 0x80)
		{
			KeyState& state = _states[key];

			//이전 프레임에 키에 누른 상태라면 PRESS
			if (state == KeyState::PRESS || state == KeyState::DOWN)
				state = KeyState::PRESS;
			else
				state = KeyState::DOWN;
		}
		else //안눌려있다면(떗다면
		{
			KeyState& state = _states[key];

			//이전 프레임에 키를 누른 상태라면 UP
			if (state == KeyState::PRESS || state == KeyState::DOWN)
				state = KeyState::UP;
			else
				state = KeyState::NONE;
		}
	}

	//마우스
	::GetCursorPos(&_mousePos); //커서좌표를 알아옴
	::ScreenToClient(_hwnd, &_mousePos);
}
