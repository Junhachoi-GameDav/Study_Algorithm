#include <iostream>
using namespace std;


// vector/list -> Tree -> Graph -> BFS -> Dijistra ->A* 
// A* 길찾기 알고리즘을 알기위해서 알아야할  선 지식들

//재귀함수 =트리를 알기위해서

void Func(int a)
{
	if (a >= 0) { return; } //재귀함수는 스택 오버플로우를 피하기 위해서 
	//반드시 나갈수있는 조건을 걸어야한다.

	cout << a << endl;

	Func(a - 1);
}

//5! = 5*4*3*2*1 = 5 * 4! =120 / 5팩토리얼
//n! = n .... 1  = n * (n-1)!

int Factorial(int n)
{
	if (n <= 1) { return 1; }

	return n * Factorial(n - 1);
}

//유클리드 호제법 알고리즘 = 최대공약수를 구하는 알고리즘
// a > b
// GCD(1071, 1029)일때
// GCD(1029, 1071 % 1029 =42)
// GCD(42, 1029 % 42 = 21)
// GCD(21, 0) =21 최대공약수

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