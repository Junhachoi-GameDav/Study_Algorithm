#include <iostream>
using namespace std;


//���� �˰����� ����Ұ���

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//�����Ѵٴ� �� //���� ��Ʈ ��� ����� ���
void Sort(int* number, int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - 1; j++) //����ū���� �ڿ��ðŴϱ� count -1���ش�.
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

		//�̹� ã�� ������
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

	srand((unsigned)time(0)); //���� ��ȣ = ��¥ ������ �ƴϴϱ� Ÿ���� �־��༭ �����ϰ� �ٲ�

	int lotto[6] = { 1,42,15,3,5,6 };

	ChooseLotto(lotto);

	for (int i = 0; i < 6; i++)
	{
		cout << lotto[i] << " ";
	}
}