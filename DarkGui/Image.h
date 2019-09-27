#pragma once

#include <SDL.h>
#include <string>
#include "PointerBag.h"
#include "Texture.h"

class Image
{
public:
	Image(PointerBag* pointerBag) : pointerBag(pointerBag) {}
	virtual ~Image() { Destroy(); }

	void Create(std::string filePath, int x, int y);
	void Destroy() { Unload(); }

	bool Load(std::string filePath);
	void Unload();

	void Render();

	void SetPosition(int x, int y) { rect.x = x; rect.y = y; }
	SDL_Rect GetRect() { return rect; }

private:
	PointerBag* pointerBag = nullptr;

	Texture* texture = nullptr;
	SDL_Rect rect;
};
