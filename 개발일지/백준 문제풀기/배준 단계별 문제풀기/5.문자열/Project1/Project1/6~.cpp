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
/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	int n=0;
	string s;
	getline(cin, s);
	if (s.length() <= 1000000)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == ' ') { n++; }
		}
		if (s[0] == ' ') { n--; }
		if (s.back() == ' ') { n--; }
	}
	cout << n+1;
}
*/
/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	string a, b;
	char temp;
	cin >> a >> b;

	temp = a.front();
	a.front() = a.back();
	a.back() = temp;
	
	temp = b.front();
	b.front() = b.back();
	b.back() = temp;

	stoi(a); stoi(b);

	a > b ? cout << a : cout << b ;
}
*/
/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	string s;
	cin >> s;
	char c[15]; int n = 0;

	for (int i = 0; i < s.length(); i++)
	{
		c[i] = s[i];

		switch (c[i])
		{
		case'A':case'B':case'C':
			n += 3;
			break;
		case'D':case'E':case'F':
			n += 4;
			break;
		case'G':case'H':case'I':
			n += 5;
			break;
		case'J':case'K':case'L':
			n += 6;
			break;
		case'M':case'N':case'O':
			n += 7;
			break;
		case'P':case'Q':case'R':case'S':
			n += 8;
			break;
		case'T':case'U':case'V':
			n += 9;
			break;
		case'W':case'X':case'Y':case'Z':
			n += 10;
			break;
		}
	}
	cout << n;
}
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	int n = 0;
	while (n<=100) {
		getline(cin, s);
		if (cin.eof() == true) { break; }
		cout << s<< endl;
		n++;
	}
}