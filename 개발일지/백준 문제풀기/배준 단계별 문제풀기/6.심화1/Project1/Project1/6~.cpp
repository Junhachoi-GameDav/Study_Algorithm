#include <iostream>
using namespace std;

int n = 0, a=0;
string c[6] = {
	"c=", "c-",
	"d-", "lj",
	"nj", "s=", 
};
string c2 = "dz=", c3 = "z=", s;

int main() {
	cin >> s;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < s.length(); j++)
		{
			if ((s.find(c[i],j) <= j)) {
				n++;
			}
		}
	}
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == 'd' && s[i + 1] == 'z' && s[i + 2] == '=') {
			a++;
		}
		else if (s[i] == 'z' && s[i + 1] == '=') {
			a++;
		}
	}
	cout << n << " " << a;
}