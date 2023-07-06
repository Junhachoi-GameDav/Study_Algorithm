#include<iostream>
using namespace std;

int main() {
    int h, m, time, result;

    cin >> h >> m;
    cin >> time;

    if (m + time > 59) {
        result = (m + time) % 60;
        h = h + (m + time) / 60 - 1;
        h++;
        if (h > 23)
            h = (m + time) / 60 - 1;
    }
    else {
        result = m + time;
    }
    cout << h << " " << result;
}