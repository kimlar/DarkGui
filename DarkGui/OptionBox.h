#pragma once

#include <SDL.h>
#include "PointerBag.h"
#include "Text.h"

class OptionBox
{
public:
	OptionBox(PointerBag* pointerBag) : pointerBag(pointerBag) {}
	virtual ~OptionBox() {}

	void Create(std::string text, int x, int y, bool checked = false);
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
	bool isChecked;
private:
	PointerBag * pointerBag;

	Text* text;
	SDL_Rect rect;
	SDL_Rect innerRect;

	SDL_Color textColor = { 0xF1, 0xF1, 0xF1, 0xFF };
	SDL_Color backColor = { 0x2D, 0x2D, 0x30, 0xFF };
	SDL_Color borderColor = { 0x3F, 0x3F, 0x46, 0xFF };
	SDL_Color activeColor = { 0x00, 0x7A, 0xCC, 0xFF };
	SDL_Color darkActiveColor = { 0x24, 0x5E, 0x81, 0xFF };

	bool isHover;
	bool isDown;

	const int optionBoxSize = 14;
	const int optionBoxMargin = 3;

	const int optionBoxHeight = 20;
	const int textAdjustX = 4;
	const int textAdjustY = 2;
	const int optionBoxAdjustX = 2;
	const int optionBoxAdjustY = 2;
};
