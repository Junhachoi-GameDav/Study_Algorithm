#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

// �α����Ҷ� ���ڵ��� ���Ѵٴ��� �������� ������ ����.

//
//int main() {
//
//	string str = "wwww";
//	string str2 = "wwww";
//
//
//	//��
//	if (str == str2) {}
//	str.compare(str2); // 1 or 0
//
//	//����
//	string str3;
//	str3 = str;
//
//	//�߰�
//	// ������ ����� ��¥�� ����°� �ƴ϶� �ɸ��� �̸���
//	// wwww_DELETED �̷������� �÷��׸� �������´�. �����ϱ� ���ؼ�
//	str.append("123");
//	str += "123";
//
//	//ã��
//	auto c = str.find("ww"); //���°���� �ε����� �����
//	if (c == string::npos) // ������ ��ã�Ҵٸ�(���ٸ�) vector�� !=v.end() ���� ������
//	{
//		cout << "no found";
//	}
//
//	//��ü
//	// �ٵ� ���־����� ��� ������� �׳� ���� �˻��ϰ� ����ٰ��Ѵ�. 
//	string chat_str = "SHIT~~!!";
//	string find_str = "SHIT";
//	string replace_str = "****";
//
//	chat_str.replace(chat_str.find(find_str), find_str.length(), replace_str);
//
//
//	// ��Ƽ����Ʈ�� �����ڵ�
//	// ����θ� �����ϸ� ���� �ѱ��� �����ų� �Ҽ��ִ�. 
//
//	// 1) ASCII �ڵ�(�ƽ�Ű) -> ��� ���
//	// 7BIT (0 ~ 127) 128������ ǥ�� ����
//
//
//	// 2) ANSI
//	// ASCII + �������� 128��
//	// CP949(�ѱ���)
//	// ���� : ȯ�渶�� �ٸ��� ����
//
//	// 3) �����ڵ� (������ ���� = ������ ��ȣ = ������ �����ڵ�)
//	// ���ڵ� (utf8, utf16) 
//	// - utf8	: ����(1) , �ѱ���/�߱���(3) ~~
//	// - utf16	: ����(2), �ѱ���(2), �߱��� (2) ~~
//
//	// 4) MBCS(Multi Byte Charactor Set)  VS   WBCS(Wide Byte Charactor Set)
//	// - MBCS - ��Ƽ����Ʈ ���� = �������� ���ڵ��� ���� (UTF-8�� ��ǥ�� �Դ� ���� �ؾ��ϴϱ�)
//	// - WBCS - �����ڵ� ����	= �������� ���ڵ� (UTF-16) ����* �����ڵ�� ���ڵ����� ���ϴ°��� ���������ΰ��� �ƴϴ�.
//
//	setlocale(LC_ALL, ""); //�⺻����(������ ���)
//	cout << setlocale(LC_ALL, NULL);
//
//	const char* test = "aaa�ѱ�"; // ����� 1����Ʈ������ �ѱ��� 2����Ʈ �̻��̶� char������ �ִ°� ���Ͱ� Ʋ�� ����
//
//	auto test2 = u8"aaa�ѱ�"; //utf8 �� �ϰڴٴ¶�
//	setlocale(LC_ALL, "en_US.UTF-8"); //�̼����̿��� �ȱ���
//
//	auto test3 = u"aaa�ѱ��Դϴ�"; //u�� utf16��
//
//	//���� utf-16�� ���� ���ٰ���
//	//����Ƽ/�𸮾� �̹���� ���̾�
//	//c#�� char�� 2����Ʈ�� �׷��� �Ű� �Ƚᵵ ������ c++�� �ƴϾ�~ �ϳ��ϳ� ������ߵ�
//	wchar_t ch = L'��'; //wbcs
//	wstring s = L"aaa�ѱ��Դϴ�.";
//	wcout << s << endl;
//}