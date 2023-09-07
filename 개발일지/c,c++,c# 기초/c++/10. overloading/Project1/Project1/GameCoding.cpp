//��ü����

//������ �����ε�
// - �ɹ� ������ �Լ� ����
//  a op b ���� �������� ���۷�����
// 
// 
// - ���� ������ �Լ� ����
//  a op b �� ���¶��, a/b ��θ� ������ �Լ��� �ǿ����ڷ� ���
// �� ��� �� �ְڴٴ� ��


//Ŭ�� + Ŭ�󽺸� �ϰ� ���ִµ� ������ ��ä�Ӱ� �ϰ������ ����.
// �����ڸ� Ŀ�� �Ҷ� ��������� �������� ������ ����.



#include<iostream>
using namespace std;

class Pos
{
public:

	Pos()
	{

	}

	//�����ڿ� ������ �� ���� �ߵ��ɱ�
	//�Ķ���Ͱ� �ϳ�¥�� ���������� explicit�� �ٿ��ִ°� ���Űǰ��� ����. �̰� ���� �������� ���´�.
	explicit Pos(int b)
	{
		x = b;
		y = b;
	}

	Pos operator+(const Pos& b)
	{
		Pos	pos;
		pos.x = x + b.x;
		pos.y = y + b.y;
		return pos;
	}
	int x = 0;
	int y = 0;

	Pos operator+(int n)
	{
		Pos pos;
		pos.x = x + n;
		pos.y = y + n;
		return pos;
	}

	// �ٸ� Ÿ�Ե� �����ϴ�.
	bool operator==(const Pos& b)
	{
		return x == b.x && y == b.y;
	}
	
	//���� ������
	void operator=(int b)
	{
		x = b;
		y = b;
	}
	
	//������
	// b= c= a; �̷������� ��ġ�ͷ� ���޾Ƽ� �����ϰ� ������ 
	//�ڽ� ������ �����ص� �ǰ� &���� ���縦 �ص� �ǰ� �������� ����
	/*Pos& operator=(int b)
	{
		x = b;
		y = b;
		return *this;
	}*/
};

//�̷��� ���� �����ڷ� ���ְ� �Ķ���Ϳ� ���ϴ� ������ ���� ��
Pos operator+ (int a, const Pos & b)
{
	Pos pos;
	pos.x = a + b.x;
	pos.y = a + b.y;
	return pos;
}


void TestPos(Pos a)
{
	
}



int main() {
	int a = 10;
	int b = 10;
	int c = a + b;

	Pos pos1;
	Pos pos2;

	//Pos pos3 = pos1 + pos2;
	//Pos pos3 = pos1 + 10; // ��Ʈ + Ŭ�󽺴� �ȵȴ�. a op b�̱� ������ �̷��� ���� ������ �Լ� ������ ����Ѵ�.
	//pos3 = pos1.operator+(pos2); �������� �Ȱ���.

	Pos pos3 = 10 + pos1;

	//�߿��� ����Ʈ
	//����� ���ÿ� ���� �ҽ� �����ڰ� �ߵ� �ȴ�. ��
	//Pos pos1(10); �̰Ŵ�.. ������ �ƴϴ�.
	// �̰� �ȵǾ� �����̴�.
	//Pos pos1 = 10;
	//Pos pos2 = 20;

	Pos pos1(10);
	Pos pos2(20);

	//������ �������Ŀ� �����ҽ� �������̴�.
	pos1 = 10; //���� ������ ���� ����
	pos2 = 20;

	//TestPos(10); // ������ posŬ�󽺸� ������� �س��µ� ������ �޾����� ������ ������ �޴� �����ڸ� Ŭ�󽺾ȿ� �������� �̰� 
	//�����Ϸ��� ������ �ϰ� �Ѱܹ�����. �̷� �� �ȴ�. �̰� �������� explicit�� �ٿ��ִ� ���̴�.
}