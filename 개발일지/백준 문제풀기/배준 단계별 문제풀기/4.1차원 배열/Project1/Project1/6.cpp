/*
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
*/
/*
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m, i, j, k = 0;
	int num[101] = {};
	cin >> n >> m;

	for (int a = 1; a < m+1; a++)
	{
		cin >> i >> j >> k;
		
		for (int b = i; b <= j; b++)
		{
			num[b] = k;
		}
	}
	for (int d = 1; d <= n; d++)
	{
		cout << num[d] << " ";
	}
}
*/
#include <iostream>
using namespace std;

int main() {
	int n, m, i, j, box;
	cin >> n >> m;
	int num[101] = {};
	
	for (int v = 1; v < n+1; v++)
	{
		num[v] = v;
	}
	for (int a = 1; a <= m; a++)
	{
		cin >> i >> j;
		box = num[i];
		num[i] = num[j];
		num[j] = box;
	}
	for (int c = 1; c <= n; c++)
	{
		cout << num[c] << " ";
	}
}