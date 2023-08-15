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
/*
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
*/

#include <iostream>
using namespace std;

int main() {
	
	string subjects_char_num;
	string grades;
	float rating; float sub_rating=0; 
	float add = 0;
	float total_rating = 0;

	for (int i = 0; i < 20; i++)
	{
		cin >> subjects_char_num >> rating >> grades;

		if (grades == "A+") { sub_rating = 4.5f; }
		else if (grades == "A0") { sub_rating = 4.0f; }
		else if (grades == "B+") { sub_rating = 3.5f; }
		else if (grades == "B0") { sub_rating = 3.0f; }
		else if (grades == "C+") { sub_rating = 2.5f; }
		else if (grades == "C0") { sub_rating = 2.0f; }
		else if (grades == "D+") { sub_rating = 1.5f; }
		else if (grades == "D0") { sub_rating = 1.0f; }
		else if (grades == "F") { sub_rating = 0.0f; }
		else if (grades == "P") { sub_rating = 0.0f; rating = 0; }
		
		add += rating * sub_rating;
		total_rating += rating;
	}
	cout << fixed;
	cout.precision(6);
	cout << add / total_rating;
}
/*
#include <iostream>
using namespace std;

int main() {
	string majorName;
	double avg = 0;
	float sumGrade = 0;
	double score[20];
	float grade[20];
	string input;

	for (int i = 0; i < 20; ++i)
	{
		cin >> majorName >> grade[i] >> input;
		if (input == "A+") score[i] = 4.5;
		else if (input == "A0") score[i] = 4.0;
		else if (input == "B+") score[i] = 3.5;
		else if (input == "B0") score[i] = 3.0;
		else if (input == "C+") score[i] = 2.5;
		else if (input == "C0") score[i] = 2.0;
		else if (input == "D+") score[i] = 1.5;
		else if (input == "D0") score[i] = 1.0;
		else if (input == "F") score[i] = 0.0;
		else if (input == "P") { score[i] = 0.0; grade[i] = 0; }
		avg += (score[i] * grade[i]);
		sumGrade += grade[i];
	}
	avg = avg / sumGrade;
	cout << fixed;
	cout.precision(6);
	cout << avg;
}*/