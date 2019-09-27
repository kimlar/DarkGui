#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "PointerBag.h"
#include "Text.h"

// TODOs:
//	* Text selection. Start,End + draw, Shift+Left/Right, Mouse selection
//	* Fix clipboard functions
//	* Common shortkeys: Ctrl+Left/Right, Ctrl+Home/End ...
//

class TextBox
{
public:
	TextBox(PointerBag* pointerBag) : pointerBag(pointerBag) {}
	virtual ~TextBox() {}

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

	void SetTextWrap(bool wrap);
	bool GetTextWrap() { return useTextWrap; }

private:
	PointerBag* pointerBag;

	Text* text;
	SDL_Rect rect;
	bool useTextWrap;

	// Edit texture (Render Texture)
	SDL_Texture* editTexture;
	SDL_Rect editRect;
	SDL_Point editCursor;
	SDL_Color textColor = { 0xF1, 0xF1, 0xF1, 0xFF };
	SDL_Color backColor = { 0x33, 0x33, 0x37, 0xFF };
	SDL_Color borderColor = { 0x3F, 0x3F, 0x46, 0xFF };
	SDL_Color activeColor = { 0x00, 0x7A, 0xCC, 0xFF };
	void CreateEditTexture(int w, int h);
	void RenderTargetEditTexture();

	bool isActive;
	bool isHover;

	// Text cursor
	int textCursorCX;
	std::vector<int> textCharsLocPX;
	void UpdateCursorLocation();
	void MouseSetTextCursorX(int mx);

	// Text control
	void InsertText(std::string text);
	void RemoveText(int startCX, int lenCX = 1);

	const int textAdjustX = 4;
	const int textAdjustY = 1;
	const int backAdjustX = 2;
	const int backAdjustY = 2;
};
