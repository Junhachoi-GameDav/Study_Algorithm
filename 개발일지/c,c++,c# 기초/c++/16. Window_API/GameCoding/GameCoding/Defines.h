#pragma once
//��ũ�� ��

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
//define�� ���ٹۿ� �ȵ����� �̷��� �ϸ� �ȴ�.
//������ �ٿ��� \�� �����Ѵ�.
//�������δ� ������� �� �ȵɼ��ִ�. ���ʿ��ѰͿ��� ������

#define GET_SINGLE(classname)	classname::GetInstance()

#define SAFE_DELETE(ptr)						\
if (ptr)										\
{												\
	delete ptr;									\
	ptr = nullptr;								\
}