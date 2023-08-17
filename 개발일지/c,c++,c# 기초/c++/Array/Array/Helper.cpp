#include "Helper.h"
#include <Windows.h>

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
