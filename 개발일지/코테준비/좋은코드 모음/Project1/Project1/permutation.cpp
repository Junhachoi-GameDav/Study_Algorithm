//#include <bits/stdc++.h>
//using namespace std;
//// 순열
///*
//int main() {
//	
//	//int a[] = { 1,2,3 };
//	//vector<int> a = { 1,2,3 }; //정렬이 되어있어야함
//	vector<int> a = { 2,1,3 };
//	sort(a.begin(), a.end()); // 오름차순
//
//	do {
//		for (int i : a) { cout << i << " "; }
//		cout << "\n";
//		//next_permutation(&a[0], &a[0] + 3)
//	} while (next_permutation(a.begin(), a.end()));
//
//	//next_permutation
//	// (시작 지점, 끝 지점(+1)) // 1,2,3 일때 0, 1, 2, 3번째 배열을 넣어야함
//	// 오름차순을 기반을 순열을 만드는 함수
//
//	return 0;
//}
//*/
//
//vector<int> v;
//void print_v(vector<int>& v)
//{
//	for (int i = 0; i < v.size(); i++)
//	{
//		cout << v[i] << " ";
//	}
//	cout << endl;
//}
//
////너비탐색 (bfs)처럼 재귀함수 순열 만들기
//void make_permutation(int n, int r, int depth)
//{
//	cout << n << " : " << r << " : " << depth << endl;
//	if (r == depth)
//	{
//		print_v(v);
//		return;
//	}
//	for (int i = depth; i < n; i++)
//	{
//		swap(v[i], v[depth]);
//		make_permutation(n, r, depth + 1);
//		swap(v[i], v[depth]);
//	}
//	return;
//}
//
//// 조합
//// 이것을 구현할려면 3중 포문으로 구현해야함...ㅎㄷㄷ
////조건 의 갯수에 따라서 포문이 느는것임. k =2 면 2중포문
//int n = 5, k = 3; //1,2,3,4,5 //조건 3조합
//void print_test(vector<int> b)
//{
//	for (int i : b) { cout << i << " "; }
//	cout << "\n";
//}
//void Combi(int start, vector<int> b)
//{
//	if (b.size() == k)
//	{
//		print_test(b);
//		return; //재귀함수라서 프린트하고 멈춤
//	}
//	for (int i = start + 1; i < n; i++)
//	{
//		b.push_back(i);
//		Combi(i, b); //return으로 멈춘다고해서 밑에꺼가 안실행되는게 아님 조건에 걸린 combi만 실행안되고 이 포문에 걸린건 실행됨
//		b.pop_back(); //포문에 들어오긴 했으니까 실행을함
//	}
//}
//
//int main() {
//
//	//vector<int> a = { 1,2,3 }; 똑같음
//	/*for (int i = 1; i <= 3; i++)
//	{
//		v.push_back(i);
//	}
//	make_permutation(3, 3, 0);*/
//
//	vector<int> b;
//	Combi(-1, b);
//	return 0;
//}