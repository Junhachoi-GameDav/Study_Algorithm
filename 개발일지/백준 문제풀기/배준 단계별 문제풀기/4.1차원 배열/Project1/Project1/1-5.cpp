/*
#include <iostream>
using namespace std;

int main() {
	int n, save_num=0 ,find_num;
	cin >> n;
	int* v = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	cin >> find_num;
	for (int j = 0; j < n; j++)
	{
		if (find_num == v[j]) { save_num++; }
	}
	cout << save_num;
}
*/
/*
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	int n, find_num_x;
	cin >> n >> find_num_x;
	int* a = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		if (a[i] < find_num_x) { cout << a[i] << " "; }
	}
}
*/
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
/*
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
*/
/*
#include <iostream>
using namespace std;

int main() {
	int n = 9, max = -100, count_num;
	int *num =new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> num[i];
		if (num[i] > max) { max = num[i]; count_num = i+1; }
	}
	cout << max << "\n" << count_num;;
}
*/