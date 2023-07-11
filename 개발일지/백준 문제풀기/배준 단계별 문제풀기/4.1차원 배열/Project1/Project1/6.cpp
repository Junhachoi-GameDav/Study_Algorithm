#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m;
	cin >> n >> m;

	if ((n >= 1 && n <= 100)|| (m >= 1 && m <= 100)) 
	{ 
		int* box = new int[n];
		int* num2 = new int[m];

		int i, j, k;
		for (int x = 0; x < m; x++)
		{
			cin >> i >> j >> k;
			for (int v = i; v <= j; v++)
			{
				box[v-1] = k;
			}
		}
		for (int b = n; b > m ; b--)
		{
			box[b-1] = 0;
		}
		for (int c = 0; c < n; c++)
		{
			cout << box[c] << " ";
		}
	}
}