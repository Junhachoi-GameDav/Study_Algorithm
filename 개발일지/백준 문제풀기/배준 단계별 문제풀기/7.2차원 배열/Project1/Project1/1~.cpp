/*
#include <iostream>
using namespace std;

int main() {
	int n, m, count =0;
	
	cin >> n >> m;

	int* A = new int[n * m];
	int* B = new int[n * m];
	for (int i = 0; i < n * m; i++)
	{
		cin >> A[i];
	}
	for (int i = 0; i < n * m; i++)
	{
		cin >> B[i];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << A[count] + B[count] << " ";
			count++;
		}
		cout << endl;
	}
}
*/

#include <iostream>
using namespace std;

int main() {
	int num[9][9] = { 0 };
	int max = 0;
	int num_x = 0, num_y = 0;

	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			cin >> num[x][y];

			if (max < num[x][y])
			{
				max = num[x][y];
				num_x = x;
				num_y = y;
			}
		}
	}

	cout << max << endl;
	cout << num_x+1 << " " << num_y+1;
}