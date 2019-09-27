#include "Button.h"

void Button::Create(std::string text, int x, int y, int w)
{
	this->text = new Text(pointerBag);
	this->text->Create(pointerBag->GetAppFont(), text, x + textAdjustX, y + textAdjustY, 0, textColor);

	SetPosition(x, y);
	SetSize(w + buttonAdjustX, buttonHeight + buttonAdjustY);
}

void Button::Destroy()
{
	text->Destroy();
	delete text;
	text = nullptr;
}

void Button::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		int mx = e.motion.x;
		int my = e.motion.y;

		isHover = false;
		if (mx >= rect.x && mx < (rect.x + rect.w))
			if (my >= rect.y && my < (rect.y + rect.h))
				isHover = true;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		int mx = e.motion.x;
		int my = e.motion.y;

		if (mx >= rect.x && mx < (rect.x + rect.w))
			if (my >= rect.y && my < (rect.y + rect.h))
				isDown = true;
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		int mx = e.motion.x;
		int my = e.motion.y;

		if (isDown)
		{
			isDown = false;
			if (mx >= rect.x && mx < (rect.x + rect.w))
				if (my >= rect.y && my < (rect.y + rect.h))
					isClicked = true;
		}
	}
}

void Button::Render()
{
	isClicked = false;

	SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	SDL_RenderDrawRect(&pointerBag->GetRenderer(), &rect);
	
	SDL_Rect backRect = { rect.x + 1, rect.y + 1, rect.w - 2, rect.h - 2 };
	if (isHover)
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	else
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), backColor.r, backColor.g, backColor.b, backColor.a);
	SDL_RenderFillRect(&pointerBag->GetRenderer(), &backRect);

	text->Render();
}

void Button::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
	text->SetPosition(x + rect.x / 2 - text->GetSize().x / 2, y + buttonHeight / 2 - text->GetSize().y / 2);
}

void Button::SetSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
}
