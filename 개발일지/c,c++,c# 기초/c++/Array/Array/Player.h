#pragma once

void MovePlayer(int x, int y);
void HandleMove();

//외부에서 등장한다는 것을 선언 한것이기 때문에 값을 넣으면 안된다.
extern int Gplayer_X; 
extern int Gplayer_Y;
