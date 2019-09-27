#include "Texture.h"
#include "Error.h"

Texture::Texture(SDL_Renderer& renderer) : renderer(renderer)
{
}

Texture::~Texture()
{

}

bool Texture::Load(std::string path)
{
	if (texture)
		Unload();

	// Load image into surface
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		std::string message = "Unable to load image ";
		message.append(path);
		message.append("\nSDL_image error: ");
		message.append(IMG_GetError());
		Error(message);
		return false;
	}
	width = surface->w;
	height = surface->h;

	// Create a texture from surface
	texture = SDL_CreateTextureFromSurface(&renderer, surface);
	if (texture == nullptr)
	{
		Error("Unable to create texture from " + path);
		return false;
	}
	SDL_FreeSurface(surface);

	return true;
}

void Texture::Unload()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}
