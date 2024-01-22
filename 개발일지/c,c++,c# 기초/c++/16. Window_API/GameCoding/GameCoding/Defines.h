#pragma once
//매크로 용

#define DECLARE_SINGLE(classname)				\
												\
private:										\
	classname() {}								\
public:											\
	static classname* GetInstance()				\
	{											\
		static classname s_instance;			\
		return &s_instance;						\
	}
//define은 한줄밖에 안되지만 이렇게 하면 된다.
//마지막 줄에는 \을 빼야한다.
//단점으로는 디버깅이 잘 안될수있다. 꼭필요한것에만 쓰도록

#define GET_SINGLE(classname)	classname::GetInstance()

#define SAFE_DELETE(ptr)						\
if (ptr)										\
{												\
	delete ptr;									\
	ptr = nullptr;								\
}