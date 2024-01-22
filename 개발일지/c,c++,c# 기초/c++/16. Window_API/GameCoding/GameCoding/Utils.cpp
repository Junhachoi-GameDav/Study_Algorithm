#include "pch.h"
#include "Utils.h"

void Utils::DrowText(HDC hdc, Pos pos, const wstring& str)
{
	::TextOut(hdc, static_cast<int32>(pos.x), static_cast<int32>(pos.y), 
		str.c_str(), static_cast<int32>(str.size()));
}

void Utils::DrowReat(HDC hdc, Pos pos, int32 w, int32 h)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - w / 2), 
		static_cast<int32>(pos.y - h / 2), 
		static_cast<int32>(pos.x + w / 2), 
		static_cast<int32>(pos.y + h / 2));
}

void Utils::DrowCircle(HDC hdc, Pos pos, int32 radius)
{
	::Ellipse(hdc, static_cast<int32>(pos.x - radius),
		static_cast<int32>(pos.y - radius),
		static_cast<int32>(pos.x + radius),
		static_cast<int32>(pos.y + radius));
}

void Utils::DrowLine(HDC hdc, Pos from, Pos to)
{
	::MoveToEx(hdc, static_cast<int32>( from.x), 
		static_cast<int32>( from.y), nullptr);
	::LineTo(hdc, static_cast<int32>(to.x), static_cast<int32>(to.y));
}
