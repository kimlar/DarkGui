#include "Font.h"
#include "Error.h"

bool Font::Load(std::string path, int fontSize)
{
	font = TTF_OpenFont(path.c_str(), fontSize);
	if (font == nullptr)
	{
		std::string fontError = "Could not load font: ";
		fontError.append(path);
		fontError.append(". SDL_ttf error: ");
		fontError.append(TTF_GetError());
		Error(fontError);
		return false;
	}
	this->fontSize = fontSize;
	this->fontName = TTF_FontFaceFamilyName(font);
	return true;
}

void Font::Unload()
{
	TTF_CloseFont(font);
	font = nullptr;
}
