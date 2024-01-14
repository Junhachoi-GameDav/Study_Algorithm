#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n, k, ret= 100000 * -100 + 1; //ÃÖ¼Ò°ª
	int arr[100001];
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
		arr[i] = arr[i - 1] + arr[i];
	}

	for (int i = k; i <= n; i++)
	{
		ret = max(ret, arr[i] - arr[i - k]);
	}
	cout << ret;
	return 0;
}