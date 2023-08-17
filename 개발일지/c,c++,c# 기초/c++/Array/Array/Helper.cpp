#include "Helper.h"
#include <Windows.h>

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
