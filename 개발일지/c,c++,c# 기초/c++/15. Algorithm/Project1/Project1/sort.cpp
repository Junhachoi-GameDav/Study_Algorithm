#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <algorithm>


// ��������� ������ O(NlogN)�̶�� ���� �� �ְ� map�� �ִµ��� ���� ��Ī�Ҷ� ���������� �κ��丮 ��ɵ� �����̴�.
// ������ ���� ����, ��޺��� ���ĵ� ui���� ���̾��ٰ��Ѵ�.
// ��ư�� ������ ���� ��Ű�� ��ɿ� ���ٰ� ���� �ȴ�. O(NlogN)�̶� ��� ���⿣ ������ �ִ�.



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
	priority_queue<int, vector<int>, greater<int>> pq;//�켱���� ť
	
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


// ���� ����(�߿�~!) (ũ������ ���׿� ���Դٰ���) �̰� ���� ���ٰ���
// ���� �����̶����� �̿���
// - ���� (Divide)		ū������ ����� �����ϰ� ����
// - ���� (Conquer)		���ҵ� ������ �ذ�
// - ���� (Combine)		����� ������ ������

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int left_idx = left;
	int right_idx = mid + 1;

	vector<int> temp;

	while (left_idx <= mid && right_idx <= right) //����־���
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

	if (left_idx > mid) //������ ���� ������
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
	//�ӽ÷ε���ִ� ��� ������ temp�� �����
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

	MergeSort(v, left, mid); //��ͷ� �ٽ� ����
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right);
}


// �� ����
// ���Ǻ�~

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

// O(NlogN) �־��϶�=pivot���� ���� �۰ų� �Ҷ� O(N^2) �Ǳ⵵�Ѵ�.
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