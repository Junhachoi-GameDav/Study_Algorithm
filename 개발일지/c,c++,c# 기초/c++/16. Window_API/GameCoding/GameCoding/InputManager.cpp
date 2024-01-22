#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::NONE);
}

//������ �����ִµ��� ����
void InputManager::Update()
{
	BYTE asciKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciKeys) == false) { return; }

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		//Ű�� ���������� TRUE
		if (asciKeys[key] & 0x80)
		{
			KeyState& state = _states[key];

			//���� �����ӿ� Ű�� ���� ���¶�� PRESS
			if (state == KeyState::PRESS || state == KeyState::DOWN)
				state = KeyState::PRESS;
			else
				state = KeyState::DOWN;
		}
		else //�ȴ����ִٸ�(���ٸ�
		{
			KeyState& state = _states[key];

			//���� �����ӿ� Ű�� ���� ���¶�� UP
			if (state == KeyState::PRESS || state == KeyState::DOWN)
				state = KeyState::UP;
			else
				state = KeyState::NONE;
		}
	}

	//���콺
	::GetCursorPos(&_mousePos); //Ŀ����ǥ�� �˾ƿ�
	::ScreenToClient(_hwnd, &_mousePos);
}
