//#1
/*
#include <iostream>
using namespace std;

int main() {
	int a = 0, b = 0;
	cin >> a >> b;

	if ((a >= 1 && a <= 100) || (b >=1 && b <= 100))
	{
		cout << b * a;
	}
	return 0;
}
*/
//#2
/*
#include <iostream>
using namespace std;

int main() {
	int x = 0, y = 0, w = 0, h = 0;
	cin >> x >> y >> w >> h;

	int min = x;
	if (y < min) { min = y; }
	if (w - x < min) { min = w - x; }
	if (h - y < min) { min = h - y; }

	cout << min;
	return 0;
}
*/
//#3
/*
#include <iostream>
using namespace std;

int main() {
	int x[4] = { 0 };
	int y[4] = { 0 };
	int count_x = 0;
	int count_y = 0;

	for (int i = 0; i < 3; i++)
	{
		cin >> x[i] >> y[i];
	}
	for (int i = 1; i < 3; i++)
	{
		if (x[0] != x[i]) { count_x++; }
		if (count_x == 1 && x[0] != x[i]) { x[3] = x[i]; }
		else if (count_x == 2) { x[3] = x[0]; }

		if (y[0] != y[i]) { count_y++; }
		if (count_y == 1 && y[0] != y[i]) { y[3] = y[i]; }
		else if (count_y == 2) { y[3] = y[0]; }
	}
	cout << x[3] << " " << y[3];
}
*/
//#4
/*
#include <iostream>
using namespace std;

int main() {
	unsigned int n = 0;
	cin >> n;
	cout << n * 4;
	return 0;
}
*/
//#5
/*
#include <iostream>
using namespace std;

int main() {
	int n = 0;
	cin >> n;
	int* x = new int[n];
	int* y = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> x[i] >> y[i];
	}

	int min_x = x[0], max_x = x[0];
	int min_y = y[0], max_y = y[0];
	for (int i = 0; i < n; i++)
	{
		if (x[i] > max_x) { max_x = x[i]; }
		if (x[i] < min_x) { min_x = x[i]; }

		if (y[i] > max_y) { max_y = y[i]; }
		if (y[i] < min_y) { min_y = y[i]; }
	}
	
	cout << (max_x - min_x) * (max_y - min_y);
	return 0;
}
*/
//#5-re
/*
#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 0; cin >> n;
	int x[100000] = { 0 };
	int y[100000] = { 0 };
	for (int i = 0; i < n; i++)
	{
		cin >> x[i] >> y[i];
	}

	sort(x, x + n);
	sort(y, y + n);

	cout << (x[n-1] - x[0]) * (y[n-1] - y[0]);
	return 0;
}
*/
//#6
#include <bits/stdc++.h>
using namespace std;

int main() {

	return 0;
}