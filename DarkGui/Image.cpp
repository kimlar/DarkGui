#include "Image.h"

#include "FilePath.h"

void Image::Create(std::string filePath, int x, int y)
{
	Load(filePath);
	SetPosition(x, y);
}

bool Image::Load(std::string filePath)
{
	if (texture)
		Unload();

	texture = new Texture(pointerBag->GetRenderer());
	std::string realPath = "";
	realPath.append(pointerBag->GetFilePath()->GetBasePath());
	realPath.append("Resources");
	realPath.append(pointerBag->GetFilePath()->GetPathSeparator());
	realPath.append(filePath);
	if (texture->Load(realPath))
	{
		rect.x = 0;
		rect.y = 0;
		rect.w = texture->GetWidth();
		rect.h = texture->GetHeight();
		return true;
	}

	return false; // failed to load
}

void Image::Unload()
{
	if (texture)
	{
		texture->Unload();
		delete texture;
		texture = nullptr;
	}
}

void Image::Render()
{
	SDL_RenderCopy(&pointerBag->GetRenderer(), &texture->GetTexture(), nullptr, &rect);
}
