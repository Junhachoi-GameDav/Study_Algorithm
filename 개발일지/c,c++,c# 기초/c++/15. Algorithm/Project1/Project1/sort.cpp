#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <algorithm>


// 결론적으로 정렬은 O(NlogN)이라고 말할 수 있고 map이 있는데도 굳이 서칭할때 쓰는이유는 인벤토리 기능들 떄문이다.
// 아이템 별로 정렬, 등급별로 정렬등 ui에서 많이쓴다고한다.
// 버튼을 눌러서 정렬 시키는 기능에 들어간다고 보면 된다. O(NlogN)이라서 계속 쓰기엔 무리가 있다.



// O(N^2)
void BubbleSort(vector<int>& v)
{
	const int n = v.size();

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n-1-i; j++)
		{
			if (v[i] > v[j + 1])
				swap(v[j], v[j + 1]);
		}
	}
}

//O(n^2)
void SelectionSort(vector<int>& v)
{
	const int n = v.size();

	for (int i = 0; i < n-1; i++)
	{
		int best_idx = i;

		for (int j = i+1; j < n; j++)
		{
			if (v[j] < v[best_idx])
			{
				best_idx = j;
			}
		}

		if(i != best_idx)
			swap(v[i], v[best_idx]);
	}
}

//O(NlogN)
void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>> pq;//우선순위 큐
	
	//O(NlogN)
	for (int num : v)
	{
		pq.push(num);
	}
	v.clear();

	//O(NlogN)
	while (pq.empty() == false)
	{
		v.push_back(pq.top());	//O(1)
		pq.pop();				//O(logN)
	}
}


// 병합 정렬(중요~!) (크래프톤 코테에 나왔다고함) 이거 많이 쓴다고함
// 분할 정복이란것을 이용함
// - 분할 (Divide)		큰문제를 나누어서 간단하게 만듬
// - 정복 (Conquer)		분할된 문제를 해결
// - 결합 (Combine)		결과를 취합후 마무리

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int left_idx = left;
	int right_idx = mid + 1;

	vector<int> temp;

	while (left_idx <= mid && right_idx <= right) //집어넣어줌
	{
		if (v[left_idx] <= v[right_idx])
		{
			temp.push_back(v[left_idx]);
			left_idx++;
		}
		else
		{
			temp.push_back(v[right_idx]);
			right_idx++;
		}
	}

	if (left_idx > mid) //왼쪽이 먼저 끝나면
	{
		while (right_idx <= mid)
		{
			temp.push_back(v[right_idx]);
			right_idx++;
		}
	}
	else
	{
		while (left_idx <= mid)
		{
			temp.push_back(v[left_idx]);
			left_idx++;
		}
	}
	//임시로들고있던 모든 데이터 temp를 덮어씌움
	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

//O(NlogN)
void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right) return;

	int mid = (left + right) / 2;

	MergeSort(v, left, mid); //재귀로 다시 나눔
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right);
}


// 퀵 정렬
// 강의봐~

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right&& pivot>= v[low])
		{
			low++;
		}

		while (high >= left +1 && pivot <= v[high])
		{
			high--;
		}

		if (low < high) {
			swap(v[low], v[high]);
		}
	}

	swap(v[left], v[high]);
	return high;
}

// O(NlogN) 최악일땐=pivot값이 제일 작거나 할때 O(N^2) 되기도한다.
void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right) { return; }

	int pivot = Partition(v, left, right);

	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot + 1, right);
}

int main() {
	vector<int> v{1, 5, 4, 2, 3};

	//BubbleSort(v);
	//SelectionSort(v);
	//HeapSort(v);
	//MergeSort(v, 0, v.size()-1);
	QuickSort(v, 0, v.size() - 1);
}