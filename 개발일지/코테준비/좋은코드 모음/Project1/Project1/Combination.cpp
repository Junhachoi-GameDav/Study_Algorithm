// 조합 만드는 재귀함수
// 조합 + 중첩 벡터 + 3중 포문

// for 문에서 
// auto는 시간이 느릴수가 있음


#include <bits/stdc++.h>
using namespace std;

int n, m, arr[54][54], result = 99999999;
vector<vector<int>> ch_list;
vector<pair<int, int>> home, chicken;

void combi(int start, vector<int> v)
{
	if (v.size() == m) {
		ch_list.push_back(v);
		return;
	}
	for (int i = start + 1; i < chicken.size(); i++)
	{
		v.push_back(i);
		combi(i, v);
		v.pop_back();
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arr[i][j];
			if (arr[i][j] == 1)
				home.push_back({ i,j });
			if (arr[i][j] == 2)
				chicken.push_back({ i,j });
		}
	}

	vector<int> v;
	combi(-1, v);

	for (vector<int> c_l : ch_list)
	{
		int ret = 0;
		for (pair<int, int> h : home)
		{
			int _min = 987654321;
			for (int ch : c_l)
			{
				int dist = abs(h.first - chicken[ch].first) + abs(h.second - chicken[ch].second);
				_min = min(_min, dist);
			}
			ret += _min;
		}
		result = min(result, ret);
	}
	cout << result << '\n';

	return 0;
}