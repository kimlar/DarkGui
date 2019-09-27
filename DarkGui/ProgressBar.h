#pragma once

#include <SDL.h>
#include "PointerBag.h"

class ProgressBar
{
public:
	ProgressBar(PointerBag* pointerBag) : pointerBag(pointerBag) {}
	virtual ~ProgressBar() {}

	void Create(int value, int max, int x, int y, int w);
	void Destroy();

	void Render();

	void SetPosition(int x, int y);
	SDL_Rect GetRect() { return rect; }

private:
	PointerBag * pointerBag;

	SDL_Rect rect;
	SDL_Color backColor = { 0x2D, 0x2D, 0x30, 0xFF };
	SDL_Color borderColor = { 0x3F, 0x3F, 0x46, 0xFF };
	SDL_Color activeColor = { 0x00, 0x7A, 0xCC, 0xFF };
	
	int value;
	int max;

	const int height = 20;
};
