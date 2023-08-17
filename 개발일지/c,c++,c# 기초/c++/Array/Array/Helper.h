#pragma once

enum MoveDir
{
	md_none,
	md_left,
	md_right,
	md_up,
	md_down,
};

void HandleKeyInput();
void SetCursorPosition(int x, int y);
void SetCursorOnOff(bool visible);

extern MoveDir Gmove_dir;