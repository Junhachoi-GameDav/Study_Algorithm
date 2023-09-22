/*
#include <iostream>
using namespace std;

int main() {
	
	int b=0, n=0, total=0;
	string alphabet;

	cin >> alphabet >> b;
	n = alphabet.length();

	for (int i = 0; i < n; i++)
	{
		if (alphabet[i] >= '0' && alphabet[i] <= '9') {
			total = total * b + (alphabet[i] - 48);
		}
		else {
			total = total * b + (alphabet[i] - 55);
		}
	}

	cout << total;
	return 0;
}
*/
/*
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n = 0, b = 0;
	string c_sum = "";
	cin >> n >> b;

	int temp = 0;

	while (n > 0)
	{
		temp = n % b;
		if (temp < 10) 
		{
			c_sum += char(temp + '0');
		}
		else
		{
			c_sum += char(temp -10 + 'A');
		}
		
		n = n / b;
	}

	reverse(c_sum.begin(), c_sum.end());
	cout << c_sum << endl;
	return 0;
}
*/
/*
#include<iostream>
using namespace std;

int main() {
	int t = 0;
	
	cin >> t;
	int* c = new int[t];

	for (int i = 0; i < t; i++)
	{
		cin >> c[i];
		int temp = 0, temp2= 0 ;
		if (1 <= c[i] <= 500)
		{
			temp = c[i] / 25;
			temp2 = c[i] % 25;
			cout << temp << " ";

			temp = temp2 / 10;
			temp2 = temp2 % 10;
			cout << temp << " ";

			temp = temp2 / 5;
			temp2 = temp2 % 5;
			cout << temp << " ";

			temp = temp2 / 1;
			temp2 = temp2 % 1;
			cout << temp << endl;
		}
	}
	return 0;
}*/
#include <iostream>
using namespace std;

int main() {
	int defalt = 3, n = 0;
	int temp = 1;
	cin >> n;

	for (int i = 1; i < n; i++)
	{
		temp = temp * 2;
		defalt += temp;
	}
	cout << defalt * defalt;
	return 0;
}