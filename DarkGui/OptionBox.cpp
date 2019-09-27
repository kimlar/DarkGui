#include "OptionBox.h"

#include "Ellipse.h"

void OptionBox::Create(std::string text, int x, int y, bool checked)
{
	this->text = new Text(pointerBag);
	this->text->Create(pointerBag->GetAppFont(), text, x + textAdjustX, y + textAdjustY, 0, textColor);

	isChecked = checked;

	SetPosition(x, y);
	SetSize(optionBoxHeight + optionBoxAdjustX, optionBoxHeight + optionBoxAdjustY);
}

void OptionBox::Destroy()
{
	text->Destroy();
	delete text;
	text = nullptr;
}

void OptionBox::HandleEvent(SDL_Event& e)
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

void OptionBox::Render()
{
	isClicked = false;

	SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	DrawEllipse(&pointerBag->GetRenderer(), innerRect.x + innerRect.w / 2, innerRect.y + innerRect.h / 2, 9, 9);

	if (isHover)
	{
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);
		for (int i = 1; i < 9; i++)
			DrawEllipse(&pointerBag->GetRenderer(), innerRect.x + innerRect.w / 2, innerRect.y + innerRect.h / 2, i, i);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 2, innerRect.y + 2, innerRect.x + innerRect.w - 3, innerRect.y + innerRect.h - 3); // fix draw holes
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 2, innerRect.y + innerRect.h - 3, innerRect.x + innerRect.w - 3, innerRect.y + 2); // fix draw holes
	}

	// Draw check mark ?
	if (isChecked)
	{
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), activeColor.r, activeColor.g, activeColor.b, activeColor.a);
		for (int i = 1; i < 5; i++)
			DrawEllipse(&pointerBag->GetRenderer(), innerRect.x + innerRect.w / 2, innerRect.y + innerRect.h / 2, i, i);
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 5, innerRect.y + 5, innerRect.x + innerRect.w - 6, innerRect.y + innerRect.h - 6); // fix draw holes
		SDL_RenderDrawLine(&pointerBag->GetRenderer(), innerRect.x + 5, innerRect.y + innerRect.h - 6, innerRect.x + innerRect.w - 6, innerRect.y + 5); // fix draw holes
		SDL_SetRenderDrawColor(&pointerBag->GetRenderer(), darkActiveColor.r, darkActiveColor.g, darkActiveColor.b, darkActiveColor.a);
		DrawEllipse(&pointerBag->GetRenderer(), innerRect.x + innerRect.w / 2, innerRect.y + innerRect.h / 2, 5, 5);
	}

	text->Render();
}

void OptionBox::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y + 2;
	innerRect.x = x;
	innerRect.y = y + 2;
	text->SetPosition(x + optionBoxHeight + 3, y + optionBoxHeight / 2 - text->GetSize().y / 2);
}

void OptionBox::SetSize(int w, int h)
{
	rect.w = w + text->GetSize().x + textAdjustX;
	rect.h = h - 5;
	innerRect.w = w - 5;
	innerRect.h = h - 5;
}
