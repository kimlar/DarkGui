#include "Application.h"

//#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Error.h"

void Application::Loop()
{
	if (InitializeSubSystems() == false)
	{
		ShutdownSubSystems();
		Error("Engine failed to start up");
		return;
	}

	Run();

	ShutdownSubSystems();
}

bool Application::InitializeSubSystems()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Error("SDL could not initialize!");		
		return false;
	}

	// Initialing SDL_image (png only)
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::string imgError = "SDL_image could not initialize! SDL_image error: ";
		imgError.append(IMG_GetError());
		Error(imgError);
		return false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::string ttfError = "SDL_ttf could not initialize! SDL_ttf error: ";
		ttfError.append(TTF_GetError());
		Error(ttfError);
		return false;
	}

	return true;
}

void Application::ShutdownSubSystems()
{
	// Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
