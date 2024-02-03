#pragma once
#include "ResourceBase.h"

class Texture : public ResourceBase
{
public:
	Texture();
	virtual ~Texture();

public:
	Texture* LoadBmp(HWND hwnd, const wstring& path);
	HDC GetDC();
	void SetSize(Vec2Int size) { _size = size; }
	Vec2Int GetSize() { return _size; }

	void SetTransparent(uint32 transparent) { _transparant = transparent; }
	uint32 GetTransparent() { return _transparant; }

private:
	HDC _hdc = {};
	HBITMAP _bitmap = {};
	Vec2Int _size = {};
	uint32 _transparant = RGB(255, 0, 255);
};

