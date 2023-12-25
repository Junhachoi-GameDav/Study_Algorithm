#include <iostream>
using namespace std;


// vector/list -> Tree -> Graph -> BFS -> Dijistra ->A* 
// A* ��ã�� �˰����� �˱����ؼ� �˾ƾ���  �� ���ĵ�

//����Լ� =Ʈ���� �˱����ؼ�

void Func(int a)
{
	if (a >= 0) { return; } //����Լ��� ���� �����÷ο츦 ���ϱ� ���ؼ� 
	//�ݵ�� �������ִ� ������ �ɾ���Ѵ�.

	cout << a << endl;

	Func(a - 1);
}

//5! = 5*4*3*2*1 = 5 * 4! =120 / 5���丮��
//n! = n .... 1  = n * (n-1)!

int Factorial(int n)
{
	if (n <= 1) { return 1; }

	return n * Factorial(n - 1);
}

//��Ŭ���� ȣ���� �˰��� = �ִ������� ���ϴ� �˰���
// a > b
// GCD(1071, 1029)�϶�
// GCD(1029, 1071 % 1029 =42)
// GCD(42, 1029 % 42 = 21)
// GCD(21, 0) =21 �ִ�����

int Gcd(int a, int b)
{
	if (b == 0) { return a; }

	return Gcd(b, a % b);
}
//
//int main() {
//
//	Func(5);
//}