#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <queue>
#include <windows.h>

//���� ��ȹ�� (dynamic programming)
// �ΰ����ɿ��� ���� ����ϴ� �˰����̶�� �Ѵ�. 
// �ߴ� �۾����̳� �ߺ��Ǵ°��� �������� �ѹ������Ѱ��� �̸� ĳ���Ͽ�(��ġ ������Ʈ Ǯ�� ���� ������)
// ���� �ӵ��� �������� �����ϴ°��̴�.
// ��û �����Ұ� �������� �������� ����... �˰����� �������Ѱ͵��� ���Ƽ� �׷���



// ĳ���� �ϴ� ����� �޸������̼�(memoization) �̶�� �Ѵ�.
//int cache[50][50];
//
//int Combination(int n, int r)
//{
//	//���� ���
//	if (r == 0 || n == r)
//	{
//		return 1;
//	}
//
//	//�̹� ���� ������ ������ �ٷ� ��ȯ
//	int& ret = cache[n][r];
//	if (ret != -1)
//		return ret;
//
//	return ret = Combination(n - 1, r - 1) + Combination(n - 1, r);
//}


//test ����
// ��ȭ�� 1+ 2+ 3+ ������ 3���� ��ȭ�� ������
// 
// 9+ ������ ����Ǽ� 
int N = 9;
int cache[100] = { -1 };
int Enchant(int num)
{
	// �������
	if (num > N)
		return 0;
	if (num == N)
		return 1;


	// ĳ��
	int& ret = cache[num];
	if (ret != -1)
		return ret;

	// ����
	return ret = Enchant(num + 1) + Enchant(num + 2) + Enchant(num + 3);
}


int main() {

	//memset(cache, -1, sizeof(cache)); // -1�� ���� �о� �ְڴٴ� ��

	//__int64 start = GetTickCount64(); //�ð�

	//int lotto = Combination(45, 6);

	//__int64 end = GetTickCount64();

	//cout << end - start << "ms";

	int ret = Enchant(0);
	cout << ret;

}