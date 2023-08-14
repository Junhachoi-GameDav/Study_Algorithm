#pragma once
#include "stdafx.h"

namespace Window
{
	static HINSTANCE global_instance;
	static HWND global_handle;

	//inline = 함수를 컴파일 타임에 구체화 시킬수있음.
	//window proc  = api의 기본. 대부분의 메세지를 처리해줄 것.
	//callback = calling convention은 함수 호출 규칙이다.
	//메모리 적재나 처리하는 방식을 정함
	inline LRESULT CALLBACK WndProc
	(
		HWND handle,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	)
	{
		switch (message)
		{
			//wm 윈도우 메세지 약자
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0); //0을 내보내고 끝
			break;

		default:
			return DefWindowProc(handle, message, wParam, lParam);
		}

		return 0;
	}

	//위도우의 가로,세로 길이 인스턴스(실체화)
	inline void Create(HINSTANCE hInstance, const UINT& width, const UINT& height)
	{
		//설명서 역할을 한다고 한다. 구조체임
		WNDCLASSEX wnd_class;
		wnd_class.cbClsExtra = 0;
		wnd_class.cbWndExtra = 0;
		//static cast는 기본 타입간 형변환 가능
		wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wnd_class.hIcon = LoadIcon(nullptr, IDI_ERROR);
		wnd_class.hIconSm = LoadIcon(nullptr, IDI_ERROR);
		wnd_class.hInstance = hInstance;
		//long pointer 윈도우 프로시져, 사용할 윈도우 프로시져 연결
		wnd_class.lpfnWndProc = WndProc;
		wnd_class.lpszClassName = L"D2D11Game";
		wnd_class.lpszMenuName = nullptr;
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.cbSize = sizeof(WNDCLASSEX);

		auto check = RegisterClassEx(&wnd_class);
		assert(check != 0); //안쪽데이터가 참이면 넘어가고 아니면 프로그램중단시킴.

		//A면 아스키코드 = char 형 , W면 와일드체형 
		global_handle = CreateWindowExW
		(
			WS_EX_APPWINDOW,
			L"D2D11Game",
			L"D2D11Game",
			WS_OVERLAPPEDWINDOW, //기본옵션
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<int>(width), //그냥쓰면 워닝 뜸
			static_cast<int>(height),//cast로 형변환후 쓰면 안뜸
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);
		assert(global_handle != nullptr);
	}

	inline void Show()
	{
		SetForegroundWindow(global_handle); //전면
		SetFocus(global_handle);
		ShowCursor(TRUE);
		ShowWindow(global_handle, SW_NORMAL);
		UpdateWindow(global_handle);
	}

	inline const bool Update()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); //문자열 관련 메세지 만들어주는 함수
			DispatchMessage(&msg); // 윈도우 프로시져로 메세지를 보내줌
		}

		return msg.message != WM_QUIT; //끝나지 않으면 계속 true를 리턴
	}

	inline void Destroy()
	{
		DestroyWindow(global_handle);
		UnregisterClass(L"D2D11Game", global_instance);
	}

	inline const UINT GetWidth()
	{
		RECT rect; //안에 들어가면 자료형이 long으로 되어있다. cast로 형변환해주자
		GetClientRect(global_handle, &rect);
		return static_cast<UINT>(rect.right - rect.left);
	}

	inline const UINT GetHeight()
	{
		RECT rect;
		GetClientRect(global_handle, &rect);
		//윈도우에서는 좌측 상단이 0,0이다. 그래서 큰수(바닥) 부터 빼는것이다.
		return static_cast<UINT>(rect.bottom - rect.top);
	}
}