#include <iostream>
using namespace std;
#include <vector>
#include <queue>


//��� �������� ��� Ʈ��(�켱���� ť) �� �ð� ���⵵�� ������
//functer �̷������ε� �����ϴ�.
template <typename T, typename Predicate = less<T>>
class PriorityQueue
{
public:

	// �迭 ��� ����
	// i�� ����� ���� �ڽ��� [(2 * i) +1]
	// i�� ����� ������ �ڽ��� [(2 * i) +2]
	// i�� ����� �θ��  [(i - 1) /2]

	// �ð� ���⵵ �ݳ�����ݳ������� �׷��� �׳� logN�̶�� �˸� ��
	// O(NlogN)  = ������ ���� �ٲ�⶧���� 
	void push(const T& data)
	{
		// �켱 �� �������� �����ش�. �迭�� �������� ���ο� �� �ֱ�
		_heap.push_back(data);

		// �������ó�� ū���� ����
		int now = static_cast<int>(_heap.size()) - 1; // ���� ������ ���

		while (now > 0)
		{
			//�θ���� ���ؼ� ������ �׸��ϱ�
			int next = (now - 1) / 2; //�θ� ���
			
			//if (_heap[now] < _heap[next]) { break; }
			if (_predicate(_heap[now], _heap[next])) { break; }

			//������ ��ü
			::swap(_heap[now], _heap[next]);
			now = next; //�ε��� ��ü
		}
	}

	// O(NlogN)
	void pop()
	{
		_heap[0] = _heap.back(); //�������� ��(��ó��)�� �ű��
		_heap.pop_back(); //������ ������ pop(����)

		int now = 0;

		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;

			if (left >= (int)_heap.size()) { break; } //�������� ��尡 ������

			int next = now;

			//���ʺ�
			if (_heap[next] < _heap[left]) { next = left; }

			//������ �� �� �ֳ����� Ȯ��
			//if (right < _heap.size() && _heap[next] < _heap[right]) { next = right; }
			if (right < _heap.size() && _predicate(_heap[next], _heap[right])) { next = right; }

			// ����/������ �� �� ���� ������ ������ ����
			if (next == now) { break; }

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	// O(1)
	T& top() //���� ū�� 
	{
		return _heap[0];
	}
	// O(1)
	bool empty()
	{
		return _heap.empty();
	}

private:
	vector<T> _heap; //���⿡ �����͸� ����
	Predicate _predicate;
};

int main()
{
	vector<int> v;
	// less �Ǵ� greater ������ �ٲ㼭 ���Ҽ��� �ִ�.
	PriorityQueue<int , greater<int>> pq;


	//���� �������� ���ϴ� ����� �׳� ������ ������ ���� �������� ���� -10�� ���� ũ�ϱ�
	pq.push(10);
	pq.push(20);
	pq.push(50);
	pq.push(40);
	pq.push(30);


	int value = pq.top();
	pq.pop();
}