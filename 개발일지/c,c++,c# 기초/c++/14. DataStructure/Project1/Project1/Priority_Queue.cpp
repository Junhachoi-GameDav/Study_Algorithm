#include <iostream>
using namespace std;
#include <vector>
#include <queue>


//기술 면접으로 물어봄 트리(우선순위 큐) 의 시간 복잡도와 그이유
//functer 이런식으로도 가능하다.
template <typename T, typename Predicate = less<T>>
class PriorityQueue
{
public:

	// 배열 노드 공식
	// i번 노드의 왼쪽 자식은 [(2 * i) +1]
	// i번 노드의 오른쪽 자식은 [(2 * i) +2]
	// i번 노드의 부모는  [(i - 1) /2]

	// 시간 복잡도 반나누고반나눠지고 그러면 그냥 logN이라고 알면 됨
	// O(NlogN)  = 높히에 따라 바뀌기때문에 
	void push(const T& data)
	{
		// 우선 힙 구조부터 맞춰준다. 배열의 마지막에 새로운 값 넣기
		_heap.push_back(data);

		// 도장깨기처럼 큰수가 위로
		int now = static_cast<int>(_heap.size()) - 1; // 가장 마지막 노드

		while (now > 0)
		{
			//부모노드와 비교해서 작으면 그만하기
			int next = (now - 1) / 2; //부모 노드
			
			//if (_heap[now] < _heap[next]) { break; }
			if (_predicate(_heap[now], _heap[next])) { break; }

			//데이터 교체
			::swap(_heap[now], _heap[next]);
			now = next; //인덱스 교체
		}
	}

	// O(NlogN)
	void pop()
	{
		_heap[0] = _heap.back(); //마지막을 위(맨처음)로 옮기기
		_heap.pop_back(); //마지막 데이터 pop(삭제)

		int now = 0;

		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;

			if (left >= (int)_heap.size()) { break; } //마지막에 노드가 없을시

			int next = now;

			//왼쪽비교
			if (_heap[next] < _heap[left]) { next = left; }

			//오른쪽 비교 및 있나없나 확인
			//if (right < _heap.size() && _heap[next] < _heap[right]) { next = right; }
			if (right < _heap.size() && _predicate(_heap[next], _heap[right])) { next = right; }

			// 왼쪽/오른쪽 둘 다 현재 값보다 작으면 종료
			if (next == now) { break; }

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	// O(1)
	T& top() //제일 큰값 
	{
		return _heap[0];
	}
	// O(1)
	bool empty()
	{
		return _heap.empty();
	}

private:
	vector<T> _heap; //여기에 데이터를 넣음
	Predicate _predicate;
};

int main()
{
	vector<int> v;
	// less 또는 greater 등으로 바꿔서 구할수도 있다.
	PriorityQueue<int , greater<int>> pq;


	//제일 작은수를 구하는 방법은 그냥 음수로 넣으면 제일 작은수가 나옴 -10이 제일 크니까
	pq.push(10);
	pq.push(20);
	pq.push(50);
	pq.push(40);
	pq.push(30);


	int value = pq.top();
	pq.pop();
}