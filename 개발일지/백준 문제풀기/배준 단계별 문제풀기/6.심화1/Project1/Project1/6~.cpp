#include <iostream>
using namespace std;

int main() {
	string s;
	cin >> s;
	int len = s.length();
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '-')
			len--;
		else if (s[i] == '=')
			len--;
		else if (s[i] == 'd' && s[i + 1] == 'z' && s[i + 2] == '=')
			len--;
		else if (s[i] == 'l' && s[i + 1] == 'j')
			len--;
		else if (s[i] == 'n' && s[i + 1] == 'j')
			len--;
	}
	cout << len;
}