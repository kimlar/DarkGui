#pragma once

#include <string>
#include "PointerBag.h"
#include "Font.h"

class Text
{
public:
	Text(PointerBag* pointerBag) : pointerBag(pointerBag) {}
	virtual ~Text() { FreeTexture(); }

	void Create(Font* font, std::string text, int x, int y, int w = 0, SDL_Color color = {0xF1,0xF1,0xF1,0xFF});
	void Destroy();

	void Render();

	void SetFont(Font* font);
	Font* GetFont() { return font; }

	void SetText(std::string text);
	std::string GetText() { return text; }

	void SetPosition(int x, int y);
	SDL_Point GetPosition() { return { rect.x,rect.y }; }
	SDL_Point GetSize() { return { rect.w,rect.h }; }
	SDL_Rect GetRect() { return rect; }

	void SetColor(SDL_Color color);
	SDL_Color GetColor() { return color; }

	void SetWrapWidth(int w);
	int GetWrapWidth() { return wrapWidth; }

	// Special feature set
	void RemoveText(int start, int len);
	void InsertText(int start, std::string text);
	int GetTextSize() { return (int)text.size(); }
private:
	PointerBag* pointerBag;

	Font* font;
	std::string text;
	SDL_Rect rect;
	SDL_Color color;
	SDL_Texture* texture;
	int wrapWidth;

	void FreeTexture();
	void UpdateTexture();
};
