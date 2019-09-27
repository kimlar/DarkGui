#include "CheckBox.h"

void CheckBox::Create(std::string text, int x, int y)
{
	this->text = new Text(pointerBag);
	this->text->Create(pointerBag->GetAppFont(), text, x + textAdjustX, y + textAdjustY, 0, textColor);

	SetPosition(x, y);
	SetSize(checkBoxHeight + checkBoxAdjustX, checkBoxHeight + checkBoxAdjustY);
}

void CheckBox::Destroy()
{
	text->Destroy();
	delete text;
	text = nullptr;
}

void CheckBox::HandleEvent(SDL_Event& e)
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
				{
					isClicked = true;
					isChecked = !isChecked;
				}
		}
	}
}

void CheckBox::Render()
{
	isClicked = false;

	SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	SDL_RenderDrawRect(&pointerBag->GetRenderer(), &innerRect);

	SDL_Rect backRect = { innerRect.x + 1, innerRect.y + 1, innerRect.w - 2, innerRect.h - 2 };
	if (isHover)
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	else
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), backColor.r, backColor.g, backColor.b, backColor.a);
	SDL_RenderFillRect(&pointerBag->GetRenderer(), &backRect);

	// Draw check mark ?
	if (isChecked)
	{
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), activeColor.r, activeColor.g, activeColor.b, activeColor.a);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 3, innerRect.y + 8,  innerRect.x + 6,  innerRect.y + 11);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 3, innerRect.y + 9,  innerRect.x + 6,  innerRect.y + 12);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 6, innerRect.y + 10, innerRect.x + 12, innerRect.y + 4);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 7, innerRect.y + 10, innerRect.x + 12, innerRect.y + 5);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 7, innerRect.y + 11, innerRect.x + 13, innerRect.y + 5);
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), darkActiveColor.r, darkActiveColor.g, darkActiveColor.b, darkActiveColor.a);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 6,  innerRect.y + 9,  innerRect.x + 11, innerRect.y + 4);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 12, innerRect.y + 3,  innerRect.x + 14, innerRect.y + 5);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 13, innerRect.y + 6,  innerRect.x + 7,  innerRect.y + 12);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 6,  innerRect.y + 13, innerRect.x + 2,  innerRect.y + 9);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 2,  innerRect.y + 8,  innerRect.x + 3,  innerRect.y + 7);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 4,  innerRect.y + 8,  innerRect.x + 5,  innerRect.y + 9);
	}

	text->Render();
}

void CheckBox::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y + 2;
	innerRect.x = x;
	innerRect.y = y + 2;
	text->SetPosition(x + checkBoxHeight + 3, y + checkBoxHeight / 2 - text->GetSize().y / 2);
}

void CheckBox::SetSize(int w, int h)
{
	rect.w = w + text->GetSize().x + textAdjustX;
	rect.h = h - 5;
	innerRect.w = w - 5;
	innerRect.h = h - 5;
}
