#pragma once

#include <SDL.h>
#include "PointerBag.h"
#include "Text.h"

class Button
{
public:
	Button(PointerBag* pointerBag) : pointerBag(pointerBag) {}
	virtual ~Button() {}

	void Create(std::string text, int x, int y, int w);
	void Destroy();

	void HandleEvent(SDL_Event& e);
	void Render();

	void SetText(std::string text) { this->text->SetText(text); }
	std::string GetText() { return text->GetText(); }

	void SetPosition(int x, int y);
	SDL_Point GetPosition() { return { rect.x, rect.y }; }
	void SetSize(int w, int h);
	SDL_Point GetSize() { return { rect.w, rect.h }; }
	SDL_Rect GetRect() { return rect; }

	bool isClicked;
private:
	PointerBag* pointerBag;

	Text* text;
	SDL_Rect rect;

	SDL_Color textColor = { 0xF1, 0xF1, 0xF1, 0xFF };
	SDL_Color backColor = { 0x2D, 0x2D, 0x30, 0xFF };
	SDL_Color borderColor = { 0x3F, 0x3F, 0x46, 0xFF };
	SDL_Color activeColor = { 0x00, 0x7A, 0xCC, 0xFF };

	bool isHover;
	bool isDown;

	const int buttonHeight = 20;
	const int textAdjustX = 4;
	const int textAdjustY = 2;
	const int buttonAdjustX = 2;
	const int buttonAdjustY = 2;
};
