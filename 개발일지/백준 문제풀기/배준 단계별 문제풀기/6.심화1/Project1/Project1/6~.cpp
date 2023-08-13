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
/*
#include <iostream>
using namespace std;

int main() {
	int n, count = 0;
	string s;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		bool a[26] = { false, };
		a[(int)(s[0]) - 97] = true;

		for (int j = 1; j < s.length(); j++)
		{
			
			if (s[j] == s[j - 1]) {
				continue;
			}
			else if (s[j] != s[j - 1] && a[(int)(s[j]) - 97] == true) {
				count++ ;
				break;
			}
			else {
				a[(int)(s[j]) - 97] = true;
			}
		}
	}
	cout << n - count;
	return 0;
}
*/

#include <iostream>
using namespace std;

int main() {
	int N;
	string word;
	int count = 0;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> word;
		bool a[26] = { false, };
		a[(int)(word[0]) - 97] = true;

		for (int i = 1; i < word.size(); i++) {
			if (word[i] == word[i - 1]) {
				continue;
			}
			else if (word[i] != word[i - 1]
				&& a[(int)(word[i]) - 97] == true) {
				count++;
				break;
			}
			else {
				a[(int)(word[i]) - 97] = true;
			}
		}
	}

	cout << N - count;

	return 0;
}
