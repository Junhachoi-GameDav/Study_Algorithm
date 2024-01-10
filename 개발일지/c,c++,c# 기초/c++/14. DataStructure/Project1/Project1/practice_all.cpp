#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>

enum class ObjectType
{
	Plyer,
	Monster,
	Projectile,
	Env
};

class Object
{
public:
	Object(ObjectType type) : _type(type) {}

	virtual ~Object() {}

public:
	ObjectType GetObjectType() { return _type; }

	int _id = 0;
	ObjectType _type;
};

class Player : public Object
{
public:
	Player() : Object(ObjectType::Plyer) {}
	Player(int id) : Object(ObjectType::Plyer) {}
};
class Monster : public Object
{
public:
	Monster() : Object(ObjectType::Monster) {}
	int _id;
};

class Projectile : public Object
{
public:
	Projectile() : Object(ObjectType::Projectile) {}
	int _id;
};
//
//class Env : public Object
//{
//public:
//
//	int _id;
//};

class Field
{
public:
	static Field* GetInstance()
	{
		static Field field;
		return &field;
	}

	void Add(Player* player)
	{
		_objects.insert(make_pair(player->_id, player));
	}

	void Remove(int id)
	{
		_objects.erase(id);
	}

	Object* Get(int id)//플레이어가 있는지
	{
		auto find_it = _objects.find(id);
		if (find_it != _objects.end())
			return find_it->second; //밸류 = &Player

		return nullptr;
	}

private:
	//하나로 묶어도 되고
	unordered_map<int, Object*> _objects;

	//하나하나 관리해도 되고
	//unordered_map<int, Player*> _players;
	//unordered_map<int, Monster*> _monsters;
	//unordered_map<int, Projectile*> _projectiles;
	//unordered_map<int, Env*> _envs;
};

int main() {
	Field::GetInstance()->Add(new Player(1)); //1을 넣고

	//#방법 1
	Object* object = Field::GetInstance()->Get(1);
	if (object && object->GetObjectType() == ObjectType::Plyer)
	{
		Player* player = static_cast<Player*>(object);
	}

	//#방법 2
	//Object* object = Field::GetInstance()->Get(1); //1찾기->object로 넣기
	Player* player = dynamic_cast<Player*>(object); // 동적 캐스팅 할려면 가상함수가 있어야함
	if (player)
	{
		//~~
	}
	
}