//split() c++ stl ������ split()�Լ��� ����... �׷��� ����� ����Ѵ�.

#include <bits/stdc++.h>
using namespace std;

vector<string> split(string input, string delimeter)
{
	vector<string> ret;
	long long pos = 0;
	string token = "";
	//input���� delimeter�� ã��������
	while ((pos= input.find(delimeter)) != string::npos)
	{
		token = input.substr(0, pos);				//0���� pos=3 ����("abcd"�ϋ� d�� ã�´ٸ� abc = 3)�� ��ū�� ����
		ret.push_back(token);						//�迭�� �������
		input.erase(0, pos + delimeter.length());	//�տ� ���ڿ��� ���� (3 + 1��ŭ) abcdabc�϶� abcd�� ����� abc�� ����
		//���̻� d �� ������ ��������
	}
	ret.push_back(token);							//���� abc�� ����
	return ret;							
	// �տ��� d�� ã�� d ���� ���ڵ��� ������ �ڿ� ��¥�� ����. �׷��� �ٽ� �տ���¥�� ������� �־
	// ��������� d�� ���� ���ڸ� �־��������
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