#pragma once

//enum �ڿ� class �� ������ ���� enum�ȿ� ���� �̸��� ���� �ص� ������ �ȳ�
// �ű�� int �� ������ �ִ� ���� enum�� ���ְ� �ؼ� �����ϰ� �����Ҽ��ִ�.
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
	static void SetCursorPosition(int32 x, int32 y); //Ŀ�� �� �� ��ġ
	static void SetCursorColor(ConsoleColor color); //�÷�
	static void ShowConsoleCursor(bool flag); // ���콺 Ŀ�� ���̰� �Ұ���
};

