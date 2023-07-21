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