//#1
/*
#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, result = 0;
	cin >> n >> m;
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}	
		
	for (int i = 0; i < n-2; i++)
	{
		for (int j = i+1; j < n-1; j++)
		{
			for (int k = j+1; k < n; k++)
			{
				int temp = arr[i] + arr[j] + arr[k];
				if (temp <= m && temp >= result)
					result = temp;
			}
		}
	}
	cout << result;
	return 0;
}
*/
//#2
/*
#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	for (int i = 1; i < n; i++)
	{
		int temp = i;
		int sum = i;
		while (temp != 0)
		{
			sum += temp % 10;
			temp = temp / 10;
		}

		if(sum == n)
		{
			cout << i << '\n';
			return 0;
		}
	}
	cout << 0;
	return 0;
}
*/
//#3
#include <bits/stdc++.h>
using namespace std;

int main() {
	int a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;

	for (int x = -999; x <= 999; x++)
	{
		for (int y = -999; y <= 999; y++)
		{
			int temp1 = (a * x) + (b * y);
			int temp2 = (d * x) + (e * y);
			if (c == temp1 && f == temp2)
			{
				cout << x << ' ' << y;
				return 0;
			}
		}
	}
	return 0;
}