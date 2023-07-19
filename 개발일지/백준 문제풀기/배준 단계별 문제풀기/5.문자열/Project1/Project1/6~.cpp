/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	int n=0, num[100];
	string s;
	cin >> s;
	
	for (int i = 0; i < 26; i++)
	{
		num[i] = -1;
	}
	for (int j = 0; j < s.length(); j++)
	{
		if (num[int(s[j]) - 97] == -1) { num[int(s[j]) - 97] = n; }
		n++;
	}
	for (int i = 0; i < 26; i++)
	{
		cout << num[i] << " ";
	}
}
*/
/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	int t, r_num[1001];
	cin >> t;
	string s;

	for (int i = 1; i <= t; i++)
	{
		cin >> r_num[i] >> s;

		if (s.length() <= 20 && r_num[i] <= 8)
		{
			for (int j = 0; j < s.length(); j++)
			{
				for (int x = 0; x < r_num[i]; x++)
				{
					cout << s[j];
				}
			}
			cout << endl;
		}
	}
}
*/