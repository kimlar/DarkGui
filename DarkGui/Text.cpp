#include "Text.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Error.h"

void Text::Create(Font* font, std::string text, int x, int y, int w, SDL_Color color)
{
	this->font = font;
	this->text = text;
	this->rect = { x,y,w,0 };
	this->wrapWidth = (w == 0 ? 65535 : w);
	this->color = color;
	UpdateTexture();
}

void Text::Destroy()
{
	FreeTexture();
}

void Text::Render()
{
	SDL_RenderCopy(&pointerBag->GetRenderer(), texture, nullptr, &rect);
}

void Text::SetFont(Font* font)
{
	this->font = font;
	UpdateTexture();
}

void Text::SetText(std::string text)
{
	this->text = text;
	UpdateTexture();
}

void Text::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
	//UpdateTexture();
}

void Text::SetColor(SDL_Color color)
{
	this->color = color;
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b); // Modulate texture rgb
	SDL_SetTextureAlphaMod(texture, color.a); // Modulate texture alpha
	UpdateTexture();
}

void Text::SetWrapWidth(int w)
{
	wrapWidth = w;
	UpdateTexture();
}

void Text::RemoveText(int start, int len)
{
	text.erase(start, len);
	UpdateTexture();
}

void Text::InsertText(int start, std::string text)
{
	this->text.insert(start, text);
	UpdateTexture();
}

void Text::FreeTexture()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		rect.w = 0;
		rect.h = 0;
	}
}

void Text::UpdateTexture()
{
	FreeTexture();

	// Render text surface
	SDL_Surface* textSurface;
	if (text.size() == 0)
	{
		std::string tempString = " ";
		textSurface = TTF_RenderText_Blended_Wrapped(font->GetFont(), tempString.c_str(), color, GetWrapWidth());
	}
	else
	{
		textSurface = TTF_RenderText_Blended_Wrapped(font->GetFont(), text.c_str(), color, GetWrapWidth());
	}
	if (textSurface == nullptr)
	{
		std::string errorMsg = "Unable to render text surface! SDL_ttf error: ";
		errorMsg.append(TTF_GetError());
		Error(errorMsg);
		return;
	}
	
	// Create texture from surface pixels
	texture = SDL_CreateTextureFromSurface(&pointerBag->GetRenderer(), textSurface);
	if (texture == nullptr)
	{
		std::string errorMsg = "Unable to create texture from rendered text! SDL error: ";
		errorMsg.append(SDL_GetError());
		Error(errorMsg);
		return;
	}

	//Get image dimensions
	if (text.size() == 0)
	{
		rect.w = 0;
		rect.h = 0;
	}
	else
	{
		rect.w = textSurface->w;
		rect.h = textSurface->h;
	}

	//Get rid of old surface
	SDL_FreeSurface(textSurface);
	return;
}
