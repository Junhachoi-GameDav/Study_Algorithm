#include "Helper.h"
#include <Windows.h>

MoveDir Gmove_dir;

void HandleKeyInput()
{
	//cin으로 입력은 받는것은 textrpg할때는 유용했어도 동적인
	//행동은 불가하다. 그래서 breaking 없는 함수를 사용한다.
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
	//마.소 에서 만들어준 기능들이다.
	//::은 외부 클라스안에 함수를 쓸때 사용하는데 글로벌이라는 의미도 있어서 강사분은 이렇게 한다고한다.
	//내가 만들지 않았다 = 외부 함수다 라는 의미
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x,(SHORT)y }; //short 말고 대문자 이다.
	::SetConsoleCursorPosition(output, pos);
}

void SetCursorOnOff(bool visible)
{
	//보통 이거 외울필요 없고 구글 검색해서 그냥 짜라고 한다.

	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = visible;
	::SetConsoleCursorInfo(output, &cursorInfo);
}
