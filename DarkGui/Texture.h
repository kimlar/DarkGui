#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture
{
public:
	Texture(SDL_Renderer& renderer);
	~Texture();

	bool Load(std::string path);
	void Unload();

	SDL_Texture& GetTexture() { return *texture; }

	int GetWidth() { return width; }
	int GetHeight() { return height; }

private:
	SDL_Renderer& renderer;
	SDL_Texture* texture = nullptr;
	int width = 0;
	int height = 0;
};
