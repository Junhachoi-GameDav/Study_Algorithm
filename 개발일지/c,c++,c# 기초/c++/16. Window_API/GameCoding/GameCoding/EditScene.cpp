#include "pch.h"
#include "EditScene.h"
#include "InputManager.h"
#include <fstream>

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
}

void EditScene::Init()
{
}

void EditScene::Update()
{
	//한붓 그리기
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		if (_setOrigin)
		{
			_lastPos = mousePos;
			_setOrigin = false;
		}
		else // 점이 두개가 됐을때
		{
			_lines.push_back(make_pair(_lastPos, mousePos));
			_lastPos = mousePos;
		}
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))
		_setOrigin = true;

	//파일 입출력 관련된것은 구글에 많이있다 찾아보면됨
	//Save
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S))
	{
		wofstream file;
		file.open(L"Unit.txt");

		//원하는곳에 놓기 위함
		//화면에 제일큰값과 작은값에 /2를하면됨 
		int32 minX = INT32_MAX;
		int32 maxX = INT32_MIN;
		int32 minY = INT32_MAX;
		int32 maxY = INT32_MIN;

		for (auto& line : _lines)
		{
			POINT from = line.first;
			POINT to = line.second;

			minX = min(min(minX, from.x), to.x);
			maxX = max(max(maxX, from.x), to.x);
			minY = min(min(minY, from.y), to.y);
			maxY = max(max(maxY, from.y), to.y);
		}

		int32 midX = (maxX + minX) / 2;
		int32 midY = (maxY + minY) / 2;

		//라인개수
		file << static_cast<int32>(_lines.size()) << '\n';

		for (auto& line : _lines)
		{
			POINT from = line.first;
			from.x -= midX;
			from.y -= midY;

			POINT to = line.second;
			to.x -= midX;
			to.y -= midY;

			wstring str = std::format(L"({0},{1})->({2},{3})", from.x, from.y, to.x, to.y);
			file << str << endl;
		}

		file.close();
	}

	//Load
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
	{
		wifstream file;
		file.open(L"Unit.txt");

		//라인개수
		int32 count;
		file >> count;

		_lines.clear();


		//원하는 곳에 놓기
		int32 midX = 400;
		int32 midY = 400;


		for (int32 i = 0; i < count; i++)
		{
			POINT pt1;
			POINT pt2;

			wstring str;
			file >> str;
			::swscanf_s(str.c_str(), L"(%d,%d)->(%d,%d)", &pt1.x, &pt1.y, &pt2.x, &pt2.y);

			pt1.x += midX;
			pt1.y += midY;
			pt2.x += midX;
			pt2.y += midY;

			_lines.push_back(make_pair(pt1, pt2));
			_setOrigin = true;
		}
		file.close();
	}
}

void EditScene::Render(HDC hdc)
{
	for (auto& line : _lines)
	{
		POINT pt1 = line.first;
		POINT pt2 = line.second;

		Pos pos1;
		pos1.x = (float)pt1.x;
		pos1.y = (float)pt1.y;


		Pos pos2;
		pos2.x = (float)pt2.x;
		pos2.y = (float)pt2.y;

		Utils::DrowLine(hdc, pos1, pos2);
	}
}
