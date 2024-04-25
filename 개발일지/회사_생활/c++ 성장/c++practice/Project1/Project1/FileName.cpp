#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

std::atomic<int> sum = 0; // �̰����� �߰����¿��� ������� �ʴ´�.
// �Ϲݺ������� 100�� �̻� ���ſ� ���� ��������
// ����ó���� ���� �ȹٲ�������ϴ� �������� �����

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

	//t.join(); //����ȭ
	/*for (auto& it : threads)
		it.join();*/


	// atomic ����
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