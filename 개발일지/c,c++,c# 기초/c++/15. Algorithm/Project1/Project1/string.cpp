#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

// 로그인할때 문자들을 비교한다던가 생각보다 쓸일이 많다.


int main() {

	string str = "wwww";
	string str2 = "wwww";


	//비교
	if (str == str2) {}
	str.compare(str2); // 1 or 0

	//복사
	string str3;
	str3 = str;

	//추가
	// 계정을 지우면 진짜로 지우는게 아니라 케릭터 이름에
	// wwww_DELETED 이런식으로 플레그를 만들어놓는다. 복원하기 위해서
	str.append("123");
	str += "123";

	//찾기
	auto c = str.find("ww"); //몇번째인지 인덱스를 뱉어줌
	if (c == string::npos) // 끝까지 못찾았다면(없다면) vector에 !=v.end() 같은 느낌임
	{
		cout << "no found";
	}

	//교체
	// 근데 자주쓸일이 없어서 까먹으면 그냥 구글 검색하고 만든다고한다. 
	string chat_str = "SHIT~~!!";
	string find_str = "SHIT";
	string replace_str = "****";

	chat_str.replace(chat_str.find(find_str), find_str.length(), replace_str);


	// 멀티바이트와 유니코드
	// 영어로만 서비스하면 몰라도 한글이 깨지거나 할수있다. 
}