//½ºÅØ ÇÏ¸é Â¦Áþ±â, Æø¹ß

//#include <bits/stdc++.h>
//using namespace std;
//
//int n, arr[1000004], ret[1000004];
//stack<int> s;
//
//int main() {
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL); cout.tie(NULL);
//
//	cin >> n;
//	memset(ret, -1, sizeof(ret));
//	for (int i = 0; i < n; i++)
//	{
//		cin >> arr[i];
//		while (s.size() && arr[s.top()] < arr[i])
//		{
//			ret[s.top()] = arr[i];
//			s.pop();
//		}
//		s.push(i);
//	}
//	for (int i = 0; i < n; i++)
//		cout << ret[i] << " ";
//	return 0;
//}

//
//#include <bits/stdc++.h>
//using namespace std;
//
//int main() {
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL); cout.tie(NULL);
//	int t;
//	string s;
//	cin >> t;
//	for (int i = 0; i < t; i++)
//	{
//		cin >> s;
//		stack<char> st;
//		for (auto it : s)
//		{
//			if (s[0] == ')') break;
//			if (st.size() && st.top() != it && it == ')')
//				st.pop();
//			else
//				st.push(it);
//		}
//
//		if (st.size() == 0 && s[0] != ')')
//			cout << "YES" << '\n';
//		else
//			cout << "NO" << '\n';
//	}
//
//	return 0;
//}