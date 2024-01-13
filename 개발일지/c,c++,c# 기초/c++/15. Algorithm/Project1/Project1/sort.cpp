#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <algorithm>

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

void HeapSort(vector<int>& v)
{

}

int main() {
	vector<int> v{1, 5, 4, 2, 3};

}