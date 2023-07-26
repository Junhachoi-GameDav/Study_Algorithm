/*
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
*/
#include <iostream>
using namespace std;

int main() {
	int n, cnt;
	cin >> n;
	cnt = n;

	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		for (int j = 0; j < s.length(); j++)
		{
			int num;

			for (num = j+1; num < s.length(); num++)
			{
				if (s[j] == s[num] && j == num - 1) { num++; }
				else if (s[j] == s[num]) { cnt--; break; }
			}
			if (num != s.length()) { break; }
		}
	}
	cout << cnt;
}
