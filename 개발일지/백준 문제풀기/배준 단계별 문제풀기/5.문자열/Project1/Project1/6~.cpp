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