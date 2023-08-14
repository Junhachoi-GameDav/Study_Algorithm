#pragma once
#include "stdafx.h"

namespace Window
{
	static HINSTANCE global_instance;
	static HWND global_handle;

	//inline = �Լ��� ������ Ÿ�ӿ� ��üȭ ��ų������.
	//window proc  = api�� �⺻. ��κ��� �޼����� ó������ ��.
	//callback = calling convention�� �Լ� ȣ�� ��Ģ�̴�.
	//�޸� ���糪 ó���ϴ� ����� ����
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
			//wm ������ �޼��� ����
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0); //0�� �������� ��
			break;

		default:
			return DefWindowProc(handle, message, wParam, lParam);
		}

		return 0;
	}

	//�������� ����,���� ���� �ν��Ͻ�(��üȭ)
	inline void Create(HINSTANCE hInstance, const UINT& width, const UINT& height)
	{
		//���� ������ �Ѵٰ� �Ѵ�. ����ü��
		WNDCLASSEX wnd_class;
		wnd_class.cbClsExtra = 0;
		wnd_class.cbWndExtra = 0;
		//static cast�� �⺻ Ÿ�԰� ����ȯ ����
		wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wnd_class.hIcon = LoadIcon(nullptr, IDI_ERROR);
		wnd_class.hIconSm = LoadIcon(nullptr, IDI_ERROR);
		wnd_class.hInstance = hInstance;
		//long pointer ������ ���ν���, ����� ������ ���ν��� ����
		wnd_class.lpfnWndProc = WndProc;
		wnd_class.lpszClassName = L"D2D11Game";
		wnd_class.lpszMenuName = nullptr;
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.cbSize = sizeof(WNDCLASSEX);

		auto check = RegisterClassEx(&wnd_class);
		assert(check != 0); //���ʵ����Ͱ� ���̸� �Ѿ�� �ƴϸ� ���α׷��ߴܽ�Ŵ.

		//A�� �ƽ�Ű�ڵ� = char �� , W�� ���ϵ�ü�� 
		global_handle = CreateWindowExW
		(
			WS_EX_APPWINDOW,
			L"D2D11Game",
			L"D2D11Game",
			WS_OVERLAPPEDWINDOW, //�⺻�ɼ�
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<int>(width), //�׳ɾ��� ���� ��
			static_cast<int>(height),//cast�� ����ȯ�� ���� �ȶ�
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);
		assert(global_handle != nullptr);
	}

	inline void Show()
	{
		SetForegroundWindow(global_handle); //����
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
			TranslateMessage(&msg); //���ڿ� ���� �޼��� ������ִ� �Լ�
			DispatchMessage(&msg); // ������ ���ν����� �޼����� ������
		}

		return msg.message != WM_QUIT; //������ ������ ��� true�� ����
	}

	inline void Destroy()
	{
		DestroyWindow(global_handle);
		UnregisterClass(L"D2D11Game", global_instance);
	}

	inline const UINT GetWidth()
	{
		RECT rect; //�ȿ� ���� �ڷ����� long���� �Ǿ��ִ�. cast�� ����ȯ������
		GetClientRect(global_handle, &rect);
		return static_cast<UINT>(rect.right - rect.left);
	}

	inline const UINT GetHeight()
	{
		RECT rect;
		GetClientRect(global_handle, &rect);
		//�����쿡���� ���� ����� 0,0�̴�. �׷��� ū��(�ٴ�) ���� ���°��̴�.
		return static_cast<UINT>(rect.bottom - rect.top);
	}
}