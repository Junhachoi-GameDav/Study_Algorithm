
// 순열
#include <bits/stdc++.h>
using namespace std;
/*
int main() {
	
	//int a[] = { 1,2,3 };
	//vector<int> a = { 1,2,3 }; //정렬이 되어있어야함
	vector<int> a = { 2,1,3 };
	sort(a.begin(), a.end()); // 오름차순

	do {
		for (int i : a) { cout << i << " "; }
		cout << "\n";
		//next_permutation(&a[0], &a[0] + 3)
	} while (next_permutation(a.begin(), a.end()));

	//next_permutation
	// (시작 지점, 끝 지점(+1)) // 1,2,3 일때 0, 1, 2, 3번째 배열을 넣어야함
	// 오름차순을 기반을 순열을 만드는 함수

	return 0;
}
*/

vector<int> v;
void print_v(vector<int>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

//너비탐색 (bfs)처럼 재귀함수 순열 만들기
void make_permutation(int n, int r, int depth)
{
	cout << n << " : " << r << " : " << depth << endl;
	if (r == depth)
	{
		print_v(v);
		return;
	}
	for (int i = depth; i < n; i++)
	{
		swap(v[i], v[depth]);
		make_permutation(n, r, depth + 1);
		swap(v[i], v[depth]);
	}
	return;
}

int main() {

	//vector<int> a = { 1,2,3 }; 똑같음
	for (int i = 1; i <= 3; i++)
	{
		v.push_back(i);
	}
	make_permutation(3, 3, 0);
	return 0;
}