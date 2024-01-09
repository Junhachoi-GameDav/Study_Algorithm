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
