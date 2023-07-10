#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n , min =1000000, max = -1000000;
	cin >> n;
	int* a = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		if (max < a[i]) { max = a[i]; }
		if (min > a[i]) { min = a[i]; }
	}

	cout << min << " " << max;
}