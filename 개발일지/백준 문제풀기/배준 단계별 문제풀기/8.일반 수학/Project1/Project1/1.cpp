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