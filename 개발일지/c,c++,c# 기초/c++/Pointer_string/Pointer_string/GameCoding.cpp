#include<iostream>
using namespace std;

int StrLen(const char* str)
{
	int i = 0;

	//*(str+i) == srt[i]   �����Ϳ� �迭�� �����������̶���Ѵ�.
	while (str[i] != 0)
	{
		i++;
	}

	return i;
}

//�����ϴ� �Լ�
char* StrCpy(char* dest, char* src)
{
	char* ret = dest;  //ret�� dest�� �ֱ�

	/*
	�ε��� ���
	int i = 0;
	while (src[i] != 0) 
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0; //������ 0�� ���簡 �ȵ����Ƿ�
	*/

	//�����͸� �̿��ϴ� ���  // �ٽ� 
	while (*src != 0) 
	{
		*dest = *src;
		dest++; //char Ÿ���̶� 1����Ʈ �ű� �� ���� ����
		src++;
	}
	*dest = 0;

	return ret;
}


//���� �̾���̴� �Լ�
char* StrCat(char* dest, char* src)
{
	char* ret = dest;
	//��� 1# �ε����� �̿�
	/*
	//int len = StrLen(dest); //0ã��
	
	//int i = 0;
	//while (src[i]) // !=0 �������� ������ �������� 0���� false �������ϱ�
	//{
	//	dest[len + i] = src[i];
	//	i++;
	//}
	//dest[len + i] = 0;
	*/

	//��� 2# �����͸� �̿�
	while (*dest) {
		dest++; //�ϳ��ϳ� �̵��ؼ� ������ 0�� ����Ű����������
	}

	while (*src) {
		*dest = *src; //dest�� ������ 0�� ����Ű���ְ� scr�� ù��°�� ����Ű�������ϱ� 
		dest++;
		src++;
	}

	return ret;
}


int main() {

	//�ؿ��� ���ÿ� �迭 hello�� ���������� �̰� �����Ͱ� ���ÿ� ����ǰ� �װ� ����Ű�� hello�� data������ �����.
	//const�� �پ���ϴ� ������ hello�� ���ϸ� �ȵǴ� ���� data�ȿ� �ֱ� �����̴�.
	//const char* ptr = "hello";

	//char str[] = {'h','e','l','l','o'}; �Ȱ���.
	//'' ����, "" ���ڿ�
	//char str[] = "hello";
	//cout << str << endl;

	
	const int buf_size = 100;
	//[hello0................~]
	//�ظ��ϸ� string �� ����. ���� �̷��� �Ⱦ���. ���� �����
	char a[buf_size] = "hello";
	char b[buf_size] = "world";


	//�̰͵��� ������ ���� ���´ٰ��Ѵ�.
	//���ڿ��̳� �����͸� �̿��� �������� ���� ����

	int len = StrLen(a); // c���� ���� ���� ���� �Լ�

	char c[buf_size];
	StrCpy(c, a);
	cout << c << endl;

	cout << StrCat(a, b) << endl;
}