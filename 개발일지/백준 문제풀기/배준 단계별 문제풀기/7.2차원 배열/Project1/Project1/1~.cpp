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
/*
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
*/
/*
#include <iostream>
using namespace std;

int main() {
	char ch[5][15] = { NULL };
	int max = 0;

	for (int i = 0; i < 5; i++)
	{
		cin >> ch[i];
	}
	
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (ch[j][i] == NULL) { continue; }
			cout << ch[j][i];
		}
	}
	return 0;
}
*/
/*
#include <iostream>
using namespace std;

int main() {
	int n = 0;
	int width[100] = { 0 };
	int height[100] = { 0 };

	cin >> n;
	int area = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> width[i] >> height[i];
	}
	
	int temp_x = 0;
	int temp_y = 0;
	int temp_area = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (abs(width[i] - width[j]) < 10 && abs(height[i] - height[j]) < 10)
			{
				temp_x = abs(width[i] - width[j]);
				temp_y = abs(height[i] - height[j]);
				if (temp_x > 0 && temp_y > 0)
				{
					temp_area += abs(temp_x - 10) * abs(temp_y - 10);
				}
			}
		}
	}
	if (temp_area == 0)
	{ 
		area = 0;
	}
	else 
	{
		area = (n *100) - temp_area;
	}
	cout << area;
}*/

#include <iostream>
using namespace std;

int main() {
	
	int a[100][100] = { 0 };
	int n, count = 0;

	cin >> n;

	while (n--)
	{
		int x, y;
		cin >> x >> y;
		for (int i = y; i < y+10; i++)
		{
			for (int j = x; j < x+10; j++)
			{
				if (a[i][j]) continue; //Áßº¹Àº ³Ñ±è
				a[i][j] = 1;
				count++;
			}
		}
	}
	cout << count;
}