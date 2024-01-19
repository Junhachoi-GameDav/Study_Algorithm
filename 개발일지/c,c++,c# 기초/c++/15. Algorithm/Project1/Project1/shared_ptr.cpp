#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <algorithm>

//����Ʈ �����ʹ� 3������ �ִ�.
// - shared_ptr  99�� �긦 ���� ���̾�
// - weak_ptr
// - unique_ptr
// 
//
//class ObjectManager
//{
//	//�̷������� �Ŵ��� Ŭ�󽺸� ����(�̱���)���� ����� 
//	// �ؽ��ʵ����� ����
//	Knight* GetObject(int id)
//	{
//		return nullptr;
//	}
//
//	unordered_map<int, Knight*> um;
//
//};

class Knight
{
public:
	~Knight() {};

	void Attack()
	{
		if (_target.expired() == false) //���󰬴��� �ƴ��� Ȯ��
			//_target->_hp -= _damage;
			shared_ptr<Knight> spr = _target.lock();// �̷��� ī��Ʈ�� ������ ���ָ缭 �����ͷ� ����ִ»�Ȳ�̵�
			//������ ĳ���� ������ + �� ������ �����ǵ� �������ͺ��� ������ (��� ������ ������ ��������)
	}

public:
	int _hp = 100;
	int _damage = 10;


	//�����ͷ� �����ϱ⺸�� id�� ���� �װ��� �Ŵ������� �����ϰ��ϴ°͵� �����
	// �������͸� ����ϴ°��� ��� ���� �ؾ���. ������ ���̳� �ʹ� ���� ����� �׷��� ����Ʈ �����͸� ����ؾ���
	//Knight* _target = nullptr;
	//int _targetId = 0;

	//shared_ptr<Knight> _target = nullptr; // ����� �����͸� ����ϸ� ���� �̰ɷ� �����ؾ��� ����� ���߿� �������
	weak_ptr<Knight> _target; // ����Ŭ �������� �����ϴ� ������ ���� �������̰� ���� ����.(�Ϸ���� weak)
	// weak ī��尡 ���� �־ str ī���Ϳ� ������ �����ʴ´�. �׷��� �̰ɷ� ���Ŀ� ���� �ٽ� ĳ�����ؼ� ���� ���� delete �ϴ°��̴�.
};

class RefCountBlock
{
public:
	//int _refCount = 1;
	atomic<int> _refCount = 1; //������ �������ϰ� �Ϸ��� �׳� int�� �ȵȴ�. �׷��� c++ shard_ptr�� �̹� atomic���� �Ǿ��־ �����ϴ�.
};

//atomic �� ����ϸ� �Ϲ� int���� ����� ������. �׷��� �𸮾󿡼� ���θ��� shared_ptr�� ���� ����Ѵ�.
//ǥ���� ������ ������ �׷��� ��� ǥ�� shared_ptr�� �Ⱦ���.

template<typename T>
class SharedPtr
{
public:
	SharedPtr(){}

	SharedPtr(T* ptr) : _ptr(ptr) 
	{
		if (ptr)//�����Ͱ� �ִٸ�
		{
			_block = new RefCountBlock();
			cout << " ref count : " << _block->_refCount << '\n';
		}
	}

	//���� ������
	SharedPtr(const SharedPtr& other) : _ptr(other._ptr), _block(other._block)
	{
		if (_ptr)
		{
			_block->_refCount++;
		}
	}

	void operator=(const SharedPtr& other)
	{
		_ptr = other._ptr;
		_block = other._block;

		if (_ptr)
		{
			_block->_refCount++;
		}
	}


	~SharedPtr()
	{
		if (_ptr)
		{
			_block->_refCount--;

			if (_block->_refCount == 0) //�ƹ��� ������� �ʴ´�
			{
				delete _ptr;
				delete _block;
			}
		}
	}

public:
	T* _ptr = nullptr;
	//int refCount = 1; //�󸶳� ����ϰ��ִ��� ����
	RefCountBlock* _block = nullptr;
};

void Test(shared_ptr<Knight>& k) // ������ �Ⱥ����� ���簡 �Ǽ� count�� ������ ������ ������ ���� ���� �ʴ´�.
{
	//�̷������� �Լ� �Ű������� ����Ʈ������ ������ ����Ҽ����ִ�. �׷��� ���� _target�� ������ �ϴ°� �������͸� ����ϴ°Ŷ�
	//�ٸ��ٰ� ��� ������ �����������.
	//k->_damage; //�̷������� �����Ͷ� �Ȱ��� ����� ���ִ�.
}

////�ϴ� �̰� ����Ʈ �����ʹ� �ƴϰ� �˸� ���� ������?~
////���۶�� �Լ��� ������ ����Ʈ�� ���⿡ �־ �����ϴٰ� 
//// ���۰� �������� �˾Ƽ� ����Ʈ�� delete ��Ŵ
//template<typename T>
//class Wrapper
//{
//public:
//	Wrapper(T* ptr) : _ptr(ptr) { }
//	~Wrapper()
//	{
//		if (_ptr)
//			delete _ptr;
//	}
//public:
//	T* _ptr;
//};
//
//int main() {
//	//Knight* knight = new Knight();
//	//Wrapper<Knight> w(new Knight());
//
//	//Knight* k1 = new Knight();
//	//Knight* k2 = new Knight();
//	//shared_ptr<Knight> k1(new Knight()); //�����Լ����� �Ѱ�ó�� ������
//	//shared_ptr<Knight> k2(new Knight());
//
//	//shared_ptr<Knight> k3;
//	//k3 = k1; //���� �̰� knight�� �����ϴ°� �ƴ϶� shaed_ptr�� �����ϴ°Ŵ�.
//
//
//	//k1->_target = k2;
//
//	//delete k2;  //�̷��� ��������
//	//k1->Attack(); // k2�� ã������ ���
//
//
//
//	shared_ptr<Knight> k1(new Knight());
//	shared_ptr<Knight> k2(new Knight());
//
//	//k1->_target = k2; //���� �������� ������ ���� �ʰ���... �׷���
//	// c#ó�� gc���� �����ϴ� �����̶�� ����ȴ�. �ƹ��� ������� ������ �������°��̶�
//	// ���Ҷ� ����� ���ٴ� ������ �ִ�.
//
//	// ���� ����� ��Ȳ�� �ִµ� �ٷ� �̰Ŵ�.
//	k1->_target = k2;
//	k2->_target = k1;
//	//�̷������� ���� ���������� �޸� ���� �Ͼ ������
//	//����� �׳� �ϳ��� null�� �о��ִ� ���ۿ� ����
//	//k1->_target = nullptr; // count--;
//	//�������� ã��� ���ٰ��Ѵ�. �׳� ����Ŭ�� Ǯ���ָ� �Ǵϱ�
//
//	//�̰��� �ذ����ִ� ����� �ִµ� �ٷ� weak_ptr�� �׷��ϴ�.
//
//
//	// unique_ptr �̰͵��� �ܼ��ϴ�.
//	// ���� ������ ���� ���Կ����ڸ� �� ���Ƴ��� �Ŷ� ����. �װ� �ܿ��� �Ϲ� �����Ͷ� �Ȱ���
//	unique_ptr<Knight> k(new Knight());
//
//	unique_ptr<Knight> k22 = move(k);
//	// �׷��� �̵��� �ϸ� ��밡����
//	// �ٵ� ȿ���� �׷��� ���� ��� ���� �Ⱦ���.
//}