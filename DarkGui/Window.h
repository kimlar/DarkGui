#pragma once

#include <SDL.h>
#include <string>
#include "PointerBag.h"

class Window
{
public:
	Window(PointerBag* pointerBag);
	~Window();

	bool run = true;
	void Create(std::string title);
	void Destroy();

	void ClearScreen();
	void UpdateScreen();

	void HandleEvent(SDL_Event& e);

	// Operators
	void SetFullScreen(bool fullscreen, bool exclusive = false);

	// Getters
	SDL_Window& GetWindow() { return *window; }
	SDL_Renderer& GetRenderer() { return *renderer; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int GetRefreshRate() { return refreshRate; }
	bool isFullScreen() { return fullScreen; }
	bool isMinimized() { return minimized; }
	bool hasKeyboardFocus() { return keyboardFocus; }
	bool hasMouseFocus() { return mouseFocus; }
	float GetDT() { return dt; }

private:
	PointerBag* pointerBag = nullptr;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int width;
	int height;
	int refreshRate;
	SDL_Color color = { 0x2D, 0x2D, 0x30, 0xFF };

	bool fullScreen;
	bool useExclusiveFullscreen;
	bool minimized;
	bool keyboardFocus;
	bool mouseFocus;

	float dt;
};
