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