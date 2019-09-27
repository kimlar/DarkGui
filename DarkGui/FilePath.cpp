#include "FilePath.h"

#include <SDL.h>
//#include "Error.h"

void FilePath::Initialize()
{
	char* tempBasePath = SDL_GetBasePath();
	if (tempBasePath)
		basePath = tempBasePath;
	else
		basePath = SDL_strdup("./");

#ifdef _VSIDE
	basePath.append("../../");
#endif

	const char* companyName = "Replicator Games";
	const char* applicationName = "ProjectManager";
	char* tempWritePath = SDL_GetPrefPath(companyName, applicationName);
	if (tempWritePath)
		writePath = tempWritePath;
	//else
	//	Error("Could not find a writable game-user path");
}

const std::string FilePath::GetPathSeparator()
{
#ifdef _WIN32
	const std::string pathSep = "\\";
#else
	const std::string pathSep = "/";
#endif
	return pathSep;
}
