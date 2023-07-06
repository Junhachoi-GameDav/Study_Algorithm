/*
#include <iostream>
using namespace std;
int main() {
	int h, m;
	cin >> h >> m;
	
	m -=45;
	if (m < 0) { h -= 1; m = 60 - (m*(-1)); }
	else if (m == 0) { m = 0; }
	
	if (h < 0) { h = 23; }

	cout << h << " " << m;
}
*/