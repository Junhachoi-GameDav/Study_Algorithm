#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, count = 0;
	cin >> n;
	string* s = new string[n];
	int arr[26] = { 0 };
	bool one_team = false;

	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			if (s[i][0] == s[j][0]) { count++; }
			if (count == 4)
			{ 
				one_team = true;
				arr[s[i][0] - 97]++;
				break;
			}
		}
		count = 0;
	}

	if (!one_team) { cout << "PREDAJA"; }
	else
	{
		for (int i = 0; i < 26; i++)
		{
			char data = i + 97;
			if (arr[i]) { cout << data; }
		}
	}
	return 0;
}