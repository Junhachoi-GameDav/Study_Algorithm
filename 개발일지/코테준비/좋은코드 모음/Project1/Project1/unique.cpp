// �ߺ��� ��Ҹ� �����ϴ� ���� = ���׿��� ���� ���� ������ �����̴�.

//#map �̶�� �Լ��� ����� ���
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
//	for (auto it : mp)				//auto stl�� �ִ� tempelte���� ��
//	{
//		ret.push_back(it.first);	//map(first, second) Ű�� ���
//	}
//
//	for (int i : ret) { cout << i << "\n"; }
//}

//#unique ��� �Լ��� ����� ���
//�ߺ��Ǵ°��� ���ְ� �տ� �����ѵ� �迭�ڿ���(�迭 ũ��� ������ �����Ƿ�) �ƹ��ų� ����ִ� �Լ��̴�.
//������ ���� �ʱ� ������ sort()�� ���� ���ش�. ���� erase�� �޺κ� �����ָ� ��~~~
#include <bits/stdc++.h>
using namespace std;

int main() {
	
	vector<int> v{2,2, 1, 1, 2, 2, 3, 3,5,6,7,8,9}; //
	sort(v.begin(), v.end());						// ����
	v.erase(unique(v.begin(), v.end()), v.end());	// �ߺ��Ǵ°��� ������ �� ������ �������� �迭 �������� ����


	for (int i : v) { cout << i << " "; }
	cout << '\n';
	return 0;
}