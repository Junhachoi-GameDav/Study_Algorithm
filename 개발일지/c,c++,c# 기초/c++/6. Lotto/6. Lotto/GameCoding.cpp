#include <iostream>
using namespace std;


//나열 알고리즘을 사용할것임

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//나열한다는 뜻 //버블 솔트 라는 방식을 사용
void Sort(int* number, int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - 1; j++) //제일큰수가 뒤에올거니까 count -1해준다.
		{
			if (number[j] > number[j + 1])
			{
				Swap(number[j], number[j + 1]);
			}
		}
	}
	
}

void ChooseLotto(int* number) 
{
	int count = 0;

	while (count != 6) {
		// 1+ 0~44 = 1~45
		int rand_value = 1 + rand() % 45;

		//이미 찾은 값인지
		bool found = false;

		for (int i = 0; i < count; i++)
		{
			if (number[i] == rand_value)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			number[count] = rand_value;
			count++;
		}
	}

	Sort(number, 6);
}


int main() {

	srand((unsigned)time(0)); //랜덤 번호 = 진짜 랜덤이 아니니까 타임을 넣어줘서 랜덤하게 바꿈

	int lotto[6] = { 1,42,15,3,5,6 };

	ChooseLotto(lotto);

	for (int i = 0; i < 6; i++)
	{
		cout << lotto[i] << " ";
	}
}