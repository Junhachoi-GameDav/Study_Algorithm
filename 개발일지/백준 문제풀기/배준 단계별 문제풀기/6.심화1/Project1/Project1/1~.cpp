/*
#include <iostream>
using namespace std;

int main() {
	cout << "         ,r\'\"7" << "\n";
	cout << "r`-_   ,'  ,/" << "\n";
	cout << " \\. \". L_r'" << "\n";
	cout << "   `~\\/" << "\n";
	cout << "      |" << "\n";
	cout << "      |";
}
*/
/*
#include <iostream>
using namespace std;

int main() {
	int a[6] = { 1,1,2,2,2,8 };
	int b[6] = { 0 };
	for (int i = 0; i < 6; i++)
	{
		cin >> b[i];
		if (a[i] < b[i] || a[i] > b[i]) { a[i] -= b[i]; }
		else { a[i] = 0; }
	}
	for (int i = 0; i < 6; i++)
	{
		cout << a[i] << " ";
	}
}
*/
/*
#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int a = n, b = 1;
	int c = 1, d = 2*n-3;

	for (int i = 0; i < 2*n-1; i++)
	{
		if (b <= 2 * n - 1) {
			for (int j = 0; j < a - 1; j++)
			{
				cout << " ";
			}
			for (int x = 0; x < b; x++)
			{
				cout << "*";
			}
			cout << "\n";
			a--;
			b += 2;
		}
		else {
			for (int j = 0; j < c; j++)
			{
				cout << " ";
			}
			for (int x = d; x > 0; x--)
			{
				cout << "*";
			}
			cout << "\n";
			d -= 2;
			c++;
		}
	}
}
*/
/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	cin >> s;
	int n = 0;
	int size = s.length();

	if (size == 1) { n = 1; }
	else
	{
		for (int i = 0; i < size /2; i++)
		{
			if (s[i] == s[(size - 1) - i]) { n = 1; }
			else { n = 0; break; }
		}
	}
	cout << n;
}
*/
/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	cin >> s;
	int counted[26]{ 0, };
	int a;

	for (int x = 0; x < s.length(); x++)
	{
		if ((int)s[x] >= 65 && (int)s[x] <= 90) {
			a = (int)s[x] - 65;
		}
		else if ((int)s[x] >= 97 && (int)s[x] <= 122) {
			a = (int)s[x] - 97;
		}
		counted[a] = counted[a] + 1;
	}
	
	int max = counted[0];
	int k = 0;

	for (int i = 1; i <= 25; i++)
	{
		if (max < counted[i]) { max = counted[i]; k = i; }
	}

	for (int i = 1; i <= 25; i++)
	{
		if (i == k) { i = i + 1; }
		else
		{
			if (max == counted[i])
			{
				cout << "?";
				return 0;
			}
		}
	}
	cout << (char)(k + 65);
}
*/
/*
#include <iostream>
using namespace std;

int main()
{
	string str;
	cin >> str;
	int count = 0 , a=0;
	int c[26] = { 0 };

	for (int i = 0; i < str.length(); i++)
	{
		if ((int)str[i] >= 65 && (int)str[i] <= 90) {
			a = (int)str[i] - 65;
		}
		else if ((int)str[i] >= 97 && (int)str[i] <= 122) {
			a = (int)str[i] - 97;
		}
		c[a] = c[a] + 1;
	}

	int max = 0, max_index = 0;

	for (int i = 0; i < 26; i++)
	{
		if (max < (int)c[i])
		{
			max = (int)c[i];
			max_index = i;
		}
	}

	for (int i = 0; i < 26; i++)
	{
		if (max == (int)c[i]) { count++; }
	}

	if (count > 1)
	{ 
		cout << "?";
	}
	else
	{ 
		cout << (char)(max_index + 65);
	}
	return 0;
}
*/
/*
#include <iostream>
using namespace std;

int a[26], cnt = 0;
string s;

int main() {
	cin >> s;

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] < 97) { a[s[i] - 65]++; } //대문자
		else { a[s[i] - 97]++; } //소문자
	}

	int max = 0, max_index = 0;

	for (int i = 0; i < 26; i++) //최대 값
	{
		if (max < a[i])
		{
			max = a[i];
			max_index = i;
		}
	}

	for (int i = 0; i < 26; i++) //여러개 확인
	{
		if (max == a[i]) { cnt++; }
	}

	if (cnt > 1) { cout << "?"; }
	else { cout << (char)(max_index + 65); }
}
/*
/*
#include <iostream>
using namespace std;

int alpha[26], cnt = 0;
string input;

int main() {
	cin >> input;

	//빈도수 체킹
	for (int i = 0; i < input.length(); i++) {
		if (input[i] < 97) alpha[input[i] - 65]++; //대문자
		else alpha[input[i] - 97]++; //소문자
	}

	int max = 0, max_indx = 0;

	for (int i = 0; i < 26; i++) {
		if (max < alpha[i]) {
			max = alpha[i];
			max_indx = i;
		}
	}
	//가장 많이 사용된 알파벳이 여러개인가?
	for (int i = 0; i < 26; i++) {
		if (max == alpha[i]) cnt++;
	}
	//여러개라면 ? 출력, 아니라면 대문자로 출력
	if (cnt > 1) cout << "?";
	else cout << (char)(max_indx + 65);
}
*/