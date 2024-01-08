//split() c++ stl 내에는 split()함수가 없다... 그래서 만들어 줘야한다.

#include <bits/stdc++.h>
using namespace std;

vector<string> split(string input, string delimeter)
{
	vector<string> ret;
	long long pos = 0;
	string token = "";
	//input에서 delimeter를 찾을때까지
	while ((pos= input.find(delimeter)) != string::npos)
	{
		token = input.substr(0, pos);				//0부터 pos=3 까지("abcd"일떄 d를 찾는다면 abc = 3)를 토큰에 넣음
		ret.push_back(token);						//배열에 집어넣음
		input.erase(0, pos + delimeter.length());	//앞에 문자열을 제거 (3 + 1만큼) abcdabc일때 abcd를 지우고 abc만 남음
		//더이상 d 가 없으니 빠져나옴
	}
	ret.push_back(token);							//남은 abc를 넣음
	return ret;							
	// 앞에서 d를 찾고 d 전에 글자들을 넣은후 뒤에 글짜를 지움. 그러고 다시 앞에글짜를 지운것을 넣어서
	// 결과적으로 d만 빼고 글자를 넣어놓은것임
}
//
//int main() {
//	string s = "abcdabc";
//	string d = "d";
//	vector<string> a = split(s, d);
//
//	for (string b : a)
//	{
//		cout << b << "\n";
//	}
//}