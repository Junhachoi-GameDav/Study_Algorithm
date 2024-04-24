#include <iostream>
#include <thread>
#include <vector>

void HelloTheard(int i)
{
	while (true)
	{
		std::cout << "hello Thread" << i << '\n';
	}
}

int main() {

	std::vector<std::thread> threads;
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(std::thread(HelloTheard, i));
	}

	std::cout << "hello main" << '\n';
	
	//t.detach();

	//t.join(); //µ¿±âÈ­
	for (auto& it : threads)
		it.join();
}