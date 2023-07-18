/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	cin >> s;
	if(s.length() <= 100){ cout << s.length(); }
}
*/
/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	int t;
	cin >> t;
	string words[11];
	for (int i = 1; i <= t; i++)
	{
		cin >> words[i];
		cout << words[i].front() << words[i].back() << endl;
	}
}
*/
/*
#include <iostream>
using namespace std;

int main() {
	char c;
	cin >> c;
	cout << int(c);
}
*/
/*
#include <iostream>
#include <string>
using namespace std;

int main() {
	int n, sum =0 ;
	string s, num[101];
	cin >> n >> s;
	for (int i = 1; i <= n; i++)
	{
		num[i] = s[i-1];
		sum += stoi(num[i]);
	}
	cout << sum;
}
*/