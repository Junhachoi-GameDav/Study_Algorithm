#include "pch.h"
#include "Vector.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player;

int main() {
	
	//���� ����
	
	//vector

	//����/����
	// - ����		o(n) ó���� ������ �ڿ� �̻���߻�
	// - �߰�		o(n) �߰��� ������ �ڿ� �̻���߻�
	// - ��			o(1) �ѹ����ϴϱ� = �ڿ� �о������ ������ �̻縦 ���ص� �ȴ�.
	// - ���� ����	o(1) �����ؼ� ���Ŷ� �ѹ��� �ϴϱ�

	//list
	
	//����/����
	// - ����		o(1) ����Ʈ Ư�������� ���� �����ʴ´�.
	// - �߰�		o(1) �̰��� ����� ����Ʈ ������ [1]<->[3] �̷������� ���ΰ� ����ִ��� �ƴ»�Ȳ���� o(1)�� ���̴�.
	// - ��			o(1) ����Ʈ Ư�������� ���� �����ʴ´�.
	// - ���� ����	o(n) index�� �����ؼ� ������� ����Ʈ�� ���� ���� count�� �ϸ� ���ϱ�


	::srand(static_cast<uint32>(time(nullptr)));

	//�ʱ�ȭ
	board.Init(25, &player);
	player.Init(&board);

	uint64 lastTick = 0;

	while (true)
	{
#pragma region ������ ����
		//::GetTickCount64() ������api �Լ����ϳ� ����� �ð��� ƽ(�и�����Ʈ ����)�� ȯ��
		const uint64 currntTick = ::GetTickCount64();
		const uint64 deltaTick = currntTick - lastTick; //������ �ð�
		lastTick = currntTick;
#pragma endregion


		//�Է�

		//���� (������Ʈ & ƽ �Լ� ������)
		player.Update(deltaTick);

		//������
		board.Render();
	}
}