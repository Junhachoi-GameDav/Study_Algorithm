// 입출력과 사칙연산

////#1
//#include <iostream>
//using namespace std;
//
//int main() {
//	cout << "Hello World!";
//}

////#2
//#include <iostream>
//using namespace std;
//int main() {
//	int a, b;
//	cin >> a;
//	cin >> b;
//	cout << fixed;
//	cout.precision(9);
//	cout << (double)a / b;
//
//	return 0;
//}

//#3
//#include <iostream>
//using namespace std;
//int main() {
//	int a, b;
//	cin >> a >> b;
//
//	cout << a + b << endl;
//	cout << a - b << endl;
//	cout << a * b << endl;
//	cout << a / b << endl;
//	cout << a % b << endl;
//}

////#4
//#include <iostream>
//using namespace std;
//int main() {
//	string text;
//	cin >> text;
//	cout <<text << "??!";
//}

////#5
//#include <iostream>
//using namespace std;
//int main() {
//	int a;
//	cin >> a;
//	cout << a - 543;
//}

////#6
//#include <iostream>
//using namespace std;
//int main() {
//	int a, b, c;
//	cin >> a >> b >> c;
//	cout << (a + b) % c << endl;
//	cout << ((a%c)+(b%c))%c << endl;
//	cout << (a * b) % c << endl;
//	cout << ((a % c) * (b % c)) % c << endl;
//}

//#7
#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;

	cout << a * (b % 10) << endl;
	cout << a * (((b%100) - ((b%100) % 10)) / 10) << endl;
	cout << a * (((b % 1000) - ((b % 1000) % 100)) / 100) << endl;
	cout << a * b << endl;

}