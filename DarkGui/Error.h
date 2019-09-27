#pragma once

#include <SDL.h>
#include <string>

inline void Error(std::string message, bool useGetError = true, bool useMessageBox = true)
{
	if (useGetError)
	{
		std::string errorString = SDL_GetError();
		message.append("\n");
		message.append(errorString);
	}
	printf("Error: %s\n", message.c_str());
	if(useMessageBox)
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr);
}
