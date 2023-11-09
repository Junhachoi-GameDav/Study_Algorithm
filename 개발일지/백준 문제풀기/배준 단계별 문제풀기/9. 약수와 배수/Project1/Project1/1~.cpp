//#1
/*
#include <iostream>
using namespace std;

int main() {

	int num1=0, num2=0;

	while (true)
	{
		cin >> num1 >> num2;
		if (num1 == num2) { break; }

		if (num2 % num1 == 0)
		{
			cout << "factor" << endl;
		}
		else if (num1 % num2 == 0)
		{
			cout << "multiple" << endl;
		}
		else
		{
			cout << "neither" << endl;
		}
	}
	
	return 0;
}
*/
//#2
#include <iostream>
using namespace std;

int main() {

	int N = 0, K = 0;
	int count = 0;
	cin >> N >> K;
	
	for (int i = N; i >= 1; i--)
	{

		if (N % i == 0 && count < K)
		{
			cout << N / i;
			count++;
		}
	}


	return 0;
}

