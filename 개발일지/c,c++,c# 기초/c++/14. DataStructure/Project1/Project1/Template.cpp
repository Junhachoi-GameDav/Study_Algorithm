#include <iostream>
using namespace std;

// 함수		템플릿
// 클라스	템플릿

//C# 에서는 제네릭으로 불림

//왠만하면 헤더파일에 만들어라. cpp에 넣으면 오류등 엄청 복잡해진다.


#pragma region 함수 템플릿

// 이런식으로 이름을 정해놓고 인트가 됬건 char가됬건 넣으면 자동으로 변환(지정)됨
// 공용으로 쓰는게 아니라 컴파일러가 함수를 따로 만드는거임
// printint() 와 printfloat()를 따로 내가 안만들어도 컴파일러가 만들어서 동작하는것임
template<typename T>

void Print(T a)
{
	cout << a << endl;
};

//꼭 한번만 하는것은 아니다. 여러개 만들어도 된다.
template<typename T1, typename T2>
void Print(T1 a, T2 b)
{
	cout << a << " " << b << endl;
};


// 만약 인트버전만 따로 쓰고 싶다거나 할때 이렇게 빈칸을 넣고 따로 만들면 된다.
template<>
void Print(int a)
{
	cout << a << endl;
}

#pragma endregion

#pragma region 클라스 템플릿
template<typename TC = int, int SIZE =100>
//이런식으로 초기값을 넣을수 있음 또한 꼭 typename만 넣을수 있는건 아니다.
class RandomBox
{
public:
	TC GetRandomData()
	{
		int index = rand() % SIZE;
		return data[index];
	}

public:
	TC data[SIZE];
};

#pragma endregion

// 템플릿
// 특수화
//
//int main() {
//	Print(1);
//	Print(3.14f);
//	Print("문자열~");
//
//	Print(1, "문자열");
//
//	//이런식으로 수동으로 지정할수도 있고 안하면 자동으로 지정되는거임
//	Print<int>(1);
//	Print<float>(3.14f);
//	Print<const char*>("문자열~");
//
//	Print<int, const char*>(1, "문자열");
//
//	// 사실상 별개의 클라스다. = 하나의 클라스가 아니라 두개가 생긴거임
//	RandomBox<int, 100> rb1;
//	RandomBox<float, 200> rb2;
//}