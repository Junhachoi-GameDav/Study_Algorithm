#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;


}

void ResourceManager::Clear()
{
	for (auto& item : _textures)
	{
		SAFE_DELETE(item.second);
	}
	_textures.clear();
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparant)
{
	if (_textures.find(key) != _textures.end())
		return _textures[key];

	fs::path fullPath = _resourcePath / path; //나누기가 아니라 path안에 들어있는 합치기 기능이다.

	Texture* texture = new Texture();
	texture->LoadBmp(_hwnd, fullPath.c_str());
	texture->SetTransparent(transparant);
	_textures[key] = texture;

	return texture;
}

Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];

	if (cx == 0)
		cx = texture->GetSize().x;
	if (cy == 0)
		cy = texture->GetSize().y;

	Sprite* sprite = new Sprite(texture, x,y,cx,cy);
	_sprites[key] = sprite;

	return sprite;
}
