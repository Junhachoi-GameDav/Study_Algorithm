#pragma once
class Player
{
public:
	//�ɹ� �Լ�
	void Attack();
	void Die();
	void HealMe(int value);

public:
	//�ɹ� ����
	int m_hp;
	int m_attack;
	int m_defence;
};
