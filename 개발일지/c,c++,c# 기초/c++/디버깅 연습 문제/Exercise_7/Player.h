#pragma once



class Player
{
public:
	Player();
	Player(int hp);

	//부모 클라스의 소멸자에는 가상함수로 만들어야 나머지도 작동한다.
	virtual ~Player();

	void PrintInfo();

	void AddHp(int value);
	bool IsDead();

	int GetAttackDamage();

	void OnDamaged(Player* attacker);

public:

	int _hp;
	int _maxHp;
	int _attack;
};

