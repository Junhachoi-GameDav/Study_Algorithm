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

	Object* Get(int id)//�÷��̾ �ִ���
	{
		auto find_it = _objects.find(id);
		if (find_it != _objects.end())
			return find_it->second; //��� = &Player

		return nullptr;
	}

private:
	//�ϳ��� ��� �ǰ�
	unordered_map<int, Object*> _objects;

	//�ϳ��ϳ� �����ص� �ǰ�
	//unordered_map<int, Player*> _players;
	//unordered_map<int, Monster*> _monsters;
	//unordered_map<int, Projectile*> _projectiles;
	//unordered_map<int, Env*> _envs;
};

int main() {
	Field::GetInstance()->Add(new Player(1)); //1�� �ְ�

	//#��� 1
	Object* object = Field::GetInstance()->Get(1);
	if (object && object->GetObjectType() == ObjectType::Plyer)
	{
		Player* player = static_cast<Player*>(object);
	}

	//#��� 2
	//Object* object = Field::GetInstance()->Get(1); //1ã��->object�� �ֱ�
	Player* player = dynamic_cast<Player*>(object); // ���� ĳ���� �ҷ��� �����Լ��� �־����
	if (player)
	{
		//~~
	}
	
}