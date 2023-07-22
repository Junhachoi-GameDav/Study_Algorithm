/*
#include <iostream>
using namespace std;

int main() {
	cout << "         ,r\'\"7" << "\n";
	cout << "r`-_   ,'  ,/" << "\n";
	cout << " \\. \". L_r'" << "\n";
	cout << "   `~\\/" << "\n";
	cout << "      |" << "\n";
	cout << "      |";
}
*/
/*
#include <iostream>
using namespace std;

int main() {
	int a[6] = { 1,1,2,2,2,8 };
	int b[6] = { 0 };
	for (int i = 0; i < 6; i++)
	{
		cin >> b[i];
		if (a[i] < b[i] || a[i] > b[i]) { a[i] -= b[i]; }
		else { a[i] = 0; }
	}
	for (int i = 0; i < 6; i++)
	{
		cout << a[i] << " ";
	}
}
*/
#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int a = n, b = 1;
	int c = 1, d = 2*n-3;

	for (int i = 0; i < 2*n-1; i++)
	{
		if (b <= 2 * n - 1) {
			for (int j = 0; j < a - 1; j++)
			{
				cout << " ";
			}
			for (int x = 0; x < b; x++)
			{
				cout << "*";
			}
			cout << "\n";
			a--;
			b += 2;
		}
		else {
			for (int j = 0; j < c; j++)
			{
				cout << " ";
			}
			for (int x = d; x > 0; x--)
			{
				cout << "*";
			}
			cout << "\n";
			d -= 2;
			c++;
		}
	}
}