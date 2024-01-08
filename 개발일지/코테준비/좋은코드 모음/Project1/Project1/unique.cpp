// 중복된 요소를 제거하는 로직 = 코테에서 정말 많이 나오는 로직이다.

//#map 이라는 함수를 사용한 방법
//#include <bits/stdc++.h>
//using namespace std;
//
//map<int, int> mp;
//
//int main() {
//	vector<int> v{1, 1, 2, 2, 3, 3};
//	for (int i : v)
//	{
//		if (mp[i]) { continue; }
//		else { mp[i] = 1; }
//	}
//
//	vector<int> ret;
//	for (auto it : mp)				//auto stl에 있는 tempelte같은 거
//	{
//		ret.push_back(it.first);	//map(first, second) 키와 밸류
//	}
//
//	for (int i : ret) { cout << i << "\n"; }
//}

//#unique 라는 함수를 사용한 방법
//중복되는것을 없애고 앞에 정열한뒤 배열뒤에는(배열 크기는 변하지 않으므로) 아무거나 집어넣는 함수이다.
//정렬이 되지 않기 때문에 sort()와 같이 써준다. 그후 erase로 뒷부분 없애주면 끝~~~
#include <bits/stdc++.h>
using namespace std;

int main() {
	
	vector<int> v{2,2, 1, 1, 2, 2, 3, 3,5,6,7,8,9}; //
	sort(v.begin(), v.end());						// 정렬
	v.erase(unique(v.begin(), v.end()), v.end());	// 중복되는것을 없앤후 그 마지막 지점부터 배열 끝까지를 제거


	for (int i : v) { cout << i << " "; }
	cout << '\n';
	return 0;
}