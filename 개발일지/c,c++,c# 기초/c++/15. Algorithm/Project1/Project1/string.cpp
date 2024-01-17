#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

// 로그인할때 문자들을 비교한다던가 생각보다 쓸일이 많다.

//
//int main() {
//
//	string str = "wwww";
//	string str2 = "wwww";
//
//
//	//비교
//	if (str == str2) {}
//	str.compare(str2); // 1 or 0
//
//	//복사
//	string str3;
//	str3 = str;
//
//	//추가
//	// 계정을 지우면 진짜로 지우는게 아니라 케릭터 이름에
//	// wwww_DELETED 이런식으로 플레그를 만들어놓는다. 복원하기 위해서
//	str.append("123");
//	str += "123";
//
//	//찾기
//	auto c = str.find("ww"); //몇번째인지 인덱스를 뱉어줌
//	if (c == string::npos) // 끝까지 못찾았다면(없다면) vector에 !=v.end() 같은 느낌임
//	{
//		cout << "no found";
//	}
//
//	//교체
//	// 근데 자주쓸일이 없어서 까먹으면 그냥 구글 검색하고 만든다고한다. 
//	string chat_str = "SHIT~~!!";
//	string find_str = "SHIT";
//	string replace_str = "****";
//
//	chat_str.replace(chat_str.find(find_str), find_str.length(), replace_str);
//
//
//	// 멀티바이트와 유니코드
//	// 영어로만 서비스하면 몰라도 한글이 깨지거나 할수있다. 
//
//	// 1) ASCII 코드(아스키) -> 영어만 고려
//	// 7BIT (0 ~ 127) 128개까지 표현 가능
//
//
//	// 2) ANSI
//	// ASCII + 각국언어별로 128개
//	// CP949(한국어)
//	// 단점 : 환경마다 다르게 나옴
//
//	// 3) 유니코드 (동일한 문자 = 동일한 번호 = 동일한 유니코드)
//	// 인코딩 (utf8, utf16) 
//	// - utf8	: 영어(1) , 한국어/중국어(3) ~~
//	// - utf16	: 영어(2), 한국어(2), 중국어 (2) ~~
//
//	// 4) MBCS(Multi Byte Charactor Set)  VS   WBCS(Wide Byte Charactor Set)
//	// - MBCS - 멀티바이트 집합 = 가변길이 인코딩을 뜻함 (UTF-8이 대표적 왔다 갔다 해야하니까)
//	// - WBCS - 유니코드 집합	= 고정길이 인코딩 (UTF-16) 주의* 유니코드는 인코딩들을 뜻하는거지 고정길이인것은 아니다.
//
//	setlocale(LC_ALL, ""); //기본설정(위도우 언어)
//	cout << setlocale(LC_ALL, NULL);
//
//	const char* test = "aaa한글"; // 영어는 1바이트이지만 한글은 2바이트 이상이라 char변수에 넣는거 부터가 틀린 얘기다
//
//	auto test2 = u8"aaa한글"; //utf8 로 하겠다는뜻
//	setlocale(LC_ALL, "en_US.UTF-8"); //이설정이여야 안깨짐
//
//	auto test3 = u"aaa한글입니다"; //u는 utf16임
//
//	//보통 utf-16을 많이 쓴다고함
//	//유니티/언리얼도 이방식을 많이씀
//	//c#도 char가 2바이트임 그래서 신경 안써도 되지만 c++은 아니야~ 하나하나 만져줘야됨
//	wchar_t ch = L'한'; //wbcs
//	wstring s = L"aaa한글입니다.";
//	wcout << s << endl;
//}