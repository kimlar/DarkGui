#pragma once

#include <string>

class FilePath
{
public:
	FilePath() {}
	~FilePath() {}

	void Initialize();

	const std::string GetBasePath() { return basePath; } // Not to be considered writable path
	const std::string GetWritePath() { return writePath; } // Is a writable path specific to this application and user
	const std::string GetPathSeparator(); // Either '\\' or '/'
private:
	std::string basePath;
	std::string writePath;
};
