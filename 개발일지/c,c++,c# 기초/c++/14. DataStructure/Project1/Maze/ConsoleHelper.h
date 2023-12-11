#pragma once

//enum 뒤에 class 를 붙히면 같은 enum안에 변수 이름을 같게 해도 오류가 안남
// 거기다 int 에 넣을수 있던 기존 enum도 못넣게 해서 안전하게 관리할수있다.
enum ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE
};

class ConsoleHelper
{
public:
	static void SetCursorPosition(int32 x, int32 y); //커서 행 열 위치
	static void SetCursorColor(ConsoleColor color); //컬러
	static void ShowConsoleCursor(bool flag); // 마우스 커서 보이게 할건지
};

