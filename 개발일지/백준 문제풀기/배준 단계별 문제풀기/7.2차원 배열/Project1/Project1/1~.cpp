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