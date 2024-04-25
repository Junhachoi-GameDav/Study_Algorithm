#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

std::atomic<int> sum = 0; // 이것으로 중간상태에서 끼어들지 않는다.
// 일반변수보다 100배 이상 무거움 전부 쓰지마라
// 병렬처리로 인해 안바뀌었으면하는 변수에만 쓰면됨

void Add()
{
	for (int i = 0; i < 100'0000; i++)
	{
		sum++;
	}
}

void Sub()
{
	for (int i = 0; i < 100'0000; i++)
	{
		sum--;
	}
}

//void HelloTheard(int i)
//{
//	while (true)
//	{
//		std::cout << "hello Thread" << i << '\n';
//	}
//}

int main() {

	/*std::vector<std::thread> threads;
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(std::thread(HelloTheard, i));
	}*/

	//std::cout << "hello main" << '\n';
	
	//t.detach();

	//t.join(); //동기화
	/*for (auto& it : threads)
		it.join();*/


	// atomic 사용법
	// int temp = sum;
	int temp = sum.load();

	// sum = 10
	sum.store(10);

	std::thread t1(Add);
	std::thread t2(Sub);

	t1.join();
	t2.join();

	std::cout << sum << std::endl;
}