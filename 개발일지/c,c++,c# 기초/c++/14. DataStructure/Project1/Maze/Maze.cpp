#include "pch.h"
#include "Vector.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player;

int main() {
	
	//면접 질문
	
	//vector

	//삽입/삭제
	// - 시작		o(n) 처음에 넣으면 뒤에 이사비용발생
	// - 중간		o(n) 중간에 넣으면 뒤에 이사비용발생
	// - 끝			o(1) 한번만하니까 = 뒤에 밀어넣을게 없으니 이사를 안해도 된다.
	// - 임의 접근	o(1) 지정해서 고른거라서 한번만 하니까

	//list
	
	//삽입/삭제
	// - 시작		o(1) 리스트 특성때문에 굳이 밀지않는다.
	// - 중간		o(1) 이것은 양방향 리스트 였을시 [1]<->[3] 이런식으로 서로가 어디있는지 아는상황에서 o(1)인 것이다.
	// - 끝			o(1) 리스트 특성때문에 굳이 밀지않는다.
	// - 임의 접근	o(n) index를 지정해서 고랐지만 리스트는 선을 따라 count를 하며 가니까


	::srand(static_cast<uint32>(time(nullptr)));

	//초기화
	board.Init(25, &player);
	player.Init(&board);

	uint64 lastTick = 0;

	while (true)
	{
#pragma region 프레임 관리
		//::GetTickCount64() 윈도우api 함수중하나 경과된 시간을 틱(밀리세컨트 단위)로 환산
		const uint64 currntTick = ::GetTickCount64();
		const uint64 deltaTick = currntTick - lastTick; //사이의 시간
		lastTick = currntTick;
#pragma endregion


		//입력

		//로직 (업데이트 & 틱 함수 같은거)
		player.Update(deltaTick);

		//랜더링
		board.Render();
	}
}