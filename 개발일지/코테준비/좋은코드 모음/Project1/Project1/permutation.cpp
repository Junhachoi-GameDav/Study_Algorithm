//#include <bits/stdc++.h>
//using namespace std;
//// ����
///*
//int main() {
//	
//	//int a[] = { 1,2,3 };
//	//vector<int> a = { 1,2,3 }; //������ �Ǿ��־����
//	vector<int> a = { 2,1,3 };
//	sort(a.begin(), a.end()); // ��������
//
//	do {
//		for (int i : a) { cout << i << " "; }
//		cout << "\n";
//		//next_permutation(&a[0], &a[0] + 3)
//	} while (next_permutation(a.begin(), a.end()));
//
//	//next_permutation
//	// (���� ����, �� ����(+1)) // 1,2,3 �϶� 0, 1, 2, 3��° �迭�� �־����
//	// ���������� ����� ������ ����� �Լ�
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
////�ʺ�Ž�� (bfs)ó�� ����Լ� ���� �����
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
//// ����
//// �̰��� �����ҷ��� 3�� �������� �����ؾ���...������
////���� �� ������ ���� ������ ���°���. k =2 �� 2������
//int n = 5, k = 3; //1,2,3,4,5 //���� 3����
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
//		return; //����Լ��� ����Ʈ�ϰ� ����
//	}
//	for (int i = start + 1; i < n; i++)
//	{
//		b.push_back(i);
//		Combi(i, b); //return���� ����ٰ��ؼ� �ؿ����� �Ƚ���Ǵ°� �ƴ� ���ǿ� �ɸ� combi�� ����ȵǰ� �� ������ �ɸ��� �����
//		b.pop_back(); //������ ������ �����ϱ� ��������
//	}
//}
//
//int main() {
//
//	//vector<int> a = { 1,2,3 }; �Ȱ���
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