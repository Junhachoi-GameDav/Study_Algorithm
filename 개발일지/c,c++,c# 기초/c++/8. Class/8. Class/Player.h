#pragma once
class Player
{
public:
	//¸É¹ö ÇÔ¼ö
	void Attack();
	void Die();
	void HealMe(int value);

public:
	//¸É¹ö º¯¼ö
	int m_hp;
	int m_attack;
	int m_defence;
};
