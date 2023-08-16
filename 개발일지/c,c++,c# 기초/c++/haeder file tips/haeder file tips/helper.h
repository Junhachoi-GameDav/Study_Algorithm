#pragma once // 예전에는 #define 등을 썼지만 지금은 이거로 헤데파일 중복을 막는다.

void Test();
void Test2();

extern int Gtest; //이런식으로 쓸수도 있다. 근데 왠만하면 전역변수는 안쓰는게 좋다고 한다.

//헤데파일에서는 최대한 간략하게 쓰는것이 좋다.
//선언문만 쓴다거나 enum문만을 쓴다거나..