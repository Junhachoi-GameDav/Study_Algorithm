#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

// �α����Ҷ� ���ڵ��� ���Ѵٴ��� �������� ������ ����.


int main() {

	string str = "wwww";
	string str2 = "wwww";


	//��
	if (str == str2) {}
	str.compare(str2); // 1 or 0

	//����
	string str3;
	str3 = str;

	//�߰�
	// ������ ����� ��¥�� ����°� �ƴ϶� �ɸ��� �̸���
	// wwww_DELETED �̷������� �÷��׸� �������´�. �����ϱ� ���ؼ�
	str.append("123");
	str += "123";

	//ã��
	auto c = str.find("ww"); //���°���� �ε����� �����
	if (c == string::npos) // ������ ��ã�Ҵٸ�(���ٸ�) vector�� !=v.end() ���� ������
	{
		cout << "no found";
	}

	//��ü
	// �ٵ� ���־����� ��� ������� �׳� ���� �˻��ϰ� ����ٰ��Ѵ�. 
	string chat_str = "SHIT~~!!";
	string find_str = "SHIT";
	string replace_str = "****";

	chat_str.replace(chat_str.find(find_str), find_str.length(), replace_str);


	// ��Ƽ����Ʈ�� �����ڵ�
	// ����θ� �����ϸ� ���� �ѱ��� �����ų� �Ҽ��ִ�. 
}