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
/*
#include <iostream>
using namespace std;

int main() {

	int N = 0, K = 0;
	int temp = 0, count =0;
	cin >> N >> K;
	
	for (int i = N; i >= 1; i--)
	{
		if (N % i == 0 && count < K)
		{
			temp = N / i;
			count++;
		}
	}
	if (count < K) { temp = 0; }
	cout << temp;
	return 0;
}
*/
//#3
/*
#include <iostream>
using namespace std;

int main() {
	int n = 0 , sum = 0;
	int arr[100000] = { 0 };
	
	while (true)
	{
		cin >> n;
		if (n == -1) { break; } //Á¾·á
		sum = 0;

		for (int i = n; i > 1; i--)
		{
			if (n % i == 0)
			{
				arr[i] = n / i;
				sum += arr[i];
			}
		}

		if (sum == n && sum > 0)
		{
			cout << n << " = ";
			for (int i = n; i > 1; i--)
			{
				if (n % i == 0)
				{
					cout << arr[i];
					if (i > 2) { cout << " + "; }
				}
			}
		}
		else
		{
			cout << n << " is NOT perfect.";
		}
		cout << endl;
	}
	
	return 0;
}
*/
//#4
/*
#include <iostream>
using namespace std;

int main() {
	int i,j,n = 0, count = 0, count2 = 0;
	int arr[100] = { 0 };

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
		for (j = arr[i];  j >= 1;  j--)
		{
			if (arr[i] % j == 0 && j > 1) { count++; }
		}
		if (count == 1) { count2++; }
		count = 0;
	}
	cout << count2;
	return 0;
}
*/