#pragma once

#include <SDL.h>

class FilePath;
class Window;
class Font;

class PointerBag
{
public:
	PointerBag() { run = true; }
	~PointerBag() {}

	void SetFilePath(FilePath* filePath) { this->filePath = filePath; }
	FilePath* GetFilePath() { return filePath; }

	void SetWindow(Window* window) { this->window = window; }
	Window* GetWindow() { return window; }

	void SetRenderer(SDL_Renderer* renderer) { this->renderer = renderer; }
	SDL_Renderer& GetRenderer() { return *renderer; }

	void SetAppFont(Font* appFont) { this->appFont = appFont; }
	Font* GetAppFont() { return appFont; }

	bool run;
private:
	FilePath* filePath = nullptr;
	Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Font* appFont = nullptr;
};
