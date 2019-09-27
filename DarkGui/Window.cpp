#include "Window.h"
#include "Error.h"

Window::Window(PointerBag* pointerBag) : pointerBag(pointerBag)
{
	pointerBag->SetWindow(this);
}

Window::~Window()
{

}

void Window::Create(std::string title)
{
	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		Error("Linear texture filtering not enabled!");
	}

	// Create window
	//width = 2560; // 800;
	//height = 1440; // 600;
	width = 800;
	height = 600;
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		Error("Window could not be created!");
		run = false;
		return;
	}
	fullScreen = false;
	useExclusiveFullscreen = false; // exclusive or borderless fullscreen
	minimized = false;
	keyboardFocus = true;
	mouseFocus = true;
	//SetFullScreen(fullScreen, useExclusiveFullscreen);

	// Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr)
	{
		Error("Renderer could not be created!");
		run = false;
		return;
	}
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	pointerBag->SetRenderer(renderer);

	// Get the refresh rate of the display where the window is occupied.
	{
		SDL_DisplayMode displayMode;
		int windowDisplayIndex = SDL_GetWindowDisplayIndex(window);
		if (SDL_GetCurrentDisplayMode(windowDisplayIndex, &displayMode) < 0)
		{
			Error("Could not get display mode for video display #" + std::to_string(windowDisplayIndex));
			run = false;
			return;
		}
		refreshRate = displayMode.refresh_rate; // we got the refresh rate.
	}
	dt = 1.0f / GetRefreshRate();
}

void Window::Destroy()
{
	// Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	// Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;
}

void Window::ClearScreen()
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
}

void Window::UpdateScreen()
{
	SDL_RenderPresent(renderer); // Note: this will cause the main thread to sleep until vsync signal.
}

void Window::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_QUIT)
		run = false;

	if (e.type == SDL_WINDOWEVENT)
	{
		switch (e.window.event)
		{
		// Get new dimensions and repaint on window size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			width = e.window.data1;
			height = e.window.data2;
			SDL_RenderPresent(renderer);
			break;

		// Repaint on exposure. Window was obscured and therefore needs to repaint.
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(renderer);
			break;

		// Mouse entered window
		case SDL_WINDOWEVENT_ENTER:
			mouseFocus = true;
			break;

		// Mouse left window
		case SDL_WINDOWEVENT_LEAVE:
			mouseFocus = false;
			break;

		// Window has keyboard focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			keyboardFocus = true;
			mouseFocus = true;
			break;

		// Window lost keyboard focus
		case SDL_WINDOWEVENT_FOCUS_LOST:
			keyboardFocus = false;
			break;

		// Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			minimized = true;
			break;

		// Window maximized
		case SDL_WINDOWEVENT_MAXIMIZED:
			minimized = false;
			break;

		// Window restored
		case SDL_WINDOWEVENT_RESTORED:
			minimized = false;
			break;
		}
	}
	// Enter exit full screen on return key
	else if (e.type == SDL_KEYDOWN && e.key.keysym.mod & KMOD_LALT && e.key.keysym.sym == SDLK_RETURN)
	{
		SetFullScreen(fullScreen, useExclusiveFullscreen);
	}
}

//
// Video modes:
//	* Window mode
//	* Exclusive fullscreen (real fullscreen)
//	* Borderless fullscreen (fake fullscreen)
//
void Window::SetFullScreen(bool fullscreen, bool exclusive)
{
	if (fullScreen)
	{
		// Set to window mode
		SDL_SetWindowFullscreen(window, 0);
		fullScreen = false;

		// Set a default window size
		width = 800;
		height = 600;
		SDL_SetWindowSize(window, width, height);
		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	else
	{
		if (exclusive)
		{
			// Exclusive fullscreen (real fullscreen)
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
			useExclusiveFullscreen = true;
		}
		else
		{
			// Borderless fullscreen (fake fullscreen)
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			useExclusiveFullscreen = false;
		}
		fullScreen = true;
		minimized = false;
	}
}
