#include "Helper.h"
#include <Windows.h>

MoveDir Gmove_dir;

void HandleKeyInput()
{
	//cin���� �Է��� �޴°��� textrpg�Ҷ��� �����߾ ������
	//�ൿ�� �Ұ��ϴ�. �׷��� breaking ���� �Լ��� ����Ѵ�.
	if (::GetAsyncKeyState(VK_LEFT) & 0x8000)
		Gmove_dir = md_left;
	else if (::GetAsyncKeyState(VK_RIGHT) & 0x8000)
		Gmove_dir = md_right;
	else if (::GetAsyncKeyState(VK_UP) & 0x8000)
		Gmove_dir = md_up;
	else if (::GetAsyncKeyState(VK_DOWN) & 0x8000)
		Gmove_dir = md_down;
	else
		Gmove_dir = md_none;
}


void SetCursorPosition(int x, int y)
{
	//��.�� ���� ������� ��ɵ��̴�.
	//::�� �ܺ� Ŭ�󽺾ȿ� �Լ��� ���� ����ϴµ� �۷ι��̶�� �ǹ̵� �־ ������� �̷��� �Ѵٰ��Ѵ�.
	//���� ������ �ʾҴ� = �ܺ� �Լ��� ��� �ǹ�
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x,(SHORT)y }; //short ���� �빮�� �̴�.
	::SetConsoleCursorPosition(output, pos);
}

void SetCursorOnOff(bool visible)
{
	//���� �̰� �ܿ��ʿ� ���� ���� �˻��ؼ� �׳� ¥��� �Ѵ�.

	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = visible;
	::SetConsoleCursorInfo(output, &cursorInfo);
}
