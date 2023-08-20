#include<iostream>
using namespace std;

int StrLen(const char* str)
{
	int i = 0;

	//*(str+i) == srt[i]   포인터와 배열은 종이한장차이라고한다.
	while (str[i] != 0)
	{
		i++;
	}

	return i;
}

//복사하는 함수
char* StrCpy(char* dest, char* src)
{
	char* ret = dest;  //ret에 dest를 넣기

	/*
	인덱스 방식
	int i = 0;
	while (src[i] != 0) 
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0; //마지막 0은 복사가 안됐으므로
	*/

	//포인터를 이용하는 방법  // 핵심 
	while (*src != 0) 
	{
		*dest = *src;
		dest++; //char 타입이라서 1파이트 옮김 즉 다음 문자
		src++;
	}
	*dest = 0;

	return ret;
}


//끝에 이어붙이는 함수
char* StrCat(char* dest, char* src)
{
	char* ret = dest;
	//방법 1# 인덱스를 이용
	/*
	//int len = StrLen(dest); //0찾음
	
	//int i = 0;
	//while (src[i]) // !=0 생략가능 어차피 마지막에 0보고 false 내보내니까
	//{
	//	dest[len + i] = src[i];
	//	i++;
	//}
	//dest[len + i] = 0;
	*/

	//방법 2# 포인터를 이용
	while (*dest) {
		dest++; //하나하나 이동해서 마지막 0을 가리키고있을거임
	}

	while (*src) {
		*dest = *src; //dest는 마지막 0을 가르키고있고 scr는 첫번째를 가르키고있으니까 
		dest++;
		src++;
	}

	return ret;
}


int main() {

	//밑에는 스택에 배열 hello를 저장했지만 이건 포인터가 스택에 저장되고 그걸 가리키는 hello는 data영역에 저장됨.
	//const가 붙어야하는 이유는 hello가 변하면 안되는 정적 data안에 있기 때문이다.
	//const char* ptr = "hello";

	//char str[] = {'h','e','l','l','o'}; 똑같다.
	//'' 문자, "" 문자열
	//char str[] = "hello";
	//cout << str << endl;

	
	const int buf_size = 100;
	//[hello0................~]
	//왠만하면 string 을 쓰자. 요즘 이렇게 안쓴다. 옛날 방식임
	char a[buf_size] = "hello";
	char b[buf_size] = "world";


	//이것들이 면접에 자주 나온다고한다.
	//문자열이나 포인터를 이용한 문제들이 많이 나옴

	int len = StrLen(a); // c에서 문자 갯수 세는 함수

	char c[buf_size];
	StrCpy(c, a);
	cout << c << endl;

	cout << StrCat(a, b) << endl;
}