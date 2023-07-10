/*
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n;
	cin >> n;
	int* a = new int[n];
	int* b = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		b[i] = a[i];
	}
	for (int j = 0; j < n; j++)
	{
		if (a[j] > a[j + 1]) { a[j+1] = a[j]; }
		if (b[j] < b[j + 1]) { b[j+1] = b[j]; }
	}
	cout << b[n-1] << " " << a[n];
}
*/