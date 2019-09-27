#include "ProgressBar.h"



void ProgressBar::Create(int value, int max, int x, int y, int w)
{
	this->value = (value > max ? max : value);
	this->max = max;
	
	SetPosition(x, y);
	rect.w = w;
	rect.h = height;
}

void ProgressBar::Destroy()
{

}

void ProgressBar::Render()
{
	SDL_Rect progressRect;
	progressRect.x = rect.x;
	progressRect.y = rect.y;
	progressRect.w = (int)(((double)value / (double)max)*rect.w);
	progressRect.h = height;

	SDL_Rect backRect;
	backRect.x = rect.x + progressRect.w;
	backRect.y = rect.y;
	backRect.w = rect.w - (int)(((double)value / (double)max)*rect.w);
	backRect.h = height;

	SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), activeColor.r, activeColor.g, activeColor.b, activeColor.a);
	SDL_RenderFillRect(&pointerBag->GetRenderer(), &progressRect);

	SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	SDL_RenderFillRect(&pointerBag->GetRenderer(), &backRect);
}

void ProgressBar::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}
