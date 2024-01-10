// 레드블랙 트리를 기반으로 만든 키와 밸류 값을 가진 함수
// vector 와 list 와 map을 제일 많이 쓴다고 한다.
// map 과 set 이 거의 세트인데 map부터 알면 된다.
// pair = pair<first, second> p; 두개를 하나의 변수로 쓴다는 얘기임

#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <map>

//플레이어가 있다 가정
class Player
{
public:
	Player() : _id(0) {}
	Player(int id) : _id(id) {}

	int _id;
};

//pair 내부는 그냥 이런 형태임
template<typename T, typename U>
struct Pair
{
	T first;
	U second;
};

template<typename T, typename U>
auto MakePair(T first, U second)
{
	return pair<T, U>(first, second);
}


// C++ vector	= C# List		이고
// C++ list		= C# LinkedList 이고(이것도 거의 사용안함)
// C++ map		= 없음 (dictionary만 사용함)
// C++ hash_map	= C# Dictionary 이다.
// hash_map은 옛날 이름 지금은 unordered_map 이다.

/*
int main() {
	vector<Player*> v;
	v.push_back(new Player(100));
	v.push_back(new Player(200));
	v.push_back(new Player(500));
	v.push_back(new Player(300));
	v.push_back(new Player(400));
	// 플레이어를 넣는다 가정할때 삽입 삭제하기가 어렵다
	// *포인터로 놓으면 8비트만 가져가니까 많이 이렇게 한다. 계속 백터<int>만 쓰진 않으니까
	//이진탐색은 데이터가 정렬 되어있어야하는데 그렇지않다.


	//map (키, 밸류)
	map<int, Player*> m;

	// 추가
	// 찾기
	// 삭제
	// 순회

	pair<int, Player*> p;

	//추가
	for (Player* p : v)
	{
		//int key = p->_id;
		//Player* data = p;
		//pair<int, Player*>(key, data)
		//make_pair(key, data); //굳이 위에처럼 안해도 됨 auto와 template의 콤보
		m.insert(make_pair(p->_id, p));
	}

	//찾기
	auto it = m.find(300);
	//int key = (*it).first;
	//int key = it->first;
	//Player* player = (*it).second;
	//Player* player = it->second;
	if (it != m.end())
	{
		int key = it->first;
		Player* player = it->second;
		cout << "찾음";
	}
	else
	{
		cout << "없음";
	}

	
	Player* p = m[100]; //100의 키의 밸류를 가져와 달라는 뜻 // 쉽고 좋아서 이거 많이쓴다고함
	//주의할점 = m[1000]과 같이 없는 키값을 가져오면 새로만든다...
	//c++에선 새로 만들기 때문에 의도치않은 키가 생길수도 있다. 물론 이걸 이용할수도 있지만...
	// 근데 얼리얼 TMap에서는 없으면 크래쉬가 남...
	// STL 함수랑 언리얼 함수랑 비슷한데 다른것도 많아서 유심히 사용해야한다.


	//삭제
	//m.erase(it);
	m.erase(200);

	//순회 _백터가 더 깔끔하긴함. 보통 백터로 배열관리를 하고 map으로 탐색을 많이함
	for (auto it = m.begin(); it != m.end(); it++)
	{
		int key = it->first;
		Player* p = it->second;
	}
}
*/