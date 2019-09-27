#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Font
{
public:
	Font() {}
	virtual ~Font() {}

	bool Load(std::string path, int fontSize);
	void Unload();

	TTF_Font* GetFont() { return font; }
	std::string GetFontName() { return fontName; }
	int GetFontSize() { return fontSize; }

private:
	TTF_Font* font = nullptr;
	std::string fontName;
	int fontSize;
};
