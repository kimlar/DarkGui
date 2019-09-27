#pragma once

#include <SDL.h>

class Application
{
public:
	Application() {}
	virtual ~Application() {}

	void Loop();

protected:
	virtual void Run() = 0;

private:
	bool InitializeSubSystems();
	void ShutdownSubSystems();
};
